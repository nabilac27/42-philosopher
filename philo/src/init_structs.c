/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:28:30 by nchairun          #+#    #+#             */
/*   Updated: 2025/07/25 22:32:36 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* TO-DO:
    - Init mutexes (forks)
    - Init philoso
    - Thread routine(eat, sleep, think loop)
 */

 t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!(table))
		return (NULL);
        
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
    
	table->num_must_meals = -1;
    if (argc == 6)
		table->num_must_meals = ft_atoi(argv[5]);
        
	return (table);
}