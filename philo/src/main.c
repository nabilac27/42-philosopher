/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:17:15 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 07:58:16 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char *argv[])
{
    t_table table;

    if (argc == 5 || argc == 6)
    {
		parse(&table, argc, argv);
        init_table_struct(&table);

        // // 3️⃣ Start philosopher threads
        // init_philo_threads(&table);

        // // 4️⃣ Start monitor thread
        // start_monitor_thread(&table);

        // // 5️⃣ Wait for all philosopher threads to finish
        // wait_all_philo_threads_finish(&table);

        // // 6️⃣ Wait for monitor thread to finish
        // wait_monitor_thread_finish(&table);

        // // 7️⃣ Clean up resources: destroy mutexes, free memory
        // clean(&table);
    }
    else
        error_msg("ERROR: Invalid Arguments");
    return (0);
}
