/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:54:59 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/01 14:43:49 by lfournie         ###   ########.fr       */
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
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	int				min_to_eat;
	int				nb_of_meal;
	long			last_meal;
	bool			is_dead;
	pthread_mutex_t	philo_data;
	struct s_data	*data;
	
}	t_philo;

typedef struct s_data
{
	pthread_t		monitor;
	bool			run_sim;
	int				nb_philo;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	int				min_to_eat;
	int				satiated;
	bool			stop;
	t_philo			*philo;
	pthread_mutex_t data;
	pthread_mutex_t print;
	pthread_mutex_t	*forks;
}	t_data;

//ROUTINE
///////
void	*routine(void *args);
bool	check_if_dead(t_philo *philo);
time_t	get_time(void);
bool	ft_eat(t_philo *philo, long start_time);
bool	ft_sleep(t_philo *philo, long start_time);
bool	ft_think(t_philo *philo, long start_time);
void	ft_die(t_philo *philo, long start_time);
///////

//UTILS
///////
int		ft_atoi(const char *nptr);
t_data	*init_data_struct(char **args);
t_philo	*init_philo_struct(t_data *data, int i);
///////

//ERR_HANDLER
///////
bool	check_args(char **args);
void	wrong_usage(void);
///////

//FREE_HANDLER
///////
void	free_philo_tab(t_philo **tab, int size);
///////

#endif