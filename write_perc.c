#include "libftprintf.h"

int	write_perc(s_line line)
{
	int	final_length;

	final_length = 1;
	if (line.minus == 1)
		line.null_flag = 0;
	if (line.minus == 0)
	{
		while ((line.width)-- > 1)
		{
			if (line.null_flag == 1)
				final_length += write(1, "0", 1);
			else
				final_length += write(1, " ", 1);
		}
		write(1, "%", 1);
		return (final_length);
	}
	write(1, "%", 1);
	while ((line.width)-- > 1)
		final_length += write(1, " ", 1);
	return (final_length);
}
