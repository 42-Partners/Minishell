/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:02:48 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/15 20:24:42 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

int	handle_format(int fd, char c, va_list ap);
int	ft_printchar_fd(char c, int fd);

int	ft_fprintf(int fd, const char *fmt, ...)
{
	va_list	ap;
	int		i;
	int		count;

	if (!fmt)
		return (-1);
	va_start(ap, fmt);
	i = 0;
	count = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1])
		{
			count += handle_format(fd, fmt[i + 1], ap);
			i += 2;
		}
		else
		{
			count += ft_printchar_fd(fmt[i], fd);
			i++;
		}
	}
	va_end(ap);
	return (count);
}
