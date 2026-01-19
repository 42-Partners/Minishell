/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 07:34:29 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/19 14:40:24 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_str_arr_dup(char **str_array);

static char	*handle_shlvl(char *og)
{
	char	*tmp;
	char	*res;
	char	*value;

	tmp = ft_strdup("SHLVL=");
	if (!tmp)
		return (NULL);
	value = ft_itoa(ft_atoi(og + 6) + 1);
	if (!value)
	{
		free(tmp);
		return (NULL);
	}
	res = ft_strjoin(tmp, value);
	free(tmp);
	free(value);
	return (res);
}

char	**ft_str_arr_dup(char **str_array)
{
	char	**duplicate;
	int		i;

	i = 0;
	while (str_array[i])
		i++;
	duplicate = malloc((i + 1) * sizeof(char *));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (str_array[i])
	{
		if (ft_strncmp(str_array[i], "SHLVL=", 6) == 0)
			duplicate[i] = handle_shlvl(str_array[i]);
		else
			duplicate[i] = ft_strdup(str_array[i]);
		if (!duplicate[i])
			ft_free_arr(&duplicate);
		i++;
	}
	duplicate[i] = NULL;
	return (duplicate);
}
