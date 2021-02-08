#include "libftprintf.h"

void ft_strcpy(char *dst, const char *src)
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

int ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int is_space(const char s)
{
	if (s == ' ' || s == '\n' || s == '\t' || s == '\v' || s == '\f' || s == '\r')
		return (1);
	return (0);
}

int is_num(const char s)
{
	if (s >= '0' && s <= '9')
		return (1);
	return (0);
}

int ft_atoi(const char *str)
{
	unsigned long long int res;
	int sign;

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

void check_flags(const char **str, s_line *line)
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
			return;
	}
}

void	check_type(int *r_len, s_line line, va_list *ap)
{
if (line.type == 'd' || line.type == 'i')
					*r_len += write_d(ap, line);
				else if (line.type == 'u')
					*r_len += write_u(ap, line);
				else if (line.type == 'c')
					*r_len += write_c(ap, line);
				else if (line.type == 's')
					*r_len+= write_s(ap, line);
				else if (line.type == 'x' || line.type == 'X')
					*r_len += write_x(ap, line);
				else if (line.type == 'p')
					*r_len += write_p(ap, line);
				else if (line.type == '%')
					*r_len += write_perc(line);
}

void pars_w_p(const char **format, s_line *line, va_list *ap)
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
						if (is_num(**format) || **format == '-') //change is_num
						{
							(*line).precision = ft_atoi(*format);
							(*line).precision_d = 'y';
							while ((**format >= '0' && **format <= '9') || **format == '-')
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

void	rep_perc(const char **format, s_line *line, int *r_l, va_list *ap)
{
				(*format)++;
				while (!ft_isalpha(**format) && **format)
				{
					check_flags(format, line);
					if (**format >= '0' && **format <= '9')
					{
						(*line).width = ft_atoi(*format);
						while (**format >= '0' && **format <= '9')
							(*format)++;
					}
					pars_w_p(format, line, ap);
					if (**format != '*' || **format != '.' || !(is_num(**format)))
						break;
				}
				(*line).type = **format;
				check_type(r_l, *line, ap);
}

void set_line(s_line *line, int *r_l, const char **format)
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

void parse_perc(const char **format, int *r_l)
{
while (**format == '%' && *((*format) + 1) == '%')
			{
				*r_l += write(1, "%", 1);
				(*format) += 2;
			}
}

int ft_printf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	s_line line;
	int return_length;

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
