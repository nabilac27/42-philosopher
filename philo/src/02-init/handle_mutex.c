/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:19:44 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 07:55:33 by nchairun         ###   ########.fr       */
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

void	handle_mutex_status(int status, t_mutex_type type)
{
	(void)type;
	if (status == 0)
		return ;
	else
		error_msg("ERROR: handle_mutex_status");
}

void	handle_mutex(t_mutex *fork, t_mutex_type type)
{
	if (type == INIT)
		handle_mutex_status(pthread_mutex_init(fork, NULL), type);
	else if (type == LOCK)
		handle_mutex_status(pthread_mutex_lock(fork), type);
	else if (type == UNLOCK)
		handle_mutex_status(pthread_mutex_unlock(fork), type);
	else if (type == DESTROY)
		handle_mutex_status(pthread_mutex_destroy(fork), type);
	else
		error_msg("ERROR: handle_mutex failed");
}
