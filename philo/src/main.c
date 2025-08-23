/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:17:15 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 10:08:18 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse(&table, argc, argv);
		init_table_struct(&table);
		init_philo_threads(&table);
		// Wait until all philosophers have incremented num_threads_ready
		while (table.num_threads_ready < table.num_philos)
			usleep(100);
		init_monitor_thread(&table);
		wait_all_philo_threads_finish(&table);
		wait_monitor_thread_finish(&table);
		clean(&table);
	}
	else
		error_msg("ERROR: Invalid Arguments");
	return (0);
}
