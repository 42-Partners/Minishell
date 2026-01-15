/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:17:58 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/15 18:17:58 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "exec.h"
#include "libft.h"
#include "error_handling.h"

#include <unistd.h>
#include <stdio.h>

int	is_arg_valid(char *arg);
int	convert_exit_status(int arg);

int	ft_exit(t_shell *shell, char **args)
{
	int	exit_status;

	exit_status = 2;
	if (args[1])
	{
		if (args[2])
			return (ft_putstr_fd("exit: too many args\n", 2), FAIL);
		else if (is_arg_valid(args[1]))
			exit_status = convert_exit_status(ft_atoi(args[1]));
		else
			ft_putstr_fd("exit: numeric arg required :(\n", 2);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (shell->ast)
		free_ast(&shell->ast);
	ft_free_arr(&shell->envv);
	write(STDERR_FILENO, "exit: Bye Bye\n", 15);
	close(STDERR_FILENO);
	exit(exit_status);
}

int	is_arg_valid(char *arg)
{
	if (ft_atol(arg) != (long)ft_atoi(arg))
		return (0);
	while (*arg == 32 || (*arg >= 9 && *arg <= 13))
		arg++;
	if(*arg == '-' || *arg == '+')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

int	convert_exit_status(int arg)
{
	if (arg > 255)
	{
		while (arg > 255)
			arg -= 256;
	}
	if (arg < 0)
	{
		while (arg < 0)
			arg += 256;
	}
	return (arg);
}
