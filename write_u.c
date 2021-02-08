/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:48:05 by lnorcros          #+#    #+#             */
/*   Updated: 2021/02/08 18:48:06 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			check_params_u(t_line *l, unsigned int d, int *d_length)
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
		*d_length = 1;
	else
		*d_length = 0;
}

void			minus_on_u(t_line *line, int d_l, int *f_l, unsigned int *d)
{
	int	diff;

	if ((*line).precision > d_l && (*line).precision > d_l)
	{
		diff = (*line).precision - d_l;
		while (diff--)
			*f_l += write(1, "0", 1);
	}
	if (!((*line).precision == 0 && *d == 0))
		ft_putnbr_u(*d);
	while ((*line).width > d_l && (*line).width > (*line).precision)
	{
		*f_l += write(1, " ", 1);
		((*line).width)--;
	}
}

void			check_idk_u(t_line *line, int d_length, int *final_length)
{
	if ((*line).null_flag == 1 && (*line).precision_p == 'n')
	{
		while ((*line).width > d_length && (*line).width > (*line).precision)
		{
			*final_length += write(1, "0", 1);
			((*line).width)--;
		}
		return ;
	}
	while ((*line).width > d_length && (*line).width > (*line).precision)
	{
		*final_length += write(1, " ", 1);
		((*line).width)--;
	}
}

void			minus_no_u(t_line *line, int d_l, int *f_l, unsigned int *d)
{
	int diff;

	if ((*line).width > d_l && (*line).width > (*line).precision)
		check_idk_u(line, d_l, f_l);
	else if ((*line).width != 0 && *d == 0 && (*line).precision == 0)
		write(1, " ", 1);
	if ((*line).precision > d_l && (*line).precision != 0)
	{
		diff = (*line).precision - d_l;
		while (diff--)
			*f_l += write(1, "0", 1);
	}
	if (!((*line).precision == 0 && *d == 0))
		ft_putnbr_u(*d);
}

int				write_u(va_list *ap, t_line line)
{
	int				d_length;
	unsigned int	d_copy;
	unsigned int	d_copy_again;
	unsigned int	diff;
	int				final_length;

	d_copy = va_arg(*ap, int);
	d_copy_again = d_copy;
	check_params_u(&line, d_copy, &d_length);
	while (d_copy)
	{
		d_copy /= 10;
		d_length++;
	}
	final_length = d_length;
	if (line.minus == 0)
		minus_no_u(&line, d_length, &final_length, &d_copy_again);
	else
		minus_on_u(&line, d_length, &final_length, &d_copy_again);
	return (final_length);
}
