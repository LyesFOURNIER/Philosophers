/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:09:26 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/22 15:16:46 by lfournie         ###   ########.fr       */
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

/* void	philo_lst_add(t_philo **lst, t_philo *new)
{
	t_philo	*head;
	t_philo	*cursor;

	if (!lst)
	{
		lst = new;
		new->prev = new;
		new->next = new;
	}
	else
	{
		head = lst;
		cursor = (*lst)->next;
		while (cursor->next != head)
			cursor = cursor->next;
		cursor->next = new;
		new->prev = cursor;
		new->next = head;
		head->prev = new;
	}
} */

t_philo	*init_philo_lst_node(int i)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->is_dead = false;
	philo->is_eating = false;
	philo->is_sleeping = false;
	philo->is_thinking = false;
	return (philo);
}

void	init_data_struct(t_data **data, char **args)
{
	(*data)->nb_philo = ft_atoi(args[1]);
	(*data)->tt_die = ft_atoi(args[2]);
	(*data)->tt_eat = ft_atoi(args[3]);
	(*data)->tt_sleep = ft_atoi(args[4]);
	if (args[5])
		(*data)->satiated = ft_atoi(args[5]);
	
}