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
#define LIBFTPRINTF_H
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

typedef struct Line
{
	int minus;
	int null_flag;
	int width;
	int precision;
	char precision_p;
	char precision_d;
	int type;
	int length;
} s_line;

int ft_printf(const char *format, ...);
size_t ft_strlen(const char *str);
void check_s(s_line *line, char **string, int *string_width, int *final_length);
void minus_s(s_line *line, char **string, int *string_width, int *final_length);
int write_s(va_list *ap, s_line line);
void check_params(s_line *line, long d_copy, int *d_length);
void minus_on(s_line *line, int d_length, int *final_length, long *d_copy_again);
void check_idk(s_line *line, int d_length, int *final_length, long *d_copy_again);
void minus_no(s_line *line, int d_length, int *final_length, long *d_copy_again);
int write_d(va_list *ap, s_line line);
int write_perc(s_line line);

unsigned int ft_divider_u(unsigned int c);
void ft_putnbr_u(unsigned int n);
void check_params_u(s_line *line, unsigned int d_copy, int *d_length);
void minus_on_u(s_line *line, int d_length, int *final_length, unsigned int *d_copy_again);
void check_idk_u(s_line *line, int d_length, int *final_length);
void minus_no_u(s_line *line, int d_length, int *final_length, unsigned int *d_copy_again);
int write_u(va_list *ap, s_line line);

void minus_no_x(s_line *line, int d_length, int *final_length, unsigned int *d_copy_again);
void check_idk_x(s_line *line, int d_length, int *final_length);
void minus_on_x(s_line *line, int d_length, int *final_length, unsigned int *d_copy_again);
void check_params_x(s_line *line, unsigned int d_copy, int *d_length);
void ft_putnbr_x(unsigned int n, s_line line);
unsigned int ft_divider_x(unsigned int c);
int write_x(va_list *ap, s_line line);

void ft_putnbr_p(unsigned long n, s_line line);
unsigned long ft_divider_p(unsigned long c);
int write_p(va_list *ap, s_line line);

int write_c(va_list *ap, s_line line);

void check_flags(const char **str, s_line *line);
int ft_atoi(const char *str);
int is_num(const char s);
int is_space(const char s);
int ft_isalpha(int c);
int ft_divider(long long int c);
void ft_putnbr(int n);
void ft_strcpy(char *dst, const char *src);

#endif
