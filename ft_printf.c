#include "libftprintf.h"

// % [ flags] [ Ширина] [. точность] [ Размер] тип

// 10 = a, 11 = b, 12 = c, 13 = d, 14 = e, 15 = f

size_t ft_strlen(const char *str)
{
    size_t i;

    i = 0;
    while (*str)
    {
        i++;
        str++;
    }
    return (i);
}

int ft_divider(long long int c)
{
    long long int divider;

    divider = 1;
    while (c > 9)
    {
        c /= 10;
        divider *= 10;
    }
    return (divider);
}

unsigned int ft_divider_u(unsigned int c)
{
    unsigned int divider;

    divider = 1;
    while (c > 9)
    {
        c /= 10;
        divider *= 10;
    }
    return (divider);
}

unsigned long ft_divider_hex(unsigned long c)
{
    unsigned long divider;

    divider = 1;
    while (c > 15)
    {
        c /= 16;
        divider *= 16;
    }
    return (divider);
}

void ft_putnbr(int n)
{
    long long int new_n;
    long long int div;
    char c;

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

void ft_putnbr_u(unsigned int n)
{
    unsigned int new_n;
    unsigned int div;
    char c;

    new_n = (unsigned int)n;
    if (new_n < 0)
    {
        write(1, "-", 1);
        new_n = new_n * (-1);
    }
    div = ft_divider_u(new_n);
    while (div)
    {
        c = (new_n / div) + '0';
        write(1, &c, 1);
        new_n -= (new_n / div) * div;
        div /= 10;
    }
}

void ft_putnbr_hex(unsigned long n, s_line line)
{
    unsigned long div;
    char c;

    div = ft_divider_hex(n);
    if (line.type == 'p')
    {
        write(1, "0", 1);
        write(1, "x", 1);
    }
    while (div)
    {
        c = (n / div);
        if (c < 10 && !(n == 0 && line.type == 'p' && line.precision_p == 'y'))
            c += '0';
        else if (c >= 10 && line.type == 'X')
            c += 55;
        else if ((c >= 10 && line.type == 'x') || (c >= 10 && line.type == 'p'))
            c += 87;
        else
            break;
        write(1, &c, 1);
        n -= (n / div) * div;
        div /= 16;
    }
}

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

int write_c(va_list *ap, s_line line)
{
    char c;
    int final_length;

    c = va_arg(*ap, int);
    final_length = 1;
    if (line.minus == 1)
    {
        write(1, &c, 1);
        while (line.width && line.width > 1)
        {
            write(1, " ", 1);
            (line.width)--;
            final_length++;
        }
        return (final_length);
    }
    while (line.width && line.width > 1)
    {
        write(1, " ", 1);
        (line.width)--;
        final_length++;
    }
    write(1, &c, 1);
    return (final_length);
}

int write_x(va_list *ap, s_line line)
{
    unsigned long d_length;
    unsigned long d_copy;
    unsigned long d_copy_again;
    unsigned long diff;
    unsigned long final_length;

    d_copy = va_arg(*ap, unsigned long);
    d_copy_again = d_copy;
    if (line.precision_p == 'y' && line.precision_d == 'n' && d_copy == 0)
        line.precision = 0;
    if (line.minus == 'y')
        line.null_flag = 0;
    if (d_copy == 0 && line.precision != 0)
        d_length = 1;
    else
        d_length = 0;
    while (d_copy)
    {
        d_copy /= 16;
        d_length++;
    }
    d_copy = d_copy_again;
    final_length = d_length;
    if (d_copy_again < 0)
    {
        line.width--;
        final_length++;
    }
    if (line.minus == 0)
    {
        if (line.width > d_length && line.width > line.precision)
        {
            if (line.null_flag == 1 && line.precision_p == 'n')
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
        else if (line.width != 0 && d_copy_again == 0 && line.precision == 0)
            write(1, " ", 1);
        if (line.precision > d_length && line.precision != 0)
        {
            diff = line.precision - d_length;
            while (diff--)
            {
                write(1, "0", 1);
                final_length++;
            }
        }
        if (!(line.precision == 0 && d_copy_again == 0))
            ft_putnbr_hex(d_copy_again, line);
    }
    else
    {
        if (line.precision > d_length && line.precision > d_length)
        {
            diff = line.precision - d_length;
            while (diff--)
            {
                write(1, "0", 1);
                final_length++;
            }
        }
        if (!(line.precision == 0 && d_copy_again == 0))
            ft_putnbr_hex(d_copy_again, line);
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

int write_p(va_list *ap, s_line line)
{
    unsigned long d_length;
    unsigned long d_copy;
    unsigned long d_copy_again;
    unsigned long diff;
    unsigned long final_length;

    d_copy = va_arg(*ap, unsigned long);
    d_copy_again = d_copy;
    d_length = 2;
    if (d_copy == 0 && line.precision_p == 'n')
        d_length = 3;
    while (d_copy)
    {
        d_copy /= 16;
        d_length++;
    }
    final_length = d_length;
    if (line.minus == 0)
    {
        while (line.width > d_length && line.width > line.precision)
        {
            write(1, " ", 1);
            (line.width)--;
            final_length++;
        }
        if (line.width != 0 && d_copy_again == 0 && line.precision == 0)
            write(1, " ", 1);
        if (!(line.precision == 0 && d_copy_again == 0))
            ft_putnbr_hex(d_copy_again, line);
    }
    else
    {
        if (!(line.precision == 0 && d_copy_again == 0))
            ft_putnbr_hex(d_copy_again, line);
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

int write_u(va_list *ap, s_line line)
{
    unsigned int d_length;
    unsigned int d_copy;
    unsigned int d_copy_again;
    unsigned int diff;
    unsigned int final_length;

    d_copy = va_arg(*ap, unsigned int);
    d_copy_again = d_copy;
    if (line.precision_p == 'y' && line.precision_d == 'n' && d_copy == 0)
        line.precision = 0;
    if (line.minus == 'y')
        line.null_flag = 0;
    if (d_copy == 0 && line.precision != 0)
        d_length = 1;
    else
        d_length = 0;
    while (d_copy)
    {
        d_copy /= 10;
        d_length++;
    }
    d_copy = d_copy_again;
    final_length = d_length;
    if (d_copy_again < 0)
    {
        line.width--;
        final_length++;
    }
    if (line.minus == 0)
    {
        if (line.width > d_length && line.width > line.precision)
        {
            if (line.null_flag == 1 && line.precision_p == 'n')
            {
                if (d_copy_again < 0)
                {
                    write(1, "-", 1);
                    d_copy_again *= -1;
                }
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
                if (d_copy_again < 0)
                {
                    write(1, "-", 1);
                    d_copy_again *= -1;
                }
            }
        }
        else if (line.width != 0 && d_copy_again == 0 && line.precision == 0)
            write(1, " ", 1);
        if (line.precision > d_length && line.precision != 0)
        {
            diff = line.precision - d_length;
            if (d_copy_again < 0)
            {
                write(1, "-", 1);
                d_copy_again *= -1;
            }
            while (diff--)
            {
                write(1, "0", 1);
                final_length++;
            }
        }
        if (!(line.precision == 0 && d_copy_again == 0))
            ft_putnbr_u(d_copy_again);
    }
    else
    {
        if (line.precision > d_length && line.precision > d_length)
        {
            if (d_copy_again < 0)
            {
                write(1, "-", 1);
                d_copy_again *= -1;
            }
            diff = line.precision - d_length;
            while (diff--)
            {
                write(1, "0", 1);
                final_length++;
            }
        }
        if (!(line.precision == 0 && d_copy_again == 0))
            ft_putnbr_u(d_copy_again);
        while (line.width > d_length && line.width > line.precision)
        {
            write(1, " ", 1);
            final_length++;
            (line.width)--;
        }
    }
    return (final_length);
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
    if (line.width < 0)
    {
        line.minus = 1;
        line.width *= -1;
    }
    if (line.precision_p == 'y' && line.precision_d == 'n' && d_copy == 0)
        line.precision = 0;
    if (line.minus == 'y')
        line.null_flag = 0;
    if (d_copy == 0 && line.precision != 0)
        d_length = 1;
    else
        d_length = 0;
    while (d_copy)
    {
        d_copy /= 10;
        d_length++;
    }
    d_copy = d_copy_again;
    final_length = d_length;
    if (d_copy_again < 0)
    {
        line.width--;
        final_length++;
    }
    if (line.minus == 0)
    {
        if (line.width > d_length && line.width > line.precision)
        {
            if (line.null_flag == 1 && line.precision_p == 'n')
            {
                if (d_copy_again < 0)
                {
                    write(1, "-", 1);
                    d_copy_again *= -1;
                }
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
                if (d_copy_again < 0)
                {
                    write(1, "-", 1);
                    d_copy_again *= -1;
                }
            }
        }
        else if (line.width != 0 && d_copy_again == 0 && line.precision == 0)
            write(1, " ", 1);
        if (line.precision > d_length && line.precision != 0)
        {
            diff = line.precision - d_length;
            if (d_copy_again < 0)
            {
                write(1, "-", 1);
                d_copy_again *= -1;
            }
            while (diff--)
            {
                write(1, "0", 1);
                final_length++;
            }
        }
        if (!(line.precision == 0 && d_copy_again == 0))
            ft_putnbr(d_copy_again);
    }
    else
    {
        if (line.precision > d_length && line.precision > d_length)
        {
            if (d_copy_again < 0)
            {
                write(1, "-", 1);
                d_copy_again *= -1;
            }
            diff = line.precision - d_length;
            while (diff--)
            {
                write(1, "0", 1);
                final_length++;
            }
        }
        if (!(line.precision == 0 && d_copy_again == 0))
            ft_putnbr(d_copy_again);
        while (line.width > d_length && line.width > line.precision)
        {
            write(1, " ", 1);
            final_length++;
            (line.width)--;
        }
    }
    return (final_length);
}

int write_s(va_list *ap, s_line line)
{
    int string_width;
    char *string;
    int final_length;

    string = va_arg(*ap, char *);
    if (line.precision < 0)
    {
        line.precision = 0;
        line.precision_p = 'n';
    }
    // printf("%d", line.precision);
    if (line.width < 0)
    {
        line.width *= -1;
        line.minus = 1;
    }
    // printf("%d", line.width);
    if (!string)
        string = "(null)";
    string_width = ft_strlen(string);
    if (line.precision_p == 'y' && line.precision_d == 'n')
        line.precision = 0;
    else if (line.precision_p == 'n')
        line.precision = string_width;
    final_length = 0;
    if (line.precision <= string_width)
        string_width = line.precision;

    if (line.minus == 0)
    {
        while ((line.width)-- > string_width)
        {
            write(1, " ", 1);
            final_length++;
        }
        while (string_width--)
        {
            write(1, string, 1);
            string++;
            final_length++;
        }
        return (final_length);
    }
    while (string_width--)
    {
        write(1, string, 1);
        string++;
        final_length++;
        (line.width)--;
    }
    while (line.width-- > 0)
    {
        write(1, " ", 1);
        final_length++;
    }
    return (final_length);
}

int ft_printf(const char *format, ...) //("%%*i 42 == |%*i|", 2, 42)
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
                }
                line.type = *format;
                if (line.type == 'd' || line.type == 'i')
                    return_length += write_d(&ap, line);
                if (line.type == 'u')
                    return_length += write_u(&ap, line);
                if (line.type == 'c')
                    return_length += write_c(&ap, line);
                if (line.type == 's')
                    return_length += write_s(&ap, line);
                if (line.type == 'x' || line.type == 'X')
                    return_length += write_x(&ap, line);
                if (line.type == 'p')
                    return_length += write_p(&ap, line);
                format++;
            }
        }
    }
    va_end(ap);
    return (return_length);
}

// int main()
// {

//     char *b = "hgjhjh";
//     char *c = "bsdfsdf";

//     printf("%%*i 42 == |%i|", 42);
//     // ft_printf("%-*.*s", 7, 3, "yolo");
//     return 0;
// }
