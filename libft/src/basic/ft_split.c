/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:49:10 by codespace         #+#    #+#             */
/*   Updated: 2025/08/04 13:32:55 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned int	words_counter(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

static	char	**memory_cleaner(char **array, unsigned int j)
{
	while (j-- > 0)
		free(array[j]);
	free(array);
	return (NULL);
}

static	char	**set_array(char **array, char const *s, char c)
{
	unsigned int	start;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			array[j] = ft_substr(s, start, (i - start));
			if (!array[j])
				return (memory_cleaner(array, j));
			j++;
		}
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char			**array;
	unsigned int	words;

	if (!s)
		return (NULL);
	words = words_counter(s, c);
	array = ft_calloc(words + 1, sizeof(char *));
	if (!array)
		return (NULL);
	return (set_array(array, s, c));
}
