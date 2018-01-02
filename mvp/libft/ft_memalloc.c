/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:49:39 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/18 18:35:25 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void	*str;

	if (!(str = (void*)malloc(size)))
		return (NULL);
	ft_bzero(str, size);
	return (str);
}
