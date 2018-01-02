/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:59:55 by sbalcort          #+#    #+#             */
/*   Updated: 2017/11/10 21:51:40 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	if (!(new = (char*)ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	ft_strcpy(new, s1);
	ft_strcat(new, s2);
	return ((char*)new);
}
