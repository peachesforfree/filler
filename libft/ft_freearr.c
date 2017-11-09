/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freearr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:33:52 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/08 20:46:35 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_freearr(void **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		ft_bzero(array[i], sizeof(array[i]));
		free(array[i]);
	}
	return (0);
}
