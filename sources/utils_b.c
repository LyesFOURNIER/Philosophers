/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:47:59 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/05 15:33:50 by lfournie         ###   ########.fr       */
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

bool	safe_mutex_lock(t_philo *philo, unsigned long s_t, pthread_mutex_t *m)
{
	pthread_mutex_lock(&philo->data->m_data);
	if (!philo->data->is_running)
	{
		pthread_mutex_unlock(&philo->data->m_data);
		return (false);
	}
	pthread_mutex_unlock(&philo->data->m_data);
	if ((get_time() - philo->last_meal) >= philo->tt_die)
	{
		ft_die(philo, s_t);
		return (false);
	}
	pthread_mutex_lock(m);
	return (true);
}
