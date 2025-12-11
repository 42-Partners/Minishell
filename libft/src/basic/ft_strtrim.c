/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:25:25 by codespace         #+#    #+#             */
/*   Updated: 2025/08/04 13:16:47 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]) != NULL)
		i++;
	start = i;
	if (!s1[start])
		return (ft_strdup(""));
	i = ft_strlen(s1);
	while (i > 0 && ft_strchr(set, s1[i - 1]) != NULL)
		i--;
	end = i - 1;
	return (ft_substr(s1, start, end - start + 1));
}
