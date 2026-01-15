/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:05:15 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/15 19:16:13 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_printnbr_fd(long n, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n < 0)
	{
		count += ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	count += ft_putchar_fd(c, fd);
	return (count);
}

int	ft_printunbr_fd(unsigned long n, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n >= 10)
		count += ft_putunbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	count += ft_putchar_fd(c, fd);
	return (count);
}
