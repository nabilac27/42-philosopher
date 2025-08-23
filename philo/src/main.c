/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:17:15 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 10:32:17 by nchairun         ###   ########.fr       */
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
		init_monitor_thread(&table);
		wait_all_philo_threads_finish(&table);
		wait_monitor_thread_finish(&table);
		clean(&table);
	}
	else
		error_msg("ERROR: Invalid Arguments");
	return (0);
}
