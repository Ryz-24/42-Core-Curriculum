/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:00:17 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/27 15:16:07 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

int	ft_printf(const char *s, ...);
int	type(char c, va_list args);
int	ft_putchar(int c);
int	ft_putstr(char *s);
int	ft_putnbr(int nbr);
int	ft_putnbr_unsigned(unsigned int nbr);
int	ft_putnbr_lower_hex(unsigned int nbr);
int	ft_putnbr_upper_hex(unsigned int nbr);
int	ft_putptr(unsigned long long ptr);
int	ft_atoi(const char *nptr);

#endif
