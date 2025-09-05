/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:26:30 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/05 16:44:22 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_fork(t_philo *philo, unsigned long start_time, int i)
{
	if (!safe_mutex_lock(philo, &philo->data->m_print))
		return ;
	printf("%zu %d has taken a fork\n",
		get_time() - start_time, i + 1);
	pthread_mutex_unlock(&philo->data->m_print);
}

bool	get_fork_even(t_philo *philo, unsigned long start_time, int i)
{
	if (!safe_mutex_lock(philo, &philo->data->m_fork[i]))
		return (false);
	print_fork(philo, start_time, i);
	if (i < philo->data->nb_philo - 1)
	{
		if (!safe_mutex_lock(philo, &philo->data->m_fork[i + 1]))
		{
			pthread_mutex_unlock(&philo->data->m_fork[i]);
			return (false);
		}
	}
	else if (i == philo->data->nb_philo - 1)
	{
		if (!safe_mutex_lock(philo, &philo->data->m_fork[0]))
		{
			pthread_mutex_unlock(&philo->data->m_fork[i]);
			return (false);
		}
	}
	print_fork(philo, start_time, i);
	return (true);
}

bool	get_fork_uneven(t_philo *philo, unsigned long start_time, int i)
{
	if (i > 0)
		if (!safe_mutex_lock(philo, &philo->data->m_fork[i - 1]))
			return (false);
	if (i == 0)
		if (!safe_mutex_lock(philo,
				&philo->data->m_fork[philo->data->nb_philo]))
			return (false);
	print_fork(philo, start_time, i);
	if (!safe_mutex_lock(philo, &philo->data->m_fork[i]))
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
	print_fork(philo, start_time, i);
	return (true);
}

bool	get_fork(t_philo *philo, unsigned long start_time)
{
	int	i;

	i = philo->philo_id;
	if (i % 2 == 0)
	{
		if (!get_fork_even(philo, start_time, i))
			return (false);
	}
	else if (i % 2 == 1)
	{
		if (!get_fork_uneven(philo, start_time, i))
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
		if (i < philo->data->nb_philo - 1)
			pthread_mutex_unlock(&philo->data->m_fork[i + 1]);
		else if (i == philo->data->nb_philo - 1)
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
