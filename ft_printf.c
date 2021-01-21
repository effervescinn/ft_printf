#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

// % [ flags] [ Ширина] [. точность] [ Размер] тип

typedef struct Line
{
    int minus; //выравнивание по левому краю в пределах ширины поля
    int null_flag;
    int width;     //ширина не обрезает, лишнее заполняет нулями или пробелами, ит депендс
    int precision; //обрезает
    int type;
    int length;
} s_line;

// 10 = a, 11 = b, 12 = c, 13 = d, 14 = e, 15 = f

int	ft_divider(long long int c)
{
	long long int	divider;

	divider = 1;
	while (c > 9)
	{
		c /= 10;
		divider *= 10;
	}
	return (divider);
}

void		ft_putnbr(int n)
{
	long long int	new_n;
	long long int	div;
	char			c;

	new_n = (long long int)n;
	if (new_n < 0)
	{
		write(1, "-", 1);
		new_n = new_n * (-1);
	}
	div = ft_divider(new_n);
	while (div)
	{
		c = (new_n / div) + '0';
		write(1, &c, 1);
		new_n -= (new_n / div) * div;
		div /= 10;
	}
}

// int hex_divider(int div)
// {
//     int divider;

//     divider  = 1;
//     while (c > 15)
//     {
//         c /= 16;
//         divider *=16;
//     }
//     return (divider);
// }

// void    print_hex(int dec)
// {
//     //int hex;
//     int div;
//     char c;

//     div = hex_divider(dec);
//     while(div)
//     {

//     }
// }
int ft_isalpha(int c)
{
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        return (1);
    return (0);
}

static int is_space(const char s)
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

int write_d(va_list *ap, s_line line)
{
    int d_length;
    long d_copy;
    long d_copy_again;
    int diff;
    int final_length;

    d_copy = va_arg(*ap, int);
    d_copy_again = d_copy;
    if (d_copy == 0)
        d_length = 1;
    else
        d_length = 0;
    while (d_copy)
    {
        d_copy /= 10;
        d_length++;
    }
    final_length = d_length;
    if (d_copy_again < 0)
        final_length++;
    if (line.minus == 0 || line.precision > d_length)
    {
        if (line.width > d_length && line.width > line.precision)
        {
            if (line.null_flag == 1 && line.precision < 2)
            {
                while (line.width > d_length && line.width > line.precision)
                {
                    write(1, "0", 1);
                    (line.width)--;
                    final_length++;
                }
            }
            else
            {
                while (line.width > d_length && line.width > line.precision)
                {
                    write(1, " ", 1);
                    (line.width)--;
                    final_length++;
                }
            }
        }
        if (line.precision > d_length)
        {
            diff = line.precision - d_length;
            while (diff--)
            {
                write(1, "0", 1);
                final_length++;
            }
        }
        ft_putnbr(d_copy_again);
    }
    else
    {
        ft_putnbr(d_copy_again);
        if (line.width > d_length && line.width > line.precision)
        {
            while (line.width > d_length && line.width > line.precision)
            {
                write(1, " ", 1);
                final_length++;
                (line.width)--;
            }
        }
    }
    return (final_length);
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
        line.minus = 0;
        line.width = 0;
        line.null_flag = 0;

        while (*format && *format != '%')
        {
            write(1, &(*format), 1);
            format++;
            return_length++;
        }
        while (*format == '%' && *(++format) == '%')
        {
            write(1, "%", 1);
            format++;
            return_length++;
        }
        if (*format == '\0')
        {
            va_end(ap);
            return (return_length);
        }
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
                if (is_num(*(++format)))
                    line.precision = ft_atoi(format);
                while (*format >= '0' && *format <= '9')
                    format++;
            }
        }
        line.type = *format;
        if (line.type == 'd') //написать функцию чекер типа
            return_length += write_d(&ap, line);
        format++;
    }
    va_end(ap);
    return (return_length);
}


int main()
{
    printf("|original=%d|", -2147483648);
    printf("|my=%d|", -2147483648);
    return 0;
}

