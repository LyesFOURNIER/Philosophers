/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:09:26 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/12 11:50:57 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		neg;
	int		nb;

	i = 0;
	neg = 1;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		i++;
		neg = -1;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
		if (!(nptr[i] >= '0' && nptr[i] <= '9'))
			return (nb * neg);
	}
	return (0);
}

t_philo	*init_philo_struct(t_data *data, int i)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_id = i;
	philo->is_dead = false;
	philo->tt_die = data->tt_die;
	philo->tt_eat = data->tt_eat;
	philo->tt_sleep = data->tt_sleep;
	philo->nb_of_meal = 0;
	philo->min_to_eat = data->min_to_eat;
	philo->satiated = false;
	philo->last_meal = data->start_time;
	pthread_mutex_init(&philo->m_philo, NULL);
	philo->data = data;
	return (philo);
}

int	create_philo_tab(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo_tab[i] = init_philo_struct(data, i);
		if (!data->philo_tab[i])
			return (i);
		i++;
	}
	return (-1);
}

bool	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->m_data, NULL);
	pthread_mutex_init(&data->m_print, NULL);
	data->m_fork = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->m_fork)
		return (false);
	while (i < data->nb_philo)
		pthread_mutex_init(&data->m_fork[i++], NULL);
	return (true);
}

t_data	*init_data_struct(char **args)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->nb_philo = ft_atoi(args[1]);
	data->tt_die = ft_atoi(args[2]);
	data->tt_eat = ft_atoi(args[3]);
	data->tt_sleep = ft_atoi(args[4]);
	if (args[5])
		data->min_to_eat = ft_atoi(args[5]);
	else
		data->min_to_eat = -1;
	data->satiated = 0;
	data->is_running = true;
	data->start_time = get_time();
	data->philo_tab = (t_philo **)malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo_tab)
		return (free(data), NULL);
	data->free_size = create_philo_tab(data);
	if (data->free_size != -1)
		return (free_all(data, 0, 1, 0), NULL);
	if (!init_mutexes(data))
		return (free_all(data, 0, 1, 0), NULL);
	return (data);
}
