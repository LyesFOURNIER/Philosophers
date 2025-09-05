/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:41:44 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/05 17:00:17 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_eat(t_philo *philo, unsigned long start_time)
{
	if (!get_fork(philo, start_time))
		return (false);
	if (!safe_mutex_lock(philo, &philo->data->m_print))
		return (put_down_forks(philo), false);
	printf("%zu %d is eating\n", get_time() - start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->m_print);
	philo->last_meal = get_time();
	if (!safe_mutex_lock(philo, &philo->m_philo))
		return (put_down_forks(philo), false);
	philo->nb_of_meal++;
	pthread_mutex_unlock(&philo->m_philo);
	usleep(philo->tt_eat * 1000);
	put_down_forks(philo);
	return (true);
}

bool	ft_sleep(t_philo *philo, unsigned long start_time)
{
	if (!safe_mutex_lock(philo, &philo->data->m_print))
		return (false);
	printf("%zu %d is sleeping\n",
		get_time() - start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->m_print);
	usleep(philo->tt_sleep * 1000);
	return (true);
}

bool	ft_think(t_philo *philo, unsigned long start_time)
{
	long	tt_think;

	if (!safe_mutex_lock(philo, &philo->m_philo))
		return (false);
	tt_think = (philo->tt_die
			- ((get_time() - philo->last_meal) - philo->tt_eat));
	pthread_mutex_unlock(&philo->m_philo);
	if (!safe_mutex_lock(philo, &philo->data->m_print))
		return (false);
	printf("%zu %d is thinking\n",
		get_time() - start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->m_print);
	if (tt_think > 0)
		usleep(tt_think);
	return (true);
}

void	ft_die(t_philo *philo, unsigned long start_time)
{
	pthread_mutex_lock(&philo->m_philo);
	philo->is_dead = true;
	pthread_mutex_unlock(&philo->m_philo);
	pthread_mutex_lock(&philo->data->m_print);
	printf("%zu %d died\n", get_time() - start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	*routine(void *args)
{
	unsigned long	start_time;
	t_philo			*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->data->m_data);
	start_time = philo->data->start_time;
	if (philo->data->nb_philo == 1)
	{
		usleep(philo->tt_die * 1000);
		ft_die(philo, start_time);
		pthread_mutex_unlock(&philo->data->m_data);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->data->m_data);
	philo->last_meal = get_time();
	while (1)
	{
		if (!ft_eat(philo, start_time))
			break ;
		if (!ft_sleep(philo, start_time))
			break ;
		if (!ft_think(philo, start_time))
			break ;
	}
	return (NULL);
}
