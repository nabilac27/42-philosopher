/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:28:31 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/20 05:32:06 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void handle_thread(pthread_t *thread, void *(*foo)(void *), void *data, t_thread_type *type)
{
    if (type == CREATE)
        pthread_create((thread, NULL, foo, data), type);
}