/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:35:08 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/19 22:44:30 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// SPINLOCK to synchronize philos start

#include "../include/philo.h"

void    wait_all_threads(t_table *table)
{
    while(!(get_bool(&table->table_mutex, &table->threads_ready)))
    ;
}