/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:03:43 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/08/12 17:16:53 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = 0;
	dst_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	while (dst[dst_len] != '\0')
		dst_len++;
	if (dst_len >= size)
		return (src_len + size);
	while (src[i] != '\0' && (dst_len + i) < size - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if (dst_len + i < size)
		dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
/*
int main()
{
    char buffer[7] = "Hi";
    size_t len = ft_strlcat(buffer, " there", sizeof(buffer));
    printf("buffer: %s\n", buffer);
    printf("len: %zu\n", len);
}*/
