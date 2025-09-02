/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:41:44 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/02 16:07:21 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_eat(t_philo *philo, long start_time)
{
	get_fork(philo);
	pthread_mutex_lock(&philo->data->print);
	printf("[%zu] %d is eating\n", get_time() - start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->print);
	philo->last_meal = get_time();
	if (philo->nb_of_meal < philo->min_to_eat)
			philo->nb_of_meal++;
	/* else if (philo->nb_of_meal == philo->min_to_eat)
	{
		A check dans le monitor
		philo->nb_of_meal++;
		pthread_mutex_lock(&philo->data->data);
		philo->data->satiated++;
		pthread_mutex_unlock(&philo->data->data);
	} */
	usleep(philo->tt_eat * 1000);
	put_down_forks(philo);
	return(false);
}

bool	ft_sleep(t_philo *philo, long start_time)
{
	pthread_mutex_lock(&philo->data->print);
	printf("[%zu] %d is sleeping\n", get_time() - start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->print);
	usleep(philo->tt_sleep * 1000);
	return(false);
}

bool	ft_think(t_philo *philo, long start_time)
{
	pthread_mutex_lock(&philo->data->print);
	printf("[%zu] %d is thinking\n", get_time() - start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->print);
	if (philo->tt_think >= 0)
		usleep(philo->tt_think * 1000);
	return(false);
}

void	ft_die(t_philo *philo, long start_time)
{
	pthread_mutex_lock(&philo->philo_data);
	philo->is_dead = true;
	pthread_mutex_unlock(&philo->philo_data);
	pthread_mutex_lock(&philo->data->print);
	printf("[%zu] %d has died\n", get_time() - start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->print);
}

void	*routine(void *args)
{
	long	start_time;
	t_philo *philo;
	
	philo = (t_philo *)args;
	while(!philo->data->run_sim)
		continue;
	start_time = get_time();
	philo->last_meal = get_time();
	while (1)
	{
		if (!philo->data->run_sim)
			break ;
		if (ft_eat(philo, start_time))
			break ;
		if (ft_sleep(philo, start_time))
			break ;
		if (ft_think(philo, start_time))
			break ;
		if (get_time() - philo->last_meal > philo->tt_die)
		{
			ft_die(philo, start_time);
			philo->data->run_sim = false;
			break ;
		}
	}
	return (NULL);
}
