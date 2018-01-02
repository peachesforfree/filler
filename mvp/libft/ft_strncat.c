/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 14:19:59 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/18 18:35:00 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strncat(char *s1, const char *s2, size_t n)
{
	char		*dst;
	const char	*src;

	dst = s1;
	src = s2;
	if (n == 0)
		return ((char*)s1);
	while (*dst != '\0')
		dst++;
	while (n > 0)
	{
		if ((*dst = *src) == '\0')
			break ;
		dst++;
		src++;
		n--;
	}
	*dst = '\0';
	return ((char*)s1);
}
