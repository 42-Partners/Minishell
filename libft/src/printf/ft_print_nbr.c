/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:55:01 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/08/12 12:37:14 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_s_nbr(int n)
{
	int	res;

	res = 0;
	if (n == -2147483648)
	{
		res = ft_print_str("-2147483648");
		return (res);
	}
	if (n < 0)
	{
		n *= -1;
		res += ft_print_char('-');
	}
	res += ft_print_u_nbr((unsigned int)n);
	return (res);
}

int	ft_print_u_nbr(unsigned int n)
{
	int	res;

	res = 0;
	if (n > 9)
	{
		res += ft_print_u_nbr(n / 10);
		res += ft_print_u_nbr(n % 10);
	}
	else
		res += ft_print_char(n + '0');
	return (res);
}
