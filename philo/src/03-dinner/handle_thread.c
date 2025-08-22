/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:28:31 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/22 03:37:34 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void handle_thread(pthread_t *thread, void *(*foo)(void *), void *data, t_thread_type *type)
{
    if (*type == CREATE)
        handle_thread_status(pthread_create(thread, NULL, foo, data), type);
    else if (*type == JOIN)
        handle_thread_status(pthread_join(*thread, NULL), type);
    else if (*type == DETACH)
        handle_thread_status(pthread_detach(*thread), type);
    else
        error_msg("ERROR: handle_thread");
}

void handle_thread_status(int status, t_thread_type  *type)
{
    if (status == 0)
        return;
    
    printf("Thread error: status=%d, type=%d\n", status, *type);
    
    if (status == EAGAIN)
        error_msg("ERROR: handle_thread - EAGAIN (insufficient resources)");
    else if (status == EPERM)
        error_msg("ERROR: handle_thread - EPERM (permission denied)");
    else if (status == EINVAL && *type == CREATE)
        error_msg("ERROR: handle_thread - EINVAL CREATE (invalid attributes)");
    else if (status == EINVAL && (*type == JOIN || *type == DETACH))
        error_msg("ERROR: handle_thread - EINVAL JOIN/DETACH (thread not joinable)");
    else if (status == ESRCH)
        error_msg("ERROR: handle_thread - ESRCH (thread not found)");
    else if (status == EDEADLK)
        error_msg("ERROR: handle_thread - EDEADLK (deadlock detected)");
    else
    {
        printf("Unknown thread error: status=%d, type=%d\n", status, *type);
        error_msg("ERROR: handle_thread - unknown error");
    }
}

bool	is_all_threads_running(t_mutex *fork, long num_philos, long *threads)
{
	bool	ret;

	ret = false;
	handle_mutex(fork, LOCK);
	if (*threads == num_philos)
		ret = true;
	handle_mutex(fork, UNLOCK);
	return (ret);
}


void    wait_all_threads(t_table *table)
{
    while(!(get_bool(&table->table_mutex, &table->threads_ready)))
    ;
}
