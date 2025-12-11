/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion_specifier.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:59:25 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/08/12 12:37:50 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_conversion_specifier(char c, va_list ap)
{
	int	res;

	res = 0;
	if (c == 'c')
		res += ft_print_char(va_arg(ap, int));
	else if (c == 's')
		res += ft_print_str(va_arg(ap, char *));
	else if (c == 'p')
		res += ft_print_pointer(va_arg(ap, void *));
	else if (c == 'i' || c == 'd')
		res += ft_print_s_nbr(va_arg(ap, int));
	else if (c == 'u')
		res += ft_print_u_nbr(va_arg(ap, unsigned int));
	else if (c == 'x' || c == 'X')
		res += ft_print_hexa(va_arg(ap, unsigned int), c);
	else if (c == '%')
		res += write(1, &c, 1);
	else
		res += write(1, &c, 1);
	return (res);
}
