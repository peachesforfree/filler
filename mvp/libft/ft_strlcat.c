/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:32:36 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/20 00:00:34 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*cdst;
	const char	*csrc;
	size_t		i;
	size_t		dlen;

	cdst = dst;
	csrc = src;
	i = size;
	while (i-- != 0 && *cdst != '\0')
		cdst++;
	dlen = cdst - dst;
	i = size - dlen;
	if (i == 0)
		return ((size_t)(dlen + ft_strlen(csrc)));
	while (*csrc != '\0')
	{
		if (i != 1)
		{
			*cdst++ = *csrc;
			i--;
		}
		csrc++;
	}
	*cdst = '\0';
	return ((size_t)(dlen + (csrc - src)));
}
