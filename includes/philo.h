/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:54:59 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/22 12:04:25 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	bool			is_eating;
	bool			is_sleeping;
	bool			is_thinking;
	bool			is_dead;
	bool			fork_left;
	bool			fork_right;
	struct s_philo	*prev;
	struct s_philo	*next;
}	t_philo;

typedef struct s_data
{
	int		nb_philo;
	int		tt_die;
	int		tt_eat;
	int		tt_sleep;
	int		satiated;
	t_philo	*philo_lst;
}	t_data;

void	philo_lst_add(t_philo **lst, t_philo *new);
void	init_data_struct(t_data **data, char **args);
t_philo	*init_philo_node(t_data **data);

#endif