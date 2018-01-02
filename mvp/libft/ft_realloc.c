/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 22:39:45 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/19 22:41:46 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc(void *src, size_t newsize)
{
	void	*new;

	if (!src)
		return (ft_memalloc(newsize));
	if (newsize <= sizeof(src))
		return (src);
	new = ft_memalloc(newsize);
	ft_memmove(src, new, sizeof(src));
	ft_bzero(src, sizeof(src));
	return ((void*)new);
}
