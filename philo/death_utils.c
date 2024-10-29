/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:46:07 by tialbert          #+#    #+#             */
/*   Updated: 2024/07/18 21:33:23 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/philo.h"

int	kill_unlock_cond(t_philo_lst *philo_lst, int type)
{
	pthread_mutex_lock(&philo_lst->philo_cond->kill_mutex);
	if (philo_lst->kill != 0 || philo_lst->philo_const->philos_num == 1)
	{
		pthread_mutex_unlock(&philo_lst->philo_cond->kill_mutex);
		if (type == 0)
		{
			if (philo_lst->philo_const->philos_num == 1)
				write_state(&philo_lst, "fork");
			if (pthread_mutex_unlock(&philo_lst->mutex) != 0)
				return (-1);
		}
		else if (type == 1)
			mutex_unlock(philo_lst);
		return (-1);
	}
	pthread_mutex_unlock(&philo_lst->philo_cond->kill_mutex);
	return (0);
}

int	kill_cond(t_philo_lst *philo_lst)
{
	pthread_mutex_lock(&philo_lst->philo_cond->kill_mutex);
	if (philo_lst->kill != 0)
	{
		pthread_mutex_unlock(&philo_lst->philo_cond->kill_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo_lst->philo_cond->kill_mutex);
	return (0);
}
