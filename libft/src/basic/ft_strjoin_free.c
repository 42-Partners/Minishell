/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:41:53 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/14 20:45:09 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	str_len;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = 0;
	if (s2)
		s2_len = ft_strlen(s2);
	str_len = s1_len + s2_len;
	str = malloc(str_len + 1);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	str[str_len] = '\0';
	free(s1);
	s1 = str;
	return (s1);
}
