/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:03:53 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/08/12 12:37:37 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hexa(unsigned int n, char c)
{
	char	*base;
	int		res;

	if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	res = 0;
	if (n >= 16)
	{
		res += ft_print_hexa((n / 16), c);
		res += ft_print_hexa((n % 16), c);
	}
	else
		res += ft_print_char(base[n % 16]);
	return (res);
}

int	ft_print_hexa_long(unsigned long n)
{
	char	*base;
	int		res;

	base = "0123456789abcdef";
	res = 0;
	if (n >= 16)
	{
		res += ft_print_hexa_long((n / 16));
		res += ft_print_hexa_long((n % 16));
	}
	else
		res += ft_print_char(base[n % 16]);
	return (res);
}
