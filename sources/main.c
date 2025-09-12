/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:55:50 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/10 13:34:06 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->monitor, NULL, m_routine, (void *)data))
		return (-1);
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo_tab[i]->thread, NULL,
				routine, (void *)data->philo_tab[i]))
			return (i);
		i++;
	}
	return (-2);
}

int	main(int ac, char **av)
{
	int		i;
	t_data	*data;

	if (ac < 5 || ac > 6 || !check_args(av))
		return (wrong_usage(), 1);
	if (atoi(av[1]) == 0 || (av[5] && atoi(av[5]) == 0) )
		return (0);
	data = init_data_struct(av);
	if (!data)
		return (1);
	pthread_mutex_lock(&data->m_data);
	i = create_threads(data);
	if (!are_threads_created(data, i))
		return (1);
	pthread_mutex_unlock(&data->m_data);
	return (free_all(data, 1, 1, 1), 0);
}
