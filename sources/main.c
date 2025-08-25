/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:55:50 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/22 15:44:11 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	create_philo_list(t_data *data)
{
	int	i;
	t_philo *new_philo;

	i = 0;
	while (i < data->nb_philo)
	{
		
	}
}

int	main(int ac, char **av)
{
	pthread_t	tid;
	t_data		*data;
	
	if (ac < 5 || ac > 6)
		return(0);
	init_data_struct(&data, av);
	create_philo_list(data);
	printf("bonjour\n");
	return (0);
}