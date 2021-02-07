#include "libftprintf.h"

unsigned long	ft_divider_p(unsigned long c)
{
	unsigned long	divider;

	divider = 1;
	while (c > 15)
	{
		c /= 16;
		divider *= 16;
	}
	return (divider);
}

void			ft_putnbr_p(unsigned long n, s_line line)
{
	unsigned long	div;
	char			c;

	div = ft_divider_p(n);
	write(1, "0", 1);
	write(1, "x", 1);
	while (div)
	{
		c = (n / div);
		if (c < 10 && !(n == 0 && line.precision_p == 'y'))
			c += '0';
		else if (c >= 10)
			c += 87;
		else
			break ;
		write(1, &c, 1);
		n -= (n / div) * div;
		div /= 16;
	}
}

void			minus_p(s_line *l, unsigned long *f, int dl, unsigned long *d)
{
	if ((*l).minus == 0)
	{
		while ((*l).width > dl && (*l).width > (*l).precision)
		{
			*f += write(1, " ", 1);
			((*l).width)--;
		}
		if ((*l).width != 0 && *d == 0 && (*l).precision == 0)
			write(1, " ", 1);
		if (!((*l).precision == 0 && d == 0))
			ft_putnbr_p(*d, (*l));
	}
	else
	{
		if (!((*l).precision == 0 && *d == 0))
			ft_putnbr_p(*d, (*l));
		if ((*l).width > dl && (*l).width > (*l).precision)
		{
			while ((*l).width > dl && (*l).width > (*l).precision)
			{
				*f += write(1, " ", 1);
				((*l).width)--;
			}
		}
	}
}

int				write_p(va_list *ap, s_line line)
{
	int				d_length;
	unsigned long	d_copy;
	unsigned long	d_copy_again;
	unsigned long	final_length;

	d_copy = va_arg(*ap, unsigned long);
	d_copy_again = d_copy;
	d_length = 2;
	if (d_copy == 0 && line.precision_p == 'n')
		d_length = 3;
	while (d_copy)
	{
		d_copy /= 16;
		d_length++;
	}
	final_length = d_length;
	minus_p(&line, &final_length, d_length, &d_copy_again);
	return (final_length);
}
