/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:50:33 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/12/12 15:14:37 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(char *str)
{
	int	res;

	if (!str)
		return (ft_print_str("(null)"));
	res = 0;
	while (*str)
	{
		res += ft_print_char(*str);
		str++;
	}
	return (res);
}
