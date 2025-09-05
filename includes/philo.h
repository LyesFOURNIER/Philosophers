/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:54:59 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/05 15:23:33 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	unsigned long	tt_die;
	unsigned long	tt_eat;
	unsigned long	tt_sleep;
	unsigned long	tt_think;
	int				nb_of_meal;
	unsigned long	last_meal;
	bool			is_dead;
	pthread_mutex_t	m_philo;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	pthread_t		monitor;
	unsigned long	start_time;
	bool			is_running;
	int				nb_philo;
	unsigned long	tt_die;
	unsigned long	tt_eat;
	unsigned long	tt_sleep;
	int				min_to_eat;
	int				satiated;
	bool			stop;
	int				free_size;
	t_philo			**philo_tab;
	pthread_mutex_t	m_data;
	pthread_mutex_t	m_print;
	pthread_mutex_t	*m_fork;
}	t_data;

//ROUTINE
///////
void	*routine(void *args);
void	*m_routine(void *args);
void	m_subroutine(t_data *data, int i, int nb);
bool	ft_eat(t_philo *philo, unsigned long start_time);
bool	ft_sleep(t_philo *philo, unsigned long start_time);
bool	ft_think(t_philo *philo, unsigned long start_time);
void	ft_die(t_philo *philo, unsigned long start_time);
///////

//UTILS
///////
int		ft_atoi(const char *nptr);
t_data	*init_data_struct(char **args);
t_philo	*init_philo_struct(t_data *data, int i);
bool	get_fork(t_philo *philo, unsigned long start_time);
void	put_down_forks(t_philo *philo);
bool	check_if_dead(t_philo *philo);
time_t	get_time(void);
bool	safe_mutex_lock(t_philo *philo, unsigned long s_t, pthread_mutex_t *m);
///////

//ERR_HANDLER
///////
bool	check_args(char **args);
void	wrong_usage(void);
bool	are_threads_created(t_data *data, int i);
///////

//FREE_HANDLER
///////
void	join_thread(t_data *data, int size);
void	free_philo_tab(t_philo **ptab, int size);
void	free_forks_tab(pthread_mutex_t	*ftab, int size);
void	free_all(t_data *data, int fr_thrd, int fr_ph, int fr_frk);
///////

#endif