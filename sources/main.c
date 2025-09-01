/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:55:50 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/01 14:30:19 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	int		i;
	t_data	*data;
	t_philo **philo_tab;
	
	if (ac < 5 || ac > 6 || !check_args(av))
		return(wrong_usage(), 1);
	data = init_data_struct(av);
	printf("main: log 1\n");
	philo_tab = (t_philo **)malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo_tab)
		return (free(data), 1);
	i = 0;
	printf("main: log 2\n");
	while (i < data->nb_philo)
	{
		philo_tab[i] = init_philo_struct(data, i);
		i++;
	}
	i = 0;
	printf("main: log 3\n");
	while (i < data->nb_philo)
	{
		if (pthread_create(&philo_tab[i]->thread, NULL, routine, (void *)philo_tab[i]))
		{
			if (i > 0)
				i--;
			data->run_sim = true;
			while (i >= 0)
			{
				pthread_join(philo_tab[i]->thread, NULL);
				i--;
			}
			return (free_philo_tab(philo_tab, data->nb_philo), free(data), 1);
		}
		i++;
	}
	printf("main: log 4\n");
	data->run_sim = true;
	while (data->run_sim)
		continue;
	i = 0;
	printf("main: log 5\n");
	while (i < data->nb_philo)
	{
		pthread_join(philo_tab[i]->thread, NULL);
		i++;
	}
	printf("main: log 6\n");
	return (free_philo_tab(philo_tab, data->nb_philo), free(data), 0);
}
