/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:21:35 by codespace         #+#    #+#             */
/*   Updated: 2025/08/04 13:26:20 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*address;
	size_t	address_size;

	if (nmemb != 0 && size > (size_t)-1 / nmemb)
		return (NULL);
	address_size = (nmemb * size);
	if (address_size == 0)
		address_size = 1;
	address = malloc(address_size);
	if (!address)
		return (NULL);
	ft_bzero(address, address_size);
	return (address);
}
