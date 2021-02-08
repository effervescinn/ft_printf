/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:45:56 by lnorcros          #+#    #+#             */
/*   Updated: 2021/02/08 18:45:58 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	set_line(t_line *line, int *r_l, const char **format)
{
	(*line).precision = 1;
	(*line).precision_p = 'n';
	(*line).precision_d = 'n';
	(*line).minus = 0;
	(*line).width = 0;
	(*line).null_flag = 0;
	while (**format != '%' && **format)
	{
		*r_l += write(1, &(**format), 1);
		(*format)++;
	}
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	t_line	line;
	int		return_length;

	va_start(ap, format);
	return_length = 0;
	while (*format)
	{
		set_line(&line, &return_length, &format);
		if (*format == '%')
		{
			parse_perc(&format, &return_length);
			if (*format == '%')
			{
				rep_perc(&format, &line, &return_length, &ap);
				if (!(*format))
					va_end(ap);
				if (!(*format))
					return (return_length);
				format++;
			}
		}
	}
	va_end(ap);
	return (return_length);
}
