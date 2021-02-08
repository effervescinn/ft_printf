/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:48:29 by lnorcros          #+#    #+#             */
/*   Updated: 2021/02/08 18:48:30 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			check_params_x(t_line *l, unsigned int d, int *d_l)
{
	if ((*l).width < 0)
	{
		(*l).minus = 1;
		(*l).width *= -1;
	}
	if ((*l).minus == 1)
		(*l).null_flag = 0;
	if ((*l).precision < 0 && (*l).null_flag == 1 && d == 0 && (*l).width == 0)
		(*l).precision = 1;
	else if ((*l).precision < 0 && (*l).null_flag == 1)
	{
		if (d < 0)
			(*l).precision = (*l).width - 1;
		else
			(*l).precision = (*l).width;
		(*l).null_flag = 0;
	}
	if ((*l).precision_p == 'y' && (*l).precision_d == 'n' && d == 0)
		(*l).precision = 0;
	if (d == 0 && (*l).precision != 0)
		*d_l = 1;
	else
		*d_l = 0;
}

void			minus_on_x(t_line *line, int d_l, int *f_l, unsigned int *d)
{
	int diff;

	if ((*line).precision > d_l && (*line).precision > d_l)
	{
		diff = (*line).precision - d_l;
		while (diff--)
			*f_l += write(1, "0", 1);
	}
	if (!((*line).precision == 0 && *d == 0))
		ft_putnbr_x(*d, *line);
	while ((*line).width > d_l && (*line).width > (*line).precision)
	{
		*f_l += write(1, " ", 1);
		((*line).width)--;
	}
}

void			check_idk_x(t_line *line, int d_l, int *f_l)
{
	if ((*line).null_flag == 1 && (*line).precision_p == 'n')
	{
		while ((*line).width > d_l && (*line).width > (*line).precision)
		{
			*f_l += write(1, "0", 1);
			((*line).width)--;
		}
		return ;
	}
	while ((*line).width > d_l && (*line).width > (*line).precision)
	{
		*f_l += write(1, " ", 1);
		((*line).width)--;
	}
}

void			minus_no_x(t_line *line, int d_l, int *f_l, unsigned int *d)
{
	int diff;

	if ((*line).width > d_l && (*line).width > (*line).precision)
		check_idk_x(line, d_l, f_l);
	else if ((*line).width != 0 && *d == 0 && (*line).precision == 0)
		write(1, " ", 1);
	if ((*line).precision > d_l && (*line).precision != 0)
	{
		diff = (*line).precision - d_l;
		while (diff--)
			*f_l += write(1, "0", 1);
	}
	if (!((*line).precision == 0 && *d == 0))
		ft_putnbr_x(*d, *line);
}

int				write_x(va_list *ap, t_line line)
{
	int				d_length;
	unsigned int	d_copy;
	unsigned int	d_copy_again;
	unsigned int	diff;
	int				final_length;

	d_copy = va_arg(*ap, int);
	d_copy_again = d_copy;
	check_params_x(&line, d_copy, &d_length);
	while (d_copy)
	{
		d_copy /= 16;
		d_length++;
	}
	final_length = d_length;
	if (line.minus == 0)
		minus_no_x(&line, d_length, &final_length, &d_copy_again);
	else
		minus_on_x(&line, d_length, &final_length, &d_copy_again);
	return (final_length);
}
