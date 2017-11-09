/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 13:45:03 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/18 18:58:15 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	size_t	len;
	char	*temp;

	len = ft_strlen(s1) + 1;
	if (!(temp = (char *)malloc(len)))
		return (NULL);
	ft_strcpy(temp, s1);
	return (temp);
}
