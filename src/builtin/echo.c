/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:16:20 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/18 17:42:08 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error_handling.h"

static int	is_n_flag(char *arg);

int	ft_echo(t_shell *shell, char **args)
{
	int	newline;
	int	i;

	shell->status = 1;
	newline = 1;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_fprintf(1, "%s", args[i]);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	shell->status = 0;
	return (OK);
}

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
