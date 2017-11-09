/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dintarray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 15:27:36 by sbalcort          #+#    #+#             */
/*   Updated: 2017/07/17 15:36:31 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		**ft_2dintarray(size_t x, size_t y)
{
	int		**array;
	size_t	i;

	i = 0;
	array = ft_memalloc(sizeof(int *) * (y + 1));
	while (i <= y)
	{
		if (!(array[i] = ft_memalloc(sizeof(int) * x)))
		{
			ft_freearr((void**)array);
			return (NULL);
		}
		i++;
	}
	array[y + 1] = NULL;
	return (array);
}
