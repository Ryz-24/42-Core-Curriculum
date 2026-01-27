/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:45:57 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/09/11 13:07:42 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type(char c, va_list args)
{
	void	*ptr;

	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'p')
	{
		ptr = va_arg(args, void *);
		if (ptr == NULL)
			return (ft_putstr("(nil)"));
		else
			return (ft_putstr("0x") + ft_putptr((unsigned long long)ptr));
	}
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_putnbr_lower_hex(va_arg(args, unsigned int)));
	else if (c == 'X')
		return (ft_putnbr_upper_hex(va_arg(args, unsigned int)));
	else if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list		args;
	int			len;
	int			i;

	va_start(args, s);
	len = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			len += type(s[i], args);
			i++;
		}
		else
			len += ft_putchar(s[i++]);
	}
	va_end(args);
	return (len);
}
/*
int main()
{
    int len;
    char *ptr = "hello world";
    len = ft_printf("Pointer: %p\n", ptr);
    ft_printf("Len: %d\n", len);
    len = printf("Pointer: %p\n", ptr);
    ft_printf("Len: %d\n", len);
    
    len = ft_printf("Pointer: %p\n", (void *)0x1234abcd);
    ft_printf("Char: %c\n", 'A');
    ft_printf("String: %s\n", "Hello, world!");
    ft_printf("Decimal: %d\n", -1234);
    ft_printf("Integer: %i\n", 5678);
    ft_printf("Unsigned: %u\n", 4294967295u);
    ft_printf("Hex lowercase: %x\n", 3735928559u);
    ft_printf("Hex UPPERCASE: %X\n", 3735928559u);
    ft_printf("Percent: %%\n");
    ft_printf("Total printed characters: %d\n\n", len);
    
    len = printf("Pointer: %p\n", (void *)0x1234abcd);
    printf("Char: %c\n", 'A');
    printf("String: %s\n", "Hello, world!");
    printf("Decimal: %d\n", -1234);
    printf("Integer: %i\n", 5678);
    printf("Unsigned: %u\n", 4294967295u);
    printf("Hex lowercase: %x\n", 3735928559u);
    printf("Hex UPPERCASE: %X\n", 3735928559u);
    printf("Percent: %%\n");
    printf("Total printed characters: %d\n", len);
    return 0;
}*/
