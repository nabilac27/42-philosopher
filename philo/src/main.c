/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:17:15 by nchairun          #+#    #+#             */
/*   Updated: 2025/07/25 22:24:53 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
    Your program(s) must take the following arguments:
        1. number_of_philosophers  
        2. time_to_die 
        3. time_to_eat 
        4. time_to_sleep 
        5. number_of_times_each_philosopher_must_eat
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
int main(int argc, char *argv[])
{
    t_table *table;
    
    if (!(argc == 5 || argc == 6) || !(check_valid_args(argc, argv))) 
        return(1);

    table = init_table(argc, argv);
    if (!(table))
		return(1);
    printf("Philosopher! \n");
    	printf("Initialized: %d philos\n", table->num_philos);
    free(table);
    return(0);
}