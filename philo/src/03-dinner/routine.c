/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:28:04 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/22 02:49:47 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
	1. wait alll philos
	2. sychnronize all
	3. endless loop philo
*/
void	*routine_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

    // spinlock
	wait_all_threads(philo->table); // TO-DO;

	// synchro with monitor
    dinner_monitor(&data);
    
	// increase table variable coutner, with all threads running

	// set last meal time
	while (!(sim_finished(philo->table)))
	{
		if (philo->full_meals) // to-do: thread safe?
			break;

		eat(philo);
		print_status(philo, SLEEP);
		usleep_micro(philo->table->time_to_sleep);
		think(philo);
	}
	return (NULL);
}

void eat(t_philo *philo)
{
	// 1
	handle_mutex(&philo->left_fork->fork, LOCK);
	print_status(philo, TAKE_LEFT_FORK);
	handle_mutex(&philo->right_fork->fork, LOCK);
	print_status(philo, TAKE_RIGHT_FORK);

	// 2
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	philo->count_eaten_meals++;
	print_status(philo, EAT);
	usleep_micro(philo->table->time_to_eat);

	if((philo->table->num_must_meals > 0 && philo->count_eaten_meals) == philo->table->num_must_meals)
		set_bool(&philo->philo_mutex, &philo->full_meals, true);

	// 3
	handle_mutex(&philo->left_fork->fork, UNLOCK);
	handle_mutex(&philo->right_fork->fork, UNLOCK);
}

void think(t_philo *philo)
{
	print_status(philo, THINK);
}

void    *dinner_monitor(void *data)
{
    int     i;
    t_table *table;

    table = (t_table *)data;
    
    // make sure all philo runs
    // spinlock untill all thread run
    while (!all_threads_running(&table->table_mutex, &table->num_threads_running, table->num_philos))
    // }       to-do
    
    // check time to die constantly
    while (!sim_finished(table))
    {
        i = 0;
        while (i++ < table->num_must_meals && !sim_finished(table))
        {
            if (dead_philo(table->philos + i)) // TO-DO
            {
                set_bool(&table->table_mutex, &table->end_sim, true);
                print_status(DEAD, table->philos + i);
            }
        }
    }
}