/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-rosa <mde-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:27:10 by mde-rosa          #+#    #+#             */
/*   Updated: 2021/10/05 19:40:11 by mde-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_check(const char *str)
{
	unsigned long long int	j;
	unsigned long long int	num;
	int						sign;

	sign = 1;
	j = 0;
	num = 0;
	while (*str >= 8 && *str <= 32)
	{
		if (*str == 27)
			return (0);
		str++;
	}
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*(str + j) >= 48 && *(str + j) <= 57)
		num = num * 10 + (unsigned long long int)(*(str + j++) - '0');
	return (ft_check(num, sign));
}

int	ft_check(unsigned long pt, int s)
{
	if (pt > 9223372036854775807 && s == -1)
		return (0);
	else if (pt > 2147483647)
		return (OFLOW);
	return (pt * s);
}

int	ft_is_number(char *string)
{
	int	i;

	i = 0;
	while (string[i] != EOL)
	{
		if (string[i] < '0' || string[i] > '9')
			return (ERROR);
		i++;
	}
	return (GOOD);
}
