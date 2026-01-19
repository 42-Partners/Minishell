/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:08:30 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/12/12 15:13:11 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_pointer(void *ptr)
{
	unsigned long	address;
	int				res;

	if (!ptr)
		return (ft_print_str("(nil)"));
	address = (unsigned long)ptr;
	res = 0;
	res += ft_print_str("0x");
	res += ft_print_hexa_long(address);
	return (res);
}
