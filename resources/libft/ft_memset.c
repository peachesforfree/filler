/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:41:40 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/09 12:09:17 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*str;

	str = (unsigned char *)b;
	i = 0;
	if (len == 0)
		return (b);
	while (len > 0)
	{
		str[i] = (unsigned char)c;
		i++;
		len--;
	}
	return (b);
}
