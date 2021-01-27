/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:11:47 by lnorcros          #+#    #+#             */
/*   Updated: 2020/11/11 14:11:49 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

typedef struct Line
{
    int minus; //выравнивание по левому краю в пределах ширины поля
    int null_flag;
    int width;     //ширина не обрезает, лишнее заполняет нулями или пробелами, ит депендс
    int precision; //обрезает
    char precision_p;
    char precision_d;
    int type;
    int length;
} s_line;

int ft_printf(const char *format, ...);
int write_d(va_list *ap, s_line line);
void check_flags(const char **str, s_line *line);
int ft_atoi(const char *str);
int is_num(const char s);
int is_space(const char s);
int ft_isalpha(int c);
int	ft_divider(long long int c);
void		ft_putnbr(int n);

#endif
