/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 15:11:29 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/08 23:30:42 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int		len;
	char	cc;
	char	*str;

	str = (char*)s;
	cc = c;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (str[len] == c)
			return (&str[len]);
		len--;
	}
	return (NULL);
}
