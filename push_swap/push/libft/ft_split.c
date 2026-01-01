/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:47:08 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/08/21 13:08:47 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	size_t	i;
	int		count;
	int		in;

	i = 0;
	count = 0;
	in = 0;
	while (s[i])
	{
		if (s[i] != c && in == 0)
		{
			in = 1;
			count++;
		}
		else if (s[i] == c)
			in = 0;
		i++;
	}
	return (count);
}

static char	*fill(const char *s, size_t start, size_t end)
{
	size_t		len;
	char		*word;

	len = end - start;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_memcpy(word, s + start, len);
	word[len] = '\0';
	return (word);
}

static void	freeing(char **result, size_t j)
{
	while (j > 0)
	{
		j--;
		free(result[j]);
	}
	free(result);
}

static int	next_word(char const *s, char c, size_t *i, size_t *start)
{
	while (s[*i] == c)
		(*i)++;
	*start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	return (*i > *start);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	result = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (s[i])
	{
		if (next_word(s, c, &i, &start))
		{
			result[j] = fill(s, start, i);
			if (!result[j])
				return (freeing(result, j), NULL);
			j++;
		}
	}
	return (result[j] = NULL, result);
}
/*
#include <stdio.h>
int main(void)
{
    char **res = ft_split("  Hello  World", ' ');
    int i = 0;

    while (res && res[i])
    {
        printf("Word %d: %s\n", i, res[i]);
        free(res[i]);
        i++;
    }
    free(res);
}*/
