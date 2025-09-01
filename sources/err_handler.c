/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:56:41 by lfournie          #+#    #+#             */
/*   Updated: 2025/08/27 11:23:40 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	check_args(char **args)
{
	if (atoi(args[1]) > 200 || atoi(args[1]) < 0)
		return(false);
	if (atoi(args[2]) < 0 || atoi(args[3]) < 0 || atoi(args[4]) < 0)
		return(false);
	if (args[5] && atoi(args[5]) < 0)
		return(false);
	return(true);
}

void	wrong_usage(void)
{
	printf("Usage: ./philo|Number of philosophers (>= 0 && <= 200)|");
	printf("Time to die in ms (>= 0)|");
	printf("Time to eat in ms (>= 0)|Time to sleep in ms (>= 0)|");
	printf("\n(optional)Minimum number of meal per philosopher (>= 0)\n");
}