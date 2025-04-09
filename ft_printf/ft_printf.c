#include <stdarg.h>
#include <unistd.h>

//? ft_putchar
int	ft_put_char(char c)
{
	return(write(1, &c, 1));
}

//? ft_putstr
int ft_put_str(char *str)
{
	int count = 0;
	if (!str)
		str = "(null)";
	while (str[count])
		ft_put_char(str[count++]);
	return (count);
}

//? ft_putnbr
int ft_put_nbr(int nb)
{
	long num = nb;
	int count = 0;

	if (num < 0)
	{
		count += ft_put_char('-');
		num = -num;
	}
	if (num > 9)
		count += ft_put_nbr(num / 10);
	count += ft_put_char((num % 10) + 48);
	return (count);
}

//? ft_puthex
int ft_put_hex(unsigned int nb)
{
	char *hex = "0123456789abcdef";
	int count = 0;

	if (nb > 15)
		count += ft_put_hexa(nb / 16);
	count += ft_put_char(hex[nb % 16]);
	return (count);
}

//? ft_printf
int	ft_printf(const char *format, ...)
{
	va_list args;
	int i = 0;
	int count = 0;

	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			if (format[i] == 's')
				count += ft_put_str(va_arg(args, char *));
			else if (format[i] == 'd')
				count += ft_put_nbr(va_arg(args, int));
			else if (format[i] == 'x')
				count += ft_put_hex(va_arg(args, unsigned int));
		}
		else
			count += ft_put_char(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}

//* -------------------------------------

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