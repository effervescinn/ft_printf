#include "libftprintf.h"

int	write_c(va_list *ap, s_line line)
{
	char	c;
	int		final_length;

	c = va_arg(*ap, int);
	final_length = 1;
	if (line.width < 0)
		line.minus = 1;
	(line.width < 0) ? (line.width *= -1) : (line.width = line.width);
	if (line.minus == 1)
	{
		write(1, &c, 1);
		while (line.width && line.width > 1)
		{
			final_length += write(1, " ", 1);
			(line.width)--;
		}
		return (final_length);
	}
	while (line.width && line.width > 1)
	{
		final_length += write(1, " ", 1);
		(line.width)--;
	}
	write(1, &c, 1);
	return (final_length);
}
