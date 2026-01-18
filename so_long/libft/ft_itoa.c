/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:57:54 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/08/17 16:19:03 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digit_count(int n)
{
	long	num;
	size_t	count;

	num = n;
	count = 0;
	if (num == 0)
		count = 1;
	else if (num < 0)
	{
		num = -num;
		count = 1;
	}
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	len;
	long	num;
	char	*str;

	len = digit_count(n);
	num = n;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
/*
int main ()
{
	printf("after: %s\n", ft_itoa(0));
	printf("after: %s\n", ft_itoa(-12345));
	printf("after: %s\n", ft_itoa(-2147483648));
	printf("after: %s\n", ft_itoa(2147483647));
}*/
