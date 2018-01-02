/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 11:40:32 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/18 18:56:12 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (ft_strlen(little) == 0)
		return ((char*)big);
	while (big[i] != '\0' && i != (int)len)
	{
		while (little[j] == big[i + j] && ((i + j) != (int)len))
		{
			if (little[j + 1] == '\0')
				return ((char*)(big + i));
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
