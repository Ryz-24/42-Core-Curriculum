/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_part2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:45:25 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/09/02 14:04:22 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_lower_hex(unsigned int nbr) // %x
{
	char	*hex;
	int		len;

	hex = "0123456789abcdef";
	len = 0;
	if (nbr >= 16)
		len += ft_putnbr_lower_hex(nbr / 16);
	len += ft_putchar(hex[nbr % 16]);
	return (len);
}

int	ft_putnbr_upper_hex(unsigned int nbr) // %X
{
	char	*hex;
	int		len;

	hex = "0123456789ABCDEF";
	len = 0;
	if (nbr >= 16)
		len += ft_putnbr_upper_hex(nbr / 16);
	len += ft_putchar(hex[nbr % 16]);
	return (len);
}

int	ft_putptr(unsigned long long ptr) // %p
{
	char	*hex;
	int		len;

	hex = "0123456789abcdef";
	len = 0;
	if (ptr >= 16)
		len += ft_putptr(ptr / 16);
	len += ft_putchar(hex[ptr % 16]);
	return (len);
}
