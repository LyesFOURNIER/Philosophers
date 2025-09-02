/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:47:59 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/02 16:09:07 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	check_if_dead(t_philo *philo)
{
	if (philo->last_meal >= philo->tt_die)
		return (true);
	return (false);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	get_fork(t_philo *philo)
{
	int	i;
	
	i = philo->philo_id;
	if (i % 2 == 0)
	{
		if (i < philo->data->nb_philo)
			pthread_mutex_lock(&philo->data->forks[i + 1]);
		else if (i == philo->data->nb_philo)
			pthread_mutex_lock(&philo->data->forks[0]);
		//check if sim still going
		//if not dont lock mutex
		//needs to code the function safe_mutex_lock
		pthread_mutex_lock(&philo->data->forks[i]);
	}
	else if (i % 2 == 1)
	{
		if (i > 0)
			pthread_mutex_lock(&philo->data->forks[i - 1]);
		else if (i == 0)
			pthread_mutex_lock(&philo->data->forks[philo->data->nb_philo]);
		pthread_mutex_lock(&philo->data->forks[i]);
	}
}

void	put_down_forks(t_philo *philo)
{
	int	i;
	
	i = philo->philo_id;
	if (i % 2 == 0)
	{
		if (i < philo->data->nb_philo)
			pthread_mutex_unlock(&philo->data->forks[i + 1]);
		else if (i == philo->data->nb_philo)
			pthread_mutex_unlock(&philo->data->forks[0]);
		pthread_mutex_unlock(&philo->data->forks[i]);
	}
	else if (i % 2 == 1)
	{
		if (i > 0)
			pthread_mutex_unlock(&philo->data->forks[i - 1]);
		else if (i == 0)
			pthread_mutex_unlock(&philo->data->forks[philo->data->nb_philo]);
		pthread_mutex_unlock(&philo->data->forks[i]);
	}
}
