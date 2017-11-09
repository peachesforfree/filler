/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:02:35 by sbalcort          #+#    #+#             */
/*   Updated: 2017/03/19 23:48:47 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float			ft_pow(int i, int j)
{
	double		number;
	int			exponent;

	number = i;
	exponent = j;
	if (j == 0 || i == 0)
		return (1);
	if (exponent < 0)
		exponent *= -1;
	exponent--;
	while (exponent > 0)
	{
		number *= i;
		exponent--;
	}
	if (number > 2147483647 || number < -2147483647)
		return (0);
	if (j < 0)
		return (1 / number);
	return (number);
}
