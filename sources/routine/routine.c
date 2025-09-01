/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:41:44 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/01 14:51:04 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

bool	ft_eat(t_philo *philo, long start_time)
{
	//mutex fork to add
	pthread_mutex_lock(&philo->data->print);
	printf("[%zu] %d is eating\n", get_time() - start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->print);
	philo->last_meal = get_time();
	if (philo->nb_of_meal < philo->min_to_eat)
			philo->nb_of_meal++;
	else if (philo->nb_of_meal == philo->min_to_eat)
	{
		philo->nb_of_meal++;
		pthread_mutex_lock(&philo->data->data);
		philo->data->satiated++;
		pthread_mutex_unlock(&philo->data->data);
	}
	usleep(philo->tt_eat * 1000);
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
	usleep((philo->tt_die - (philo->tt_eat + philo->tt_sleep)) * 1000);
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
	printf("routine[%d]: start\n", philo->philo_id + 1);
	while(!philo->data->run_sim)
		continue;
	printf("routine[%d]: log 1\n", philo->philo_id + 1);
	start_time = get_time();
	philo->last_meal = get_time();
	while (1)
	{
		if (ft_eat(philo, start_time))
			break ;
		printf("routine[%d]: log 2\n", philo->philo_id + 1);
		if (ft_sleep(philo, start_time))
			break ;
		printf("routine[%d]: log 3\n", philo->philo_id + 1);
		if (ft_think(philo, start_time))
			break ;
	}
	printf("routine[%d]: end\n", philo->philo_id + 1);
	return (NULL);
}
