/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:19:44 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 09:02:53 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*handle_malloc(size_t bytes)
{
	void	*ret_value;

	ret_value = malloc(bytes);
	if (ret_value == NULL)
		error_msg("ERROR: malloc failed");
	return (ret_value);
}

void handle_mutex(t_mutex *mutex, t_mutex_type type)
{
    int status;

    status = 0;
    if (type == INIT)
        status = pthread_mutex_init(mutex, NULL);
    else if (type == LOCK)
        status = pthread_mutex_lock(mutex);
    else if (type == UNLOCK)
        status = pthread_mutex_unlock(mutex);
    else if (type == DESTROY)
        status = pthread_mutex_destroy(mutex);
    else
        error_msg("ERROR: handle_mutex - invalid type");

    if (status != 0)
        error_msg("ERROR: mutex operation failed");
}
