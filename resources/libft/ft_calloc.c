/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 22:39:45 by sbalcort          #+#    #+#             */
/*   Updated: 2017/11/03 02:20:35 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		**ft_calloc(size_t num_elem, size_t elem_size)
{
	void	**array;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (num_elem < 2 || elem_size < 1)
		return (0);
	if (!(array = (void**)malloc(sizeof(void *) * num_elem)))
		return (0);
	array[num_elem] = 0;
	while (num_elem)
	{
		if (!(array[i] = (void*)malloc(sizeof(void) * elem_size)))
		{
			ft_freearr(array);
			return (0);
		}
		ft_bzero(array[i], elem_size);
		i++;
		num_elem--;
	}
	array[i] = 0;
	return (array);
}
