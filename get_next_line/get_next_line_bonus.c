/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:32:12 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/09/29 17:14:01 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *s, char *p)
{
	if (s)
		free(s);
	if (p)
		free(p);
	return (NULL);
}

static char	*read_line(int fd, char *buffer)
{
	char	*temp;
	char	*to_read;
	int		bytes;

	bytes = 1;
	to_read = malloc(BUFFER_SIZE + 1);
	if (!to_read)
		return (ft_free(to_read, buffer));
	while (!ft_strchr(buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, to_read, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_free(to_read, buffer));
		to_read[bytes] = '\0';
		temp = ft_strjoin(buffer, to_read);
		if (!temp)
			return (ft_free(to_read, buffer));
		free(buffer);
		buffer = temp;
	}
	free(to_read);
	return (buffer);
}

static char	*extract_line(char *buffer)
{
	int			i;
	char		*temp;

	i = 0;
	if (!buffer || !buffer[0])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	temp = ft_substr(buffer, 0, i);
	if (!temp)
		return (NULL);
	return (temp);
}

static char	*trim_line(char *buffer)
{
	int			i;
	char		*result;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (ft_free(buffer, NULL));
	result = ft_strdup(buffer + i + 1);
	free(buffer);
	if (!result || *result == '\0')
		return (ft_free(result, NULL));
	return (result);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	if (!buffer[fd])
		return (NULL);
	buffer[fd] = read_line(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = extract_line(buffer[fd]);
	buffer[fd] = trim_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
/*
int main ()
{
	int     fd;
	char    *line;

	fd = open("test1.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file");
		return (1);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
