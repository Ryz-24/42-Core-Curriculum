/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:19:46 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/08/12 13:19:52 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*int main(void)
{
    printf("ft_isprint('A') = %d\n", ft_isprint('A'));
    printf("ft_isprint('!') = %d\n", ft_isprint('!'));
    printf("ft_isprint('\\n') = %d\n", ft_isprint('\n'));
}*/
