/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:02:55 by codespace         #+#    #+#             */
/*   Updated: 2025/12/22 23:51:23 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	size_t	s1_len;
	size_t	s2_len;
	size_t	str_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_len = s1_len + s2_len;
	strjoin = malloc(str_len + 1);
	if (!strjoin)
		return (NULL);
	ft_memcpy(strjoin, s1, s1_len);
	ft_memcpy(strjoin + s1_len, s2, s2_len);
	strjoin[str_len] = '\0';
	return (strjoin);
}
