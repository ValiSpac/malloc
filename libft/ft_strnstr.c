/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:50:12 by vpac              #+#    #+#             */
/*   Updated: 2022/11/22 15:06:34 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	j;

	if (n == 0 && !str1)
		return (0);
	if (!ft_strncmp((char *)str2, "", 1))
		return ((char *)str1);
	i = 0;
	while (str1[i] && i < n)
	{
		j = 0;
		while (str1[i + j] == str2[j] && (i + j) < n)
		{
			j++;
			if (!str2[j])
				return ((char *)str1 + i);
		}
		i++;
	}
	return (0);
}
