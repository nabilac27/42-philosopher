/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:17:15 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/22 04:10:25 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_table(&table, argv);
		init_table(&table);
		dinner(&table);
		// clean_table(&table); // TO-DO
	}
	else
		error_msg("ERROR: Invalid number of arguments");
	return (0);
}

/*
	Your program(s) must take the following arguments:
		1. number_of_philosophers
		2. time_to_die
		3. time_to_eat
		4. time_to_sleep
		5. number_of_times_each_philosopher_must_eat
*/

/*
	TO_DO: Think, Sleep, Monitor, Deadlock
	include/
    	philo.h
	src/
    	parse_table/
        	clean_table.c
        	parse_table.c
    	init_table/
        	init_table.c
        	handle_mutex.c
    	dinner/
        	dinner.c
			dinner_monitor.c
        	dinner_utils.c
        	handle_thread.c
        	handle_thread_utils.c
	main.c
*/

/*
	
*/