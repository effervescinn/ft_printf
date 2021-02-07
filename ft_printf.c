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

int ft_printf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	s_line line;
	int return_length;

	return_length = 0;

	while (*format)
	{
		line.precision = 1;
		line.precision_p = 'n';
		line.precision_d = 'n';
		line.minus = 0;
		line.width = 0;
		line.null_flag = 0;
		while (*format != '%' && *format)
		{
			write(1, &(*format), 1);
			format++;
			return_length++;
		}
		if (*format == '%')
		{
			while (*format == '%' && *(format + 1) == '%')
			{
				write(1, "%", 1);
				format += 2;
				return_length++;
			}
			if (*format == '%')
			{
				format++;
				while (!ft_isalpha(*format) && *format)
				{
					check_flags(&format, &line);

					if (*format >= '0' && *format <= '9')
					{
						line.width = ft_atoi(format);
						while (*format >= '0' && *format <= '9')
							format++;
					}
					if (*format == '*')
					{
						line.width = va_arg(ap, int);
						format++;
					}
					if (*format == '.')
					{
						format++;
						line.precision_p = 'y';
						if (is_num(*format) || *format == '-')
						{
							line.precision = ft_atoi(format);
							line.precision_d = 'y';
							while ((*format >= '0' && *format <= '9') || *format == '-')
								format++;
						}
						else if (*format == '*')
						{
							line.precision = va_arg(ap, int);
							line.precision_p = 'y';
							line.precision_d = 'y';
							format++;
						}
					}
					if (*format != '*' || *format != '.' || !(*format >= '0' && *format <= '9'))
						break;
				}
				line.type = *format;
				if (line.type == 'd' || line.type == 'i')
					return_length += write_d(&ap, line);
				else if (line.type == 'u')
					return_length += write_u(&ap, line);
				else if (line.type == 'c')
					return_length += write_c(&ap, line);
				else if (line.type == 's')
					return_length += write_s(&ap, line);
				else if (line.type == 'x' || line.type == 'X')
					return_length += write_x(&ap, line);
				else if (line.type == 'p')
					return_length += write_p(&ap, line);
				else if (line.type == '%')
					return_length += write_perc(line);
				if (!(*format))
				{
					va_end(ap);
					return (return_length);
				}
				format++;
			}
		}
	}
	va_end(ap);
	return (return_length);
}
