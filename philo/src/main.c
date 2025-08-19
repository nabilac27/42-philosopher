/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:17:15 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/19 18:00:50 by nchairun         ###   ########.fr       */
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

// int main(int argc, char *argv[])
// {
//     t_table *table;
    
//     if (!(argc == 5 || argc == 6) || !(check_valid_args(argc, argv))) 
//         return(1);
//     table = setup_table(argc, argv);
//     if (!(table))
// 		return(1);
//     setup_thread(table);
//     return(0);
// }

int main(int argc, char *argv[])
{
    if (argc == 5 || argc == 6)
	{
		parse_args(argc, argv); // TO-DO
		init_data(argc, argv); // TO_DO
		start_sim(argc, argv); // TO-DO
		clean(argc, argv); // TO-DO
	}
	else
		exit(1);
	return(0);
}
