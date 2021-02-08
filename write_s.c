/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:47:42 by lnorcros          #+#    #+#             */
/*   Updated: 2021/02/08 18:47:44 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

void	check_s(t_line *line, char **str, int *str_w, int *f_len)
{
	if ((*line).precision < 0)
	{
		(*line).precision = 0;
		(*line).precision_p = 'n';
	}
	if ((*line).width < 0)
	{
		(*line).width *= -1;
		(*line).minus = 1;
	}
	if (!(*str))
		*str = "(null)";
	*str_w = ft_strlen(*str);
	if ((*line).precision_p == 'y' && (*line).precision_d == 'n')
		(*line).precision = 0;
	else if ((*line).precision_p == 'n')
		(*line).precision = *str_w;
	*f_len = 0;
	if ((*line).precision <= *str_w)
		*str_w = (*line).precision;
}

void	minus_s(t_line *line, char **str, int *str_w, int *f_len)
{
	if ((*line).minus == 0)
	{
		while (((*line).width)-- > *str_w)
			*f_len += write(1, " ", 1);
		while ((*str_w)--)
		{
			*f_len += write(1, *str, 1);
			(*str)++;
		}
	}
	else
	{
		while ((*str_w)--)
		{
			*f_len += write(1, *str, 1);
			(*str)++;
			((*line).width)--;
		}
		while ((*line).width-- > 0)
			*f_len += write(1, " ", 1);
	}
}

int		write_s(va_list *ap, t_line line)
{
	int		string_width;
	char	*string;
	int		final_length;

	string = va_arg(*ap, char *);
	check_s(&line, &string, &string_width, &final_length);
	minus_s(&line, &string, &string_width, &final_length);
	return (final_length);
}
