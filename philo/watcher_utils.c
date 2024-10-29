/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:19:18 by tialbert          #+#    #+#             */
/*   Updated: 2024/07/20 22:32:27 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/philo.h"

int	death_check(t_philo_lst *philo_lst)
{
	int	num_finished;

	num_finished = 0;
	pthread_mutex_lock(&philo_lst->philo_cond->death_mutex);
	while (philo_lst->philo_cond->death <= 0)
	{
		pthread_mutex_unlock(&philo_lst->philo_cond->death_mutex);
		if (starve_check(&philo_lst) == 1)
			philo_lst->philo_cond->death = philo_lst->seat;
		usleep(75);
		pthread_mutex_lock(&philo_lst->philo_cond->death_mutex);
		if (philo_lst->philo_cond->death == -1)
		{
			num_finished++;
			if (num_finished == philo_lst->philo_const->philos_num)
			{
				pthread_mutex_unlock(&philo_lst->philo_cond->death_mutex);
				return (-1);
			}
		}
		philo_lst = philo_lst->next;
	}
	pthread_mutex_unlock(&philo_lst->philo_cond->death_mutex);
	return (0);
}

int	kill_philos(t_philo_lst *philo_lst)
{
	int			i;
	t_philo_lst	*lst;

	i = 0;
	lst = philo_lst;
	while (i++ < lst->philo_const->philos_num)
	{
		if (pthread_mutex_lock(&lst->philo_cond->kill_mutex) != 0)
			return (-1);
		lst->kill++;
		if (pthread_mutex_unlock(&lst->philo_cond->kill_mutex) != 0)
			return (-1);
		lst = lst->next;
	}
	return (0);
}
