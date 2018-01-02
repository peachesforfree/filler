/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 19:00:39 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/09 16:50:18 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*cdst;
	unsigned char	*csrc;
	unsigned char	d;

	i = 0;
	cdst = (unsigned char*)dst;
	csrc = (unsigned char*)src;
	d = (unsigned char)c;
	while (n > 0)
	{
		cdst[i] = csrc[i];
		if (csrc[i] == d)
			return (&cdst[i + 1]);
		i++;
		n = n - 1;
	}
	return (NULL);
}
