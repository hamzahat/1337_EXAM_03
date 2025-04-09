
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_check_format(const char *c, va_list args, int *count);
int	ft_puthexa(unsigned int num, int *count, const char *c);
int	ft_putptr(unsigned long ptr, int *count);
int	ft_putunsgd(unsigned int n, int *count);
int	ft_putstr(char *str, int *count);
int	ft_putchar(char c, int *count);
int	ft_putnbr(int nb, int *count);
int	ft_check_char(const char *c);

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if ((*format == '%') && *(++format))
		{
			if (ft_check_char(format))
			{
				if (ft_check_format(format, args, &count) == -1)
					return (-1);
			}
			else if (ft_putchar(*format, &count) == -1)
				return (-1);
		}
		else if (ft_putchar(*format, &count) == -1)
			return (-1);
		format++;
	}
	va_end(args);
	return (count);
}
// ft_printf ===================================================================
#include <stdio.h>

int	ft_check_char(const char *c)
{
	char	*str;

	str = "cspdiuxX%";
	while (*str)
	{
		if (*str == *c)
			return (1);
		str++;
	}
	return (0);
}
// ft_check_char ===============================================================

int	ft_check_format(const char *c, va_list args, int *count)
{
	if (*c == 'c')
		return (ft_putchar(va_arg(args, int), count));
	if (*c == 's')
		return (ft_putstr(va_arg(args, char *), count));
	if (*c == 'p')
		return (ft_putstr("0x", count), \
				ft_putptr(va_arg(args, unsigned long), count));
	if (*c == 'd' || *c == 'i')
		return (ft_putnbr(va_arg(args, int), count));
	if (*c == 'u')
		return (ft_putunsgd(va_arg(args, unsigned int), count));
	if (*c == 'x' || *c == 'X')
		return (ft_puthexa(va_arg(args, unsigned int), count, c));
	if (*c == '%')
		return (ft_putchar('%', count));
	c++;
	return (0);
}
// ft_check_format =============================================================

int	ft_putchar(char c, int *count)
{
	int	written;

	written = write(1, &c, 1);
	if (written == -1)
		return (-1);
	*count += written;
	return (0);
}
// ft_putchar ==================================================================

int	ft_puthexa(unsigned int num, int *count, const char *c)
{
	char	*base;

	if (*c == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (num >= 16)
		if (ft_puthexa(num / 16, count, c) == -1)
			return (-1);
	if (ft_putchar(base[num % 16], count) == -1)
		return (-1);
	return (0);
}
// ft_puthexa ==================================================================

int	ft_putnbr(int nb, int *count)
{
	long	num;

	num = nb;
	if (num < 0)
	{
		if (ft_putchar('-', count) == -1)
			return (-1);
		num = -num;
	}
	if (num > 9)
		ft_putnbr(num / 10, count);
	if (ft_putchar((num % 10) + 48, count) == -1)
		return (-1);
	return (0);
}
// ft_putnbr ===================================================================

int	ft_putptr(unsigned long ptr, int *count)
{
	unsigned long	addr;
	char			*base;

	if (!ptr)
		return (ft_putstr("0", count) == -1);
	base = "0123456789abcdef";
	addr = (unsigned long) ptr;
	if (addr >= 16)
		if (ft_putptr((addr / 16), count) == -1)
			return (-1);
	if (ft_putchar(base[addr % 16], count) == -1)
		return (-1);
	return (0);
}
//ft_putptr ====================================================================

int	ft_putstr(char *str, int *count)
{
	if (!str)
		return (ft_putstr("(null)", count));
	while (*str)
	{
		if (ft_putchar(*str++, count) == -1)
			return (-1);
	}
	return (0);
}
// ft_putstr ===================================================================

int	ft_putunsgd(unsigned int n, int *count)
{
	if (n > 9)
		if (ft_putunsgd(n / 10, count) == -1)
			return (-1);
	if (ft_putchar((n % 10) + 48, count) == -1)
		return (-1);
	return (0);
}
// ft_putunsigned ==============================================================
