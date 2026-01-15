/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:07:33 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/15 19:16:46 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		count += ft_puthex_fd(n / 16, fd, upper);
	count += ft_putchar_fd(base[n % 16], fd);
	return (count);
}
