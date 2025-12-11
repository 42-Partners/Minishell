/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:10:10 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/08/04 13:23:21 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s_cpy;
	size_t	len;

	len = ft_strlen(s);
	s_cpy = malloc((len + 1) * sizeof(char));
	if (!s_cpy)
		return (NULL);
	ft_memcpy(s_cpy, s, len);
	s_cpy[len] = '\0';
	return (s_cpy);
}
