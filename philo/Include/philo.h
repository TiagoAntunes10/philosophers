/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:42:52 by tialbert          #+#    #+#             */
/*   Updated: 2024/07/20 22:32:34 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

# define WB "\033[1;37m"
# define W "\033[0;37m"
# define CR "\033[0;31m"
# define G "\033[0;32m"
# define Y "\033[0;33m"
# define B "\033[0;34m"

typedef struct s_philo_const
{
	long long	philos_num;
	long long	t_die;
	long long	t_eat;
	long long	t_sleep;
	long long	eat_num;
	int			queue;
}				t_philo_const;

typedef struct s_cond
{
	int				death;
	int				start;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	kill_mutex;
}				t_cond;

typedef struct s_philo_lst
{
	int					seat;
	int					kill;
	long long			t_init;
	long long			t_after_eat;
	long long			t_now;
	pthread_mutex_t		t_to_die_mutex;
	pthread_mutex_t		mutex;
	pthread_mutex_t		time_mutex;
	t_philo_const		*philo_const;
	t_cond				*philo_cond;
	struct s_philo_lst	*next;
	struct s_philo_lst	*prev;
}					t_philo_lst;

int			get_args(t_philo_const *philo, char **argv, int argc);
void		argument_error(int type);
t_philo_lst	*create_lst(t_philo_const *philo);
int			mutex_unlock(t_philo_lst *philo_lst);
void		*run_thread(void *arg);
void		*watcher(void *arg);
int			philo_sim(t_philo_lst *philo_lst, int eat_limit);
int			start_mutex(t_philo_lst **philo_lst);
int			end_lst(t_philo_lst *philo_lst);
int			get_init_time(t_philo_lst **philo_lst);
int			get_current_time(t_philo_lst *philo_lst, int type);
int			starve_check(t_philo_lst **philo_lst);
int			kill_unlock_cond(t_philo_lst *philo_lst, int type);
int			kill_cond(t_philo_lst *philo_lst);
void		write_state(t_philo_lst **philo_lst, char *state);
int			start_sim(t_philo_lst *philo_lst);
int			death_check(t_philo_lst *philo_lst);
int			kill_philos(t_philo_lst *philo_lst);
void		eating_queue(t_philo_lst *philo_lst, int eat_limit);

#endif
