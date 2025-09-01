/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:24:40 by lfournie          #+#    #+#             */
/*   Updated: 2025/08/25 14:07:09 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philo_tab(t_philo **tab, int size)
{
	int	i;
	
	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}