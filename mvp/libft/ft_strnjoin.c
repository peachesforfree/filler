/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:02:35 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/19 23:48:47 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnjoin(char const *s1, char const *s2, int i)
{
	char *string;

	string = ft_strjoin(s1, s2);
	if (i == 1 || i == 3)
	{
		free((void*)s1);
		s1 = NULL;
	}
	else if (i == 2 || i == 3)
	{
		free((void*)s2);
		s2 = NULL;
	}
	return ((char*)string);
}
