
#include <unistd.h>
#include <stdarg.h>

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}


int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (ft_putstr("(null)"));
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}




int	ft_put_decimal(int n)
{
	int	c;

	c = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		c += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		c += ft_put_decimal(n / 10);
	c += ft_putchar((n % 10) + '0');
	return (c);
}


int	ft_puthex1(unsigned int n)
{
	char *p;
	int i;
	
	i = 0;
	p = "0123456789abcdef";
	if(n >= 16)
		i += ft_puthex1(n / 16);
	i += ft_putchar(p[n % 16]);
	return (i);
}

int	ft_printf(const char *fmt, ...)
{
	int		i;
	int		c;
	va_list	ptr;

	i = 0;
	c = 0;
	va_start(ptr, fmt);
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			i++;
			if (fmt[i] == '\0')
				break ;
			if (fmt[i] == 's')
				c += (ft_putstr(va_arg(ptr, char *)));
			else if (fmt[i] == 'd')
				c += ft_put_decimal(va_arg(ptr, int));
			else if (fmt[i] == 'x')
				c += ft_puthex1(va_arg(ptr, unsigned int));
			else
				c += ft_putchar(fmt[i]);
		}
		else
			c += ft_putchar(fmt[i]);
		i++;
	}
	va_end(ptr);
	return (c);
}


int main()
{
    int n1;
    int n2;
    int i = 6;
    n1 = ft_printf("%d", i);
    printf("\n");
    n2 = printf("%d", i);
    printf("\nn1 = %d n2 = %d\n", n1, n2);
}
