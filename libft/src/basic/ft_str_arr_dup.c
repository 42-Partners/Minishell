/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 07:34:29 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/28 16:57:35 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_str_arr_dup(char **str_array);

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
		duplicate[i] = ft_strdup(str_array[i]);
		if (!duplicate[i])
		{
			while (--i >= 0)
				free(duplicate[i]);
			return (free(duplicate), NULL);
		}
		i++;
	}
	duplicate[i] = NULL;
	return (duplicate);
}
