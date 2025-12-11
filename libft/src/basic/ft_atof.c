/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:25:07 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/11/06 15:25:34 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *nptr)
{
	double	signal;
	double	res;
	double	div;

	signal = 1;
	res = 0.0;
	div = 1.0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
		res = res * 10 + (*nptr++ - '0');
	if (*nptr == '.')
	{
		nptr++;
		while (*nptr >= '0' && *nptr <= '9')
			res += ((*nptr++ - '0') / (div *= 10));
	}
	return (res * signal);
}
