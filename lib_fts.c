/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_fts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:45:43 by lnorcros          #+#    #+#             */
/*   Updated: 2021/02/08 18:45:45 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_strcpy(char *dst, const char *src)
{
	if (*src == '\0')
		*dst = '\0';
	else
	{
		while (*src)
		{
			*dst = *src;
			dst++;
			src++;
		}
		while (*dst)
		{
			*dst = '\0';
		}
	}
}

int		ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int		is_space(const char s)
{
	if (s == ' ' || s == '\n' || s == '\t' ||
	s == '\v' || s == '\f' || s == '\r')
		return (1);
	return (0);
}

int		is_num(const char s)
{
	if (s >= '0' && s <= '9')
		return (1);
	return (0);
}

int		ft_atoi(const char *str)
{
	unsigned long long int	res;
	int						sign;

	res = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (is_num(*str))
	{
		res = res * 10 + *str - '0';
		str++;
	}
	if (res > 999999999999999999 && sign == 1)
		return (-1);
	if (res > 999999999999999999 && sign == -1)
		return (0);
	return (res * sign);
}
