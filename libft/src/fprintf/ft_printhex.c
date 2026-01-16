/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:07:33 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/15 20:31:09 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_printchar_fd(char c, int fd);

int	ft_printhex_fd(unsigned long n, int fd, int upper)
{
	int		count;
	char	*base;

	count = 0;
	if (upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		count += ft_printhex_fd(n / 16, fd, upper);
	count += ft_printchar_fd(base[n % 16], fd);
	return (count);
}
