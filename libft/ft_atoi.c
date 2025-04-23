/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:25:32 by vpac              #+#    #+#             */
/*   Updated: 2022/11/24 12:50:31 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				neg;
	int				i;
	long long int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		neg *= -1;
	if (str[i] == '-' || str[i] == '+')
		i ++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if ((num * neg) > LLONG_MAX)
			return (-1);
		else if ((num * neg) < LLONG_MIN)
			return (0);
		else
			num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}
