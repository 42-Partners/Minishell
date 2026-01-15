/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:04:22 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/15 20:33:13 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_printstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return (write(fd, "(null)", 6));
	i = 0;
	while (s[i])
		i++;
	return (write(fd, s, i));
}
