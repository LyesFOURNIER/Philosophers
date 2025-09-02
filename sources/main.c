/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:55:50 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/02 13:56:44 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_threads(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo_tab[i]->thread, NULL, routine, (void *)data->philo_tab[i]))
			return(i - 1);
		i++;
	}
	return (-2);
}

int	main(int ac, char **av)
{
	int		i;
	t_data	*data;
	
	if (ac < 5 || ac > 6 || !check_args(av))
		return(wrong_usage(), 1);
	if (atoi(av[1]) == 0)
		return(0);
	data = init_data_struct(av);
	if (!data)
		return(1);
	i = create_threads(data);
	if (i != -2)
	{
		if (i == -1)
			return(free_all(data, 0, 1, 1), 1);
		else
			return(join_thread(data, i), free_all(data, 0, 1, 1), 1);
	}
	data->run_sim = true;
	while (data->run_sim)
		continue;
	return (free_all(data, 1, 1, 1), 0);
}
