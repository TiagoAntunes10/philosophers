/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 10:51:49 by tialbert          #+#    #+#             */
/*   Updated: 2024/07/20 22:32:53 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/philo.h"

int	get_init_time(t_philo_lst **philo_lst)
{
	struct timeval	t_init;
	t_philo_lst		*lst;
	int				i;

	lst = *philo_lst;
	if (gettimeofday(&t_init, NULL) != 0)
		return (-1);
	i = 0;
	while (i++ < lst->philo_const->philos_num)
	{
		lst->t_init = t_init.tv_sec * 1000 + t_init.tv_usec / 1000;
		lst = lst->next;
	}
	return (0);
}

static long long	get_time(t_philo_lst *philo_lst)
{
	struct timeval	t_now;

	if (gettimeofday(&t_now, NULL) != 0)
		return (-1);
	return ((t_now.tv_sec * 1000 + t_now.tv_usec / 1000) - philo_lst->t_init);
}

int	get_current_time(t_philo_lst *philo_lst, int type)
{
	long long		t;

	t = get_time(philo_lst);
	if (t == -1)
		return (-1);
	if (type == 0)
	{
		pthread_mutex_lock(&philo_lst->t_to_die_mutex);
		philo_lst->t_after_eat = t;
		pthread_mutex_unlock(&philo_lst->t_to_die_mutex);
	}
	else if (type == 1)
	{
		pthread_mutex_lock(&philo_lst->time_mutex);
		philo_lst->t_now = t;
		pthread_mutex_unlock(&philo_lst->time_mutex);
	}
	return (0);
}

int	starve_check(t_philo_lst **philo_lst)
{
	long	t_now;

	pthread_mutex_lock(&(*philo_lst)->t_to_die_mutex);
	t_now = get_time(*philo_lst);
	if ((t_now - (*philo_lst)->t_after_eat) >= (*philo_lst)->philo_const->t_die)
	{
		pthread_mutex_unlock(&(*philo_lst)->t_to_die_mutex);
		return (1);
	}
	pthread_mutex_unlock(&(*philo_lst)->t_to_die_mutex);
	return (0);
}
