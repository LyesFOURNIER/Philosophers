/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:09:26 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/01 14:49:26 by lfournie         ###   ########.fr       */
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
	philo->min_to_eat = data->min_to_eat;
	philo->nb_of_meal = 0;
	pthread_mutex_init(&philo->philo_data, NULL);
	philo->data = data;
	return (philo);
}

t_data	*init_data_struct(char **args)
{
	t_data *data;
	int		i;
	
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return(NULL);
	i = 0;
	data->nb_philo = ft_atoi(args[1]);
	data->tt_die = ft_atoi(args[2]);
	data->tt_eat = ft_atoi(args[3]);
	data->tt_sleep = ft_atoi(args[4]);
	if (args[5])
		data->min_to_eat = ft_atoi(args[5]);
	else
		data->min_to_eat = -1;
	data->run_sim = false;
	data->satiated = 0;
	pthread_mutex_init(&data->data, NULL);
	pthread_mutex_init(&data->print, NULL);
	data->forks = (pthread_mutex_t	*)malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return(free(data), NULL);
	while (i < data->nb_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	return (data);
}
