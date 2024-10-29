/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 23:19:39 by tialbert          #+#    #+#             */
/*   Updated: 2024/07/20 22:37:33 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/philo.h"

static int	mutex_lock(t_philo_lst *philo_lst, int eat_limit)
{
	t_philo_lst	*lst;

	lst = philo_lst;
	if (philo_lst->seat == lst->philo_const->philos_num)
		lst = lst->next;
	eating_queue(philo_lst, eat_limit);
	if (pthread_mutex_lock(&lst->mutex) != 0)
		return (-1);
	if (get_current_time(philo_lst, 1) == -1)
		return (-1);
	if (kill_unlock_cond(lst, 0) != 0)
		return (-1);
	write_state(&philo_lst, "fork");
	if (philo_lst->seat == lst->philo_const->philos_num)
		lst = lst->prev;
	else
		lst = lst->next;
	if (pthread_mutex_lock(&lst->mutex) != 0)
		return (-1);
	if (get_current_time(philo_lst, 1) == -1)
		return (-1);
	if (kill_unlock_cond(philo_lst, 1) != 0)
		return (-1);
	write_state(&philo_lst, "fork");
	return (0);
}

int	mutex_unlock(t_philo_lst *philo_lst)
{
	t_philo_lst	*lst;

	lst = philo_lst;
	if (philo_lst->seat == lst->philo_const->philos_num)
		lst = lst->next;
	if (pthread_mutex_unlock(&lst->mutex) != 0)
		return (-1);
	if (philo_lst->seat == lst->philo_const->philos_num)
		lst = lst->prev;
	else
		lst = lst->next;
	if (pthread_mutex_unlock(&lst->mutex) != 0)
		return (-1);
	return (0);
}

int	philo_sim(t_philo_lst *philo_lst, int eat_limit)
{
	if (get_current_time(philo_lst, 1) == -1)
		return (-1);
	if (pthread_mutex_lock(&philo_lst->time_mutex) != 0)
		return (-1);
	printf(WB"\%lld"Y" %d is thinking\n", philo_lst->t_now, philo_lst->seat);
	if (pthread_mutex_unlock(&philo_lst->time_mutex) != 0)
		return (-1);
	if (mutex_lock(philo_lst, eat_limit) == -1)
		return (-1);
	if (kill_unlock_cond(philo_lst, 1) != 0)
		return (-1);
	if (get_current_time(philo_lst, 0) == -1)
		return (-1);
	write_state(&philo_lst, "eat");
	if (mutex_unlock(philo_lst) == -1)
		return (-1);
	if (kill_cond(philo_lst) != 0)
		return (-1);
	if (get_current_time(philo_lst, 1) == -1)
		return (-1);
	write_state(&philo_lst, "sleep");
	if (kill_cond(philo_lst) != 0)
		return (-1);
	return (0);
}

void	*run_thread(void *arg)
{
	t_philo_lst		*philo_lst;

	philo_lst = (t_philo_lst *) arg;
	pthread_mutex_lock(&philo_lst->philo_cond->death_mutex);
	philo_lst->philo_const->queue++;
	while (philo_lst->philo_cond->start != 1)
	{
		pthread_mutex_unlock(&philo_lst->philo_cond->death_mutex);
		usleep(50);
		pthread_mutex_lock(&philo_lst->philo_cond->death_mutex);
	}
	pthread_mutex_unlock(&philo_lst->philo_cond->death_mutex);
	if (start_sim(philo_lst) == -1)
		return (NULL);
	return (NULL);
}

void	*watcher(void *arg)
{
	t_philo_lst	*philo_lst;

	philo_lst = (t_philo_lst *) arg;
	pthread_mutex_lock(&philo_lst->philo_cond->death_mutex);
	while (philo_lst->philo_const->queue < philo_lst->philo_const->philos_num)
	{
		pthread_mutex_unlock(&philo_lst->philo_cond->death_mutex);
		usleep(5);
		pthread_mutex_lock(&philo_lst->philo_cond->death_mutex);
	}
	philo_lst->philo_cond->start++;
	if (get_init_time(&philo_lst) == -1)
		return (NULL);
	pthread_mutex_unlock(&philo_lst->philo_cond->death_mutex);
	if (death_check(philo_lst) != 0)
		return (NULL);
	if (get_current_time(philo_lst, 1) == -1)
		return (NULL);
	pthread_mutex_lock(&philo_lst->time_mutex);
	printf(WB"\%lld"CR" %d died\n", philo_lst->t_now,
		philo_lst->philo_cond->death);
	pthread_mutex_unlock(&philo_lst->time_mutex);
	if (kill_philos(philo_lst) != 0)
		return (NULL);
	return (NULL);
}
