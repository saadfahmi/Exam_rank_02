#include <unistd.h> // write//
#include <stdarg.h>

#define NOTATION ((spec == 'd') ? 10 : 16)
#define BASE ((spec == 'd') ? "0123456789" : "0123456789abcdef")

int width;
int dot;
int prec;
int spec;
int data_len;
int printed_len;

int ft_strlen(char *str)
{
    int idx = 0;
    if (spec == 's' && dot == 1 && prec == 0)
        return (0);
    while (str[idx])
        idx++;
    return (idx);
}

int ft_nbrlen(long long n)
{
    int idx = 1;

    if (n == 0 && dot == 1 && prec == 0)
        return (0);
    while (n >= NOTATION)
    {
        n /= NOTATION;
        idx++;
    }

    return (idx);
}

void ft_putchar(int c)
{
    write(1, &c, 1);
    printed_len++;
}

void ft_putstr(char *s)
{
    int idx = 0;
    if (dot == 1 && prec == 0)
        return;
    if (prec)
        while (s[idx] && idx < prec)
            ft_putchar(s[idx++]);
    else
        while (s[idx])
            ft_putchar(s[idx++]);
}

void putnbr(long long n)
{
    if (n == 0 && dot == 1 && prec == 0)
        return;
    if (n >= NOTATION)
        ft_putnbr(n / NOTATION);
    ft_putchar(BASE[n % NOTATION]);
}

void print_space_zero(void)
{
    int count_space = 0;
    int count_zero = 0; 

    if (spec == 's')
        count_space = (prec && prec < data_len) ? width - prec : width - data_len;
    else 
    {
        count_space = (data_len < prec) ? width - prec : width - data_len;
        count_zero = prec - data_len;
    }
    while (0 < count_space--)
        ft_putchar(' ');
    while (0 < count_zero--) 
        ft_putchar('0');
}

void print_sdx(va_list ap)
{
    char *data_s;
    long long data_dx;

    if (spec == 's')
    {
        data_s = va_arg(ap, char *);
        data_s = (data_s == NULL) ? "(null)" : data_s;
        data_len = ft_strlen(data_s);
        print_space_zero();
        ft_putstr(data_s);
    }
    else
    {
        spec == 'd' ? (data_dx = va_arg(ap, int)) : (data_dx = va_arg(ap, unsigned int));
        data_len = (data_dx < 0) ? (int)ft_nbrlen(-data_dx) : ft_nbrlen(data_dx);
        print_space_zero();
        data_dx < 0 ? ft_putchar('-') : 0;                      
        data_dx < 0 ? ft_putnbr(-data_dx) : ft_putnbr(data_dx); 
    }
}

void parse_info(const char **str) 
{
    while ('0' <= **str && **str <= '9')
    {
        width = width * 10 + **str - '0';
        (*str)++;
    }
    if (**str == '.')
    {
        dot = 1;
        (*str)++;
    }
    while ('0' <= **str && **str <= '9')
    {
        prec = prec * 10 + **str - '0';
        (*str)++;
    }
    if (**str == 's' || **str == 'd' || **str == 'x')
        spec = **str;
}

void init()
{
    width = 0;
    dot = 0;
    prec = 0;
    spec = 0;
    data_len = 0;
}

int ft_printf(const char *str, ...)
{
    va_list ap;

    va_start(ap, str);
    printed_len = 0;
    while (*str)
    {
        if (*str == '%')
        {
            ++str;
            parse_info(&str);
            print_sdx(ap);
            str++;
        }
        else
        {
            ft_putchar(*str);
            str++;
        }
        init();
    }
    va_end(ap);
    return (printed_len);
}
