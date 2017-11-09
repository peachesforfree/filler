/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 11:03:48 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/20 23:17:06 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char*))
{
	int i;
	int length;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	length = ft_strlen(s);
	while (i < length)
	{
		f(&s[i]);
		i++;
	}
}
