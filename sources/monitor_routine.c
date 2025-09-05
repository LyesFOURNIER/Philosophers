/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:44:10 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/05 16:47:46 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	m_subsubroutine(t_data *data, int i)
{
	pthread_mutex_lock(&data->m_data);
	pthread_mutex_lock(&data->philo_tab[i]->m_philo);
	if (data->philo_tab[i]->nb_of_meal >= data->min_to_eat)
		data->satiated++;
	if (data->philo_tab[i]->is_dead)
	{
		pthread_mutex_lock(&data->m_print);
		printf("%zu %d died\n", get_time() - data->start_time,
			data->philo_tab[i]->philo_id + 1);
		pthread_mutex_unlock(&data->m_print);
		data->is_running = false;
	}
	if (data->satiated >= data->nb_philo && data->min_to_eat != -1)
		data->is_running = false;
	pthread_mutex_unlock(&data->philo_tab[i]->m_philo);
	pthread_mutex_unlock(&data->m_data);
}

void	m_subroutine(t_data *data, int i, int nb)
{
	while (1)
	{
		i = 0;
		while (i < nb)
		{
			m_subsubroutine(data, i);
			i++;
		}
		pthread_mutex_lock(&data->m_data);
		if (!data->is_running)
		{
			pthread_mutex_unlock(&data->m_data);
			break ;
		}
		pthread_mutex_unlock(&data->m_data);
	}
}

void	*m_routine(void *args)
{
	t_data	*data;
	int		i;
	int		nb;

	data = (t_data *)args;
	pthread_mutex_lock(&data->m_data);
	nb = data->nb_philo;
	pthread_mutex_unlock(&data->m_data);
	i = 0;
	m_subroutine(data, i, nb);
	return (NULL);
}
