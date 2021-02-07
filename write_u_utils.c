#include "libftprintf.h"

unsigned int	ft_divider_u(unsigned int c)
{
	unsigned int	divider;

	divider = 1;
	while (c > 9)
	{
		c /= 10;
		divider *= 10;
	}
	return (divider);
}

void			ft_putnbr_u(unsigned int n)
{
	unsigned int	new_n;
	unsigned int	div;
	char			c;

	new_n = (long long int)n;
	if (new_n < 0)
	{
		write(1, "-", 1);
		new_n = new_n * (-1);
	}
	div = ft_divider_u(new_n);
	while (div)
	{
		c = (new_n / div) + '0';
		write(1, &c, 1);
		new_n -= (new_n / div) * div;
		div /= 10;
	}
}
