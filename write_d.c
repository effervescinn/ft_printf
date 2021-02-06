#include "libftprintf.h"

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

void check_params (s_line *line, long d_copy, int *d_length)
{
    if ((*line).width < 0)
    {
        (*line).minus = 1;
        (*line).width *= -1;
    }
    if ((*line).minus == 1)
        (*line).null_flag = 0;
    if ((*line).precision < 0 && (*line).null_flag == 1 && d_copy == 0 && (*line).width == 0)
        (*line).precision = 1;
    else if ((*line).precision < 0 && (*line).null_flag == 1)
    {
        if (d_copy < 0)
            (*line).precision = (*line).width - 1;
        else 
            (*line).precision = (*line).width;
        (*line).null_flag = 0;
    }
    if ((*line).precision_p == 'y' && (*line).precision_d == 'n' && d_copy == 0)
        (*line).precision = 0;
    if (d_copy == 0 && (*line).precision != 0)
        *d_length = 1;
    else
        *d_length = 0;
}

void minus_on(s_line *line, int d_length, int *final_length, long *d_copy_again)
{
    int diff;

     if ((*line).precision > d_length && (*line).precision > d_length)
        {
            if (*d_copy_again < 0)
            {
                write(1, "-", 1);
                *d_copy_again *= -1;
            }
            diff = (*line).precision - d_length;
            while (diff--)
            {
                write(1, "0", 1);
                (*final_length)++;
            }
        }
        if (!((*line).precision == 0 && *d_copy_again == 0))
            ft_putnbr(*d_copy_again);
        while ((*line).width > d_length && (*line).width > (*line).precision)
        {
            write(1, " ", 1);
            (*final_length)++;
            ((*line).width)--;
        }
}

void check_idk(s_line *line, int d_length, int *final_length, long *d_copy_again)
{
  if ((*line).null_flag == 1 && (*line).precision_p == 'n')
            {
                if (*d_copy_again < 0)
                    write(1, "-", 1);
                while ((*line).width > d_length && (*line).width > (*line).precision)
                {
                    write(1, "0", 1);
                    ((*line).width)--;
                    (*final_length)++;
                }
                if (*d_copy_again < 0)
                    *d_copy_again *= -1;
                return ;
            }
                while ((*line).width > d_length && (*line).width > (*line).precision)
                {
                    write(1, " ", 1);
                    ((*line).width)--;
                    (*final_length)++;
                }
                if (*d_copy_again < 0)
                    write(1, "-", 1);
                if (*d_copy_again < 0)
                    *d_copy_again *= -1;
}

void minus_no(s_line *line, int d_length, int *final_length, long *d_copy_again)
{
    int diff;

if ((*line).width > d_length && (*line).width > (*line).precision)
            check_idk(line, d_length, final_length, d_copy_again);
        else if ((*line).width != 0 && *d_copy_again == 0 && (*line).precision == 0)
            write(1, " ", 1);
        if ((*line).precision > d_length && (*line).precision != 0)
        {
            diff = (*line).precision - d_length;
            if (*d_copy_again < 0)
            {
                write(1, "-", 1);
                *d_copy_again *= -1;
            }
            while (diff--)
            {
                write(1, "0", 1);
                (*final_length)++;
            }
        }
        if (!((*line).precision == 0 && *d_copy_again == 0))
            ft_putnbr(*d_copy_again);
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