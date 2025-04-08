#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

int	ft_putstr(char *s)
{
	int len = 0;
	if (!s)
		s = "(null)";
	while (s[len])
		write(1, &s[len++], 1);
	return (len);
}

int	ft_putnbr(int n)
{
	long nb = n;
	int count = 0;
	char c;

	if (nb < 0)
	{
		write(1, "-", 1);
		count++;
		nb = -nb;
	}
	if (nb > 9)
		count += ft_putnbr(nb / 10);
	c = '0' + (nb % 10);
	write(1, &c, 1);
	return (count + 1);
}

int	ft_puthex(unsigned int n)
{
	char *hex = "0123456789abcdef";
	int count = 0;

	if (n >= 16)
		count += ft_puthex(n / 16);
	write(1, &hex[n % 16], 1);
	return (count + 1);
}

int	ft_printf(const char *format, ...)
{
	va_list args;
	int i = 0, count = 0;

	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			if (format[i] == 's')
				count += ft_putstr(va_arg(args, char *));
			else if (format[i] == 'd')
				count += ft_putnbr(va_arg(args, int));
			else if (format[i] == 'x')
				count += ft_puthex(va_arg(args, unsigned int));
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
