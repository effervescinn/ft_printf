/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:46:06 by lnorcros          #+#    #+#             */
/*   Updated: 2021/02/08 18:46:08 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	parse_perc(const char **format, int *r_l)
{
	while (**format == '%' && *((*format) + 1) == '%')
	{
		*r_l += write(1, "%", 1);
		(*format) += 2;
	}
}

void	rep_perc(const char **format, t_line *line, int *r_l, va_list *ap)
{
	(*format)++;
	while (!ft_isalpha(**format) && **format)
	{
		check_flags(format, line);
		if (is_num(**format))
		{
			(*line).width = ft_atoi(*format);
			while (is_num(**format))
				(*format)++;
		}
		pars_w_p(format, line, ap);
		if (**format != '*' || **format != '.' || !(is_num(**format)))
			break ;
	}
	(*line).type = **format;
	check_type(r_l, *line, ap);
}

void	check_flags(const char **str, t_line *line)
{
	while ((**str == '0' || **str == '-') && **str)
	{
		if (**str == '0')
		{
			line->null_flag = 1;
			while (**str == '0' && **str)
				(*str)++;
		}
		if (**str == '-')
		{
			line->minus = 1;
			while (**str == '-' && **str)
				(*str)++;
		}
		if (!(**str == '0' || **str == '-'))
			return ;
	}
}

void	pars_w_p(const char **format, t_line *line, va_list *ap)
{
	if (**format == '*')
	{
		(*line).width = va_arg(*ap, int);
		(*format)++;
	}
	if (**format == '.')
	{
		(*format)++;
		(*line).precision_p = 'y';
		if (is_num(**format) || **format == '-')
		{
			(*line).precision = ft_atoi(*format);
			(*line).precision_d = 'y';
			while (is_num(**format) || **format == '-')
				(*format)++;
		}
		else if (**format == '*')
		{
			(*line).precision = va_arg(*ap, int);
			(*line).precision_p = 'y';
			(*line).precision_d = 'y';
			(*format)++;
		}
	}
}

void	check_type(int *r_len, t_line line, va_list *ap)
{
	if (line.type == 'd' || line.type == 'i')
		*r_len += write_d(ap, line);
	else if (line.type == 'u')
		*r_len += write_u(ap, line);
	else if (line.type == 'c')
		*r_len += write_c(ap, line);
	else if (line.type == 's')
		*r_len += write_s(ap, line);
	else if (line.type == 'x' || line.type == 'X')
		*r_len += write_x(ap, line);
	else if (line.type == 'p')
		*r_len += write_p(ap, line);
	else if (line.type == '%')
		*r_len += write_perc(line);
}
