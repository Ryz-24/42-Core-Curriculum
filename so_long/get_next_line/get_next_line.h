/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:34:04 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/09/10 16:37:27 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h> 

size_t	g_strlen(const char *str);
char	*g_strdup(const char *s);
char	*g_strchr(char *s, int c);
char	*g_strjoin(char *s1, char *s2);
char	*g_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);

#endif
