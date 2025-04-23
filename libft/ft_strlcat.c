/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:03:43 by vpac              #+#    #+#             */
/*   Updated: 2022/11/22 15:04:26 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	dest_l;
	size_t	src_l;

	if (n == 0 && (!dst || !src))
		return (0);
	src_l = ft_strlen(src);
	dest_l = ft_strlen(dst);
	j = dest_l;
	i = 0;
	if (dest_l < n - 1 && n > 0)
	{
		while (src[i] && dest_l + i < n - 1)
		{
			dst[j] = src[i];
			j++;
			i++;
		}
		dst[j] = 0;
	}
	if (dest_l >= n)
		dest_l = n;
	return (dest_l + src_l);
}
