/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:46:20 by lnorcros          #+#    #+#             */
/*   Updated: 2021/02/08 18:46:21 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	check_params(t_line *l, long d, int *d_length)
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

void	minus_on(t_line *line, int d_length, int *f_l, long *d)
{
	int	diff;

	if ((*line).precision > d_length && (*line).precision > d_length)
	{
		if (*d < 0)
		{
			write(1, "-", 1);
			*d *= -1;
		}
		diff = (*line).precision - d_length;
		while (diff--)
			*f_l += write(1, "0", 1);
	}
	if (!((*line).precision == 0 && *d == 0))
		ft_putnbr(*d);
	while ((*line).width > d_length && (*line).width > (*line).precision)
	{
		*f_l += write(1, " ", 1);
		((*line).width)--;
	}
}

void	check_idk(t_line *line, int d_l, int *f_l, long *d)
{
	if ((*line).null_flag == 1 && (*line).precision_p == 'n')
	{
		if (*d < 0)
			write(1, "-", 1);
		while ((*line).width > d_l && (*line).width > (*line).precision)
		{
			*f_l += write(1, "0", 1);
			((*line).width)--;
		}
		if (*d < 0)
			*d *= -1;
		return ;
	}
	while ((*line).width > d_l && (*line).width > (*line).precision)
	{
		*f_l += write(1, " ", 1);
		((*line).width)--;
	}
	if (*d < 0)
		write(1, "-", 1);
	if (*d < 0)
		*d *= -1;
}

void	minus_no(t_line *line, int d_length, int *final_length, long *d)
{
	int	diff;

	if ((*line).width > d_length && (*line).width > (*line).precision)
		check_idk(line, d_length, final_length, d);
	else if ((*line).width != 0 && *d == 0 && (*line).precision == 0)
		write(1, " ", 1);
	if ((*line).precision > d_length && (*line).precision != 0)
	{
		diff = (*line).precision - d_length;
		if (*d < 0)
		{
			write(1, "-", 1);
			*d *= -1;
		}
		while (diff--)
			*final_length += write(1, "0", 1);
	}
	if (!((*line).precision == 0 && *d == 0))
		ft_putnbr(*d);
}

int		write_d(va_list *ap, t_line line)
{
	int		d_length;
	long	d_copy;
	long	d_copy_again;
	int		diff;
	int		final_length;

	d_copy = va_arg(*ap, int);
	d_copy_again = d_copy;
	check_params(&line, d_copy, &d_length);
	while (d_copy)
	{
		d_copy /= 10;
		d_length++;
	}
	final_length = d_length;
	if (d_copy_again < 0)
	{
		line.width--;
		final_length++;
	}
	if (line.minus == 0)
		minus_no(&line, d_length, &final_length, &d_copy_again);
	else
		minus_on(&line, d_length, &final_length, &d_copy_again);
	return (final_length);
}
