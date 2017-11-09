/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 13:28:06 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/18 19:20:00 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_digcount(int nbr)
{
	int		len;

	if (nbr == 0)
		return (1);
	len = 0;
	if (nbr < 0)
		len++;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char				*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	temp;

	len = ft_digcount(n);
	if (!(str = (char*)ft_strnew(len)))
		return (NULL);
	temp = n;
	if (n < 0)
		temp *= -1;
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	while (--len >= 0 && temp != 0)
	{
		str[len] = (temp % 10) + '0';
		temp /= 10;
	}
	return (str);
}
