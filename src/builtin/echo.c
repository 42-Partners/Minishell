/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:16:20 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/12 20:41:02 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	while (args[++i] && ft_strcmp(args[i], "-n") == 0)
		newline = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i++], STDOUT_FILENO);
		if (args [i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
