/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 13:12:50 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/18 19:04:20 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;
	size_t			i;

	i = 0;
	dest = (unsigned char*)dst;
	source = (unsigned char*)src;
	if (source < dest)
		while ((int)--len >= 0)
		{
			*(dest + len) = *(source + len);
		}
	else
		while (i < len)
		{
			*(dest + i) = *(source + i);
			i++;
		}
	return (dest);
}
