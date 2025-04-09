#include <unistd.h> // write
#include <stdarg.h> // va_start, va_arg, va_end

//? putstr
int	ft_putstr(char *s)
{
	int len = 0;
	if (!s)
		s = "(null)";
	while (s[len])
		write(1, &s[len++], 1);
	return (len);
}

//? putnbr
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

//? put_hexa
int	ft_puthex(unsigned int n)
{
	char *hex = "0123456789abcdef";
	int count = 0;

	if (n >= 16)
		count += ft_puthex(n / 16);
	write(1, &hex[n % 16], 1);
	return (count + 1);
}

//? ft_printf
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int	i = 0;
	int	count = 0;

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

//? test main:
#include <stdio.h>
int	main (void)
{
	printf("Hello %s\n", "toto");	// origine
	ft_printf("Hello %s\n", "toto");// copy
//!out:Hello toto$

	printf("Magic %s is %d\n", "number", 42);	//origine
	ft_printf("Magic %s is %d\n", "number", 42);// copy
//!out:Magic number is 42%

	printf("Hexadecimal for %d is %x\n", 42, 42);	//origine
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);//copy
//! out:Hexadecimal for 42 is 2a$

	return 0;
}

//! pased in grademe tests
