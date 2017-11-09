/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:50:32 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/14 16:01:24 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	char	cc;
	char	*str;
	int		i;
	int		len;

	len = ft_strlen(s);
	i = 0;
	cc = (char)c;
	str = (char*)s;
	while (i <= len)
	{
		if (str[i] == cc)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
