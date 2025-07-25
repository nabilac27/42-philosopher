/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:01:19 by nchairun          #+#    #+#             */
/*   Updated: 2025/07/25 22:23:03 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool check_valid_args(int argc, char *argv[])
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!(ft_atoi(argv[i])))
			return(false);
		i++;
	}
	return(true);
}

int	ft_atoi(char *str)
{
	int	i;
	int	negative;
	long long	result;

	i = 0;
	negative = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -1 * negative;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (str[i] - '0') + (result * 10);
		i++;
	}
	if (result < INT_MIN || result > INT_MAX)
		return (0);
	return ((int)result * negative);
}
