/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:12:56 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/08/04 13:15:50 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*set_str(char *str, long nl, long buffer)
{
	str[buffer] = '\0';
	buffer--;
	if (nl == 0)
	{
		str[buffer] = '0';
		return (str);
	}
	if (nl < 0)
	{
		nl = -nl;
		str[0] = '-';
	}
	while (nl > 9)
	{
		str[buffer] = (nl % 10) + '0';
		nl = nl / 10;
		buffer--;
	}
	str[buffer] = nl + '0';
	return (str);
}

static	long	buffer_size(long nl)
{
	long	i;

	i = 0;
	if (nl < 0)
	{
		nl = -nl;
		i++;
	}
	while (nl > 0)
	{
		nl = nl / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nl;
	char	*str;
	long	buffer;

	nl = (long)n;
	if (nl == 0)
		buffer = 1;
	else
		buffer = buffer_size(nl);
	str = malloc(buffer + 1);
	if (!str)
		return (NULL);
	return (set_str(str, nl, buffer));
}
