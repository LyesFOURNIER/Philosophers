/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:24:40 by lfournie          #+#    #+#             */
/*   Updated: 2025/09/02 16:08:15 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philo_tab(t_philo **ptab, int size)
{
	int	i;
	
	i = 0;
	while (i < size)
	{
		free(ptab[i]);
		//needs to destroy mutexes
		i++;
	}
	free(ptab);
}

void	free_forks_tab(pthread_mutex_t	*ftab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		//needs to destroy mutexes
		i++;
	}
	free(ftab);
}

void	join_thread(t_data *data, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_join(data->philo_tab[i]->thread, NULL);
		i++;
	}
}

void	free_all(t_data *data, int fr_thrd, int fr_ph, int fr_frk)
{
	int	i;

	if (data->free_size == -1)
		i = data->nb_philo;
	else
		i = data->free_size;
	if (fr_thrd)
		join_thread(data, i);
	if (fr_ph)
		free_philo_tab(data->philo_tab, i);
	if (fr_frk)
		free_forks_tab(data->forks, i);
	//needs to destroy mutexes
	free(data);
}
