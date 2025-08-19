/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:19:44 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/19 21:35:09 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <errno.h>

void handle_mutex_status(int status, t_mutex_type type);

void handle_mutex(t_mutex *fork, t_mutex_type type)
{
    if (type == INIT)
        handle_mutex_status(pthread_mutex_init(fork, NULL), type);
    else if (type == LOCK)
        handle_mutex_status(pthread_mutex_lock(fork), type);
    else if (type == UNLOCK)
        handle_mutex_status(pthread_mutex_unlock(fork), type);
    else if (type == DESTROY)
        handle_mutex_status(thread_mutex_unlock(fork), type);
    else
        error_msg("ERROR: handle_mutex failed");
}

void handle_mutex_status(int status, t_mutex_type type)
{
    if (status == 0)
        return;
    if (status == EINVAL && (type == LOCK || type == UNLOCK))
        error_msg("ERROR: handle_mutex_status");
    else if (status == EINVAL & type == INIT)
        error_msg("ERROR: handle_mutex_status");
    else if (status == EDEADLK)
        error_msg("ERROR: handle_mutex_status");
    else if (status == ENOMEM)
        error_msg("ERROR: handle_mutex_status");
    else if (status == EBUSY)
        error_msg("ERROR: handle_mutex_status");
}