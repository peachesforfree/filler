/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:22:34 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/20 23:22:40 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s1, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	if (!(sub = (char*)malloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		sub[i] = s1[start];
		start++;
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
