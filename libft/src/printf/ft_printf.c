/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:11:21 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/08/12 12:35:30 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
