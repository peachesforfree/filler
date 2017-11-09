/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 11:40:32 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/18 19:02:37 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *big, const char *little)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strlen(little) == 0)
		return ((char*)big);
	while (big[i] != '\0')
	{
		while (little[j] == big[i + j])
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
