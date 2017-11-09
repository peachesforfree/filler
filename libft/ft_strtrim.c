/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 13:06:22 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/21 00:04:11 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*rs;
	int		start;
	int		end;
	char	*str;

	if (!s)
		return (ft_strnew(0));
	str = (char*)s;
	start = 0;
	while (ft_isspace(&str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (ft_isspace(&str[end]))
		end--;
	if (end <= 0)
		return (ft_strnew(0));
	rs = ft_strsub(str, start, (end - start) + 1);
	return ((char*)rs);
}
