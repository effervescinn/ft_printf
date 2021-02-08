/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:59:59 by lnorcros          #+#    #+#             */
/*   Updated: 2021/02/08 19:00:01 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

typedef	struct	s_line
{
	int		minus;
	int		null_flag;
	int		width;
	int		precision;
	char	precision_p;
	char	precision_d;
	int		type;
	int		length;
}				t_line;

void			ft_strcpy(char *dst, const char *src);
int				ft_isalpha(int c);
int				is_space(const char s);
int				is_num(const char s);
int				ft_atoi(const char *str);
void			set_line(t_line *line, int *r_l, const char **format);
int				ft_printf(const char *format, ...);
void			parse_perc(const char **format, int *r_l);
void			rep_perc(const char **f, t_line *line, int *r_l, va_list *ap);
void			check_flags(const char **str, t_line *line);
void			pars_w_p(const char **format, t_line *line, va_list *ap);
void			check_type(int *r_len, t_line line, va_list *ap);
void			check_params(t_line *l, long d, int *d_length);
void			minus_on(t_line *line, int d_length, int *f_l, long *d);
void			check_idk(t_line *line, int d_l, int *f_l, long *d);
void			minus_no(t_line *line, int d_len, int *final_len, long *d);
int				write_d(va_list *ap, t_line line);
int				ft_divider(long long int c);
void			ft_putnbr(int n);
size_t			ft_strlen(const char *str);
void			check_s(t_line *line, char **str, int *str_w, int *f_len);
void			minus_s(t_line *line, char **str, int *str_w, int *f_len);
int				write_s(va_list *ap, t_line line);
int				write_perc(t_line line);
void			check_params_u(t_line *l, unsigned int d, int *d_length);
void			minus_on_u(t_line *line, int d_l, int *f_l, unsigned int *d);
void			check_idk_u(t_line *line, int d_length, int *final_length);
void			minus_no_u(t_line *line, int d_l, int *f_l, unsigned int *d);
int				write_u(va_list *ap, t_line line);
unsigned int	ft_divider_u(unsigned int c);
void			ft_putnbr_u(unsigned int n);
void			check_params_x(t_line *l, unsigned int d, int *d_l);
void			minus_on_x(t_line *line, int d_l, int *f_l, unsigned int *d);
void			check_idk_x(t_line *line, int d_l, int *f_l);
void			minus_no_x(t_line *line, int d_l, int *f_l, unsigned int *d);
int				write_x(va_list *ap, t_line line);
unsigned int	ft_divider_x(unsigned int c);
void			ft_putnbr_x(unsigned int n, t_line line);
unsigned long	ft_divider_p(unsigned long c);
void			ft_putnbr_p(unsigned long n, t_line line);
void			minus_p(t_line *l, unsigned long *f, int dl, unsigned long *d);
int				write_p(va_list *ap, t_line line);
int				write_c(va_list *ap, t_line line);

#endif
