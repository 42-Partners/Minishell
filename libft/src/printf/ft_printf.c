/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:11:21 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/12/12 15:12:59 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, format);
	res = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1))
			res += ft_conversion_specifier(*(++format), ap);
		else
			res += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (res);
}
