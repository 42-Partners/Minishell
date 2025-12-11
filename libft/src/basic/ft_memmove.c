/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:53:54 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/08/04 11:45:29 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*str;

	dst = (unsigned char *)dest;
	str = (unsigned char *)src;
	if (dst > str)
	{
		while (n-- > 0)
			dst[n] = str[n];
	}
	else if (dst < str)
		ft_memcpy(dest, src, n);
	return ((void *)dst);
}
