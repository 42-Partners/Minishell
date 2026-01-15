/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:00:19 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/15 20:29:54 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

int	ft_printchar_fd(char c, int fd);
int	ft_printstr_fd(char *s, int fd);
int	ft_printnbr_fd(long n, int fd);
int	ft_printunbr_fd(unsigned long n, int fd);
int	ft_printhex_fd(unsigned long n, int fd, int upper);

int	handle_format(int fd, char c, va_list ap)
{
	if (c == 'c')
		return (ft_printchar_fd(va_arg(ap, int), fd));
	if (c == 's')
		return (ft_printstr_fd(va_arg(ap, char *), fd));
	if (c == 'd' || c == 'i')
		return (ft_printnbr_fd(va_arg(ap, int), fd));
	if (c == 'u')
		return (ft_printunbr_fd(va_arg(ap, unsigned int), fd));
	if (c == 'x')
		return (ft_printhex_fd(va_arg(ap, unsigned int), fd, 0));
	if (c == 'X')
		return (ft_printhex_fd(va_arg(ap, unsigned int), fd, 1));
	if (c == '%')
		return (ft_printchar_fd('%', fd));
	return (0);
}
