/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:16:20 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/13 19:19:14 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_echo(t_shell *shell, char **args)
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
	shell->status = 0;
	return (0);
}
