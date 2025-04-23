/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:56:49 by vpac              #+#    #+#             */
/*   Updated: 2023/03/18 16:04:39 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1)
		return (0);
	start = 0;
	while (s1[start] && char_in_set(s1[start], set))
		start ++;
	end = ft_strlen(s1);
	while ((end > start) && char_in_set(s1[end - 1], set))
		end--;
	i = 0;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (0);
	while (start < end)
	{
		str[i++] = s1[start];
		start ++;
	}
	str[i] = 0;
	return (str);
}
