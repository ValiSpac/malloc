/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:12:01 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/29 16:12:11 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *s, int c, size_t n)
{
	char	byte;

	byte = (char) c;
	while (*s && *s != byte && n)
	{
		s++;
		n--;
	}
	if (*s == byte)
		return ((char *)s);
	return (0);
}
