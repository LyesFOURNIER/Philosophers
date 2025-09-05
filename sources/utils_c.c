/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:26:30 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/05 15:34:44 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	get_fork_even(t_philo *philo, unsigned long start_time)
{
	int	i;

	i = philo->philo_id;
	if (!safe_mutex_lock(philo, start_time, &philo->data->m_fork[i]))
		return (false);
	if (i < philo->data->nb_philo)
	{
		if (!safe_mutex_lock(philo, start_time,
				&philo->data->m_fork[i + 1]))
		{
			pthread_mutex_unlock(&philo->data->m_fork[i]);
			return (false);
		}
	}
	else if (i == philo->data->nb_philo)
	{
		if (!safe_mutex_lock(philo, start_time, &philo->data->m_fork[0]))
		{
			pthread_mutex_unlock(&philo->data->m_fork[i]);
			return (false);
		}
	}
	return (true);
}

bool	get_fork_uneven(t_philo *philo, unsigned long start_time)
{
	int	i;

	i = philo->philo_id;
	if (i > 0)
		if (!safe_mutex_lock(philo, start_time, &philo->data->m_fork[i - 1]))
			return (false);
	if (i == 0)
		if (!safe_mutex_lock(philo, start_time,
				&philo->data->m_fork[philo->data->nb_philo]))
			return (false);
	if (!safe_mutex_lock(philo, start_time, &philo->data->m_fork[i]))
	{
		if (i > 0)
		{
			pthread_mutex_unlock(&philo->data->m_fork[i - 1]);
			return (false);
		}
		else if (i == 0)
		{
			pthread_mutex_unlock(&philo->data->m_fork[philo->data->nb_philo]);
			return (false);
		}
	}
	return (true);
}

bool	get_fork(t_philo *philo, unsigned long start_time)
{
	int	i;

	i = philo->philo_id;
	if (i % 2 == 0)
	{
		if (!get_fork_even(philo, start_time))
			return (false);
	}
	else if (i % 2 == 1)
	{
		if (!get_fork_uneven(philo, start_time))
			return (false);
	}
	return (true);
}

void	put_down_forks(t_philo *philo)
{
	int	i;

	i = philo->philo_id;
	if (i % 2 == 0)
	{
		pthread_mutex_unlock(&philo->data->m_fork[i]);
		if (i < philo->data->nb_philo)
			pthread_mutex_unlock(&philo->data->m_fork[i + 1]);
		else if (i == philo->data->nb_philo)
			pthread_mutex_unlock(&philo->data->m_fork[0]);
	}
	else if (i % 2 == 1)
	{
		if (i > 0)
			pthread_mutex_unlock(&philo->data->m_fork[i - 1]);
		else if (i == 0)
			pthread_mutex_unlock(&philo->data->m_fork[philo->data->nb_philo]);
		pthread_mutex_unlock(&philo->data->m_fork[i]);
	}
}
