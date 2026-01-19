/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:05:15 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/15 20:31:31 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_printchar_fd(char c, int fd);

int	ft_printnbr_fd(long n, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n < 0)
	{
		count += ft_printchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
		count += ft_printnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	count += ft_printchar_fd(c, fd);
	return (count);
}

int	ft_printunbr_fd(unsigned long n, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n >= 10)
		count += ft_printunbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	count += ft_printchar_fd(c, fd);
	return (count);
}
