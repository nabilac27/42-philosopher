/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 07:41:47 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 08:52:30 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos,
		int num_philos)
{
	// Normal assignment: left = current, right = next
	philo->left_fork = &forks[philo_pos];
	philo->right_fork = &forks[(philo_pos + 1) % num_philos];
	// Deadlock prevention: even philosophers pick right fork firs
	if (philo->philo_id % 2 == 0)
	{
		philo->left_fork = &forks[(philo_pos + 1) % num_philos];
		philo->right_fork = &forks[philo_pos];
	}
}

void	init_philo_struct(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->num_philos)
	{
		philo = &table->philos[i];
		philo->philo_id = i + 1;
		philo->is_full = false;
		philo->count_eaten_meals = 0;
		philo->table = table;
		handle_mutex(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i, table->num_philos);
		i++;
	}
}
