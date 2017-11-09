/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 15:41:04 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/18 18:59:01 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *chr;

	if (n != 0)
	{
		chr = (unsigned char*)s;
		while (n != 0)
		{
			if (*chr == (unsigned char)c)
				return ((void*)chr);
			n--;
			chr++;
		}
	}
	return (NULL);
}
