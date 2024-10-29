/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:42:17 by tialbert          #+#    #+#             */
/*   Updated: 2024/07/18 21:49:47 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/philo.h"

static int	start_threads(t_philo_lst *lst, pthread_t *thread)
{
	int	i;

	i = 0;
	if (pthread_create(&thread[i++], NULL, &watcher, (void *) lst) != 0)
		return (-1);
	while (i <= lst->philo_const->philos_num)
	{
		if (pthread_create(thread + i, NULL, &run_thread, (void *) lst) != 0)
			return (-1);
		i++;
		lst = lst->next;
	}
	i = 0;
	while (i <= lst->philo_const->philos_num)
	{
		if (pthread_join(thread[i++], NULL) != 0)
			return (-1);
	}
	return (0);
}

static void	start_philo(t_philo_lst **philo_lst)
{
	pthread_t		*thread;
	int				philos_num;
	t_philo_lst		*lst;

	if ((*philo_lst)->philo_const->eat_num == 0)
		return ;
	philos_num = (*philo_lst)->philo_const->philos_num;
	lst = *philo_lst;
	thread = malloc(sizeof(pthread_t) * (philos_num + 1));
	if (thread == NULL)
		return ;
	if (start_threads(lst, thread) != 0)
		return (free(thread));
	free(thread);
	return ;
}

int	main(int argc, char **argv)
{
	t_philo_const	*philo;
	t_philo_lst		*philo_lst;

	if (argc < 5 || argc > 6)
	{
		argument_error(0);
		return (-1);
	}
	philo = malloc(sizeof(t_philo_const));
	if (philo == NULL)
		return (0);
	philo->queue = 0;
	if (get_args(philo, argv, argc) != 0)
	{
		argument_error(1);
		free(philo);
		return (-1);
	}
	philo_lst = create_lst(philo);
	if (philo_lst == NULL)
		return (end_lst(philo_lst));
	start_philo(&philo_lst);
	end_lst(philo_lst);
	return (1);
}
