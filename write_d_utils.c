/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_d_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:47:32 by lnorcros          #+#    #+#             */
/*   Updated: 2021/02/08 18:47:34 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_divider(long long int c)
{
	long long int	divider;

	divider = 1;
	while (c > 9)
	{
		c /= 10;
		divider *= 10;
	}
	return (divider);
}

void	ft_putnbr(int n)
{
	long long int	new_n;
	long long int	div;
	char			c;

	new_n = (long long int)n;
	if (new_n < 0)
	{
		write(1, "-", 1);
		new_n = new_n * (-1);
	}
	div = ft_divider(new_n);
	while (div)
	{
		c = (new_n / div) + '0';
		write(1, &c, 1);
		new_n -= (new_n / div) * div;
		div /= 10;
	}
}
