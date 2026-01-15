/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:04:22 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/15 19:16:28 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
