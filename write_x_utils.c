#include "libftprintf.h"

unsigned int	ft_divider_x(unsigned int c)
{
	unsigned int	divider;

	divider = 1;
	while (c > 15)
	{
		c /= 16;
		divider *= 16;
	}
	return (divider);
}

void			ft_putnbr_x(unsigned int n, s_line line)
{
	unsigned int	div;
	char			c;

	div = ft_divider_x(n);
	while (div)
	{
		c = (n / div);
		if (c < 10)
			c += '0';
		else if (c >= 10 && line.type == 'X')
			c += 55;
		else if (c >= 10 && line.type == 'x')
			c += 87;
		else
			break ;
		write(1, &c, 1);
		n -= (n / div) * div;
		div /= 16;
	}
}
