/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 04:24:23 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/20 04:41:41 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// To avoid writing LOCK, UNLOCK everywhere

void	set_bool(t_mutex *fork, bool *dest, bool value)
{
    handle_mutex(fork, LOCK);
    *dest = value;
    handle_mutex(fork,UNLOCK);
}

bool	get_bool(t_mutex *fork, bool *value)
{
    bool    ret_value;
    
    handle_mutex(fork, LOCK);
    ret_value = *value;
    handle_mutex(fork, UNLOCK);
    return(ret_value);
}

long	get_long(t_mutex *fork, long *value)
{
    long    ret_value;

    handle_mutex(fork, LOCK);
    ret_value = *value;
    handle_mutex(fork, UNLOCK);
    return(ret_value);
}

void	set_long(t_mutex *fork, long *dest, long value)
{
    handle_mutex(fork, LOCK);
    *dest = value;
    handle_mutex(fork, UNLOCK);
}

bool	sim_finished(t_table *table)
{
    return(get_bool(&table->table_mutex, &table->end_sim));
}