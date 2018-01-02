/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 13:45:03 by sbalcort          #+#    #+#             */
/*   Updated: 2017/11/10 21:52:01 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	size_t	len;
	char	*temp;

	len = ft_strlen(s1);
	if (!(temp = (char *)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	temp[len] = '\0';
	ft_strcpy(temp, s1);
	return (temp);
}
