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

static int	is_arg_valid(char *arg);
static void	exit_cleanup(t_shell *shell, int pipe);

int	ft_exit(t_shell *shell, char **args, int pipe)
{
	int	exit_status;

	exit_status = shell->status;
	if (args && args[1])
	{
		if (!is_arg_valid(args[1]))
		{
			ft_fprintf(2, "exit: %s: numeric argument required\n", args[1]);
			exit_status = 2;
		}
		else if (args[2])
		{
			shell->status = 1;
			return (ft_fprintf(2, "exit: too many arguments\n"), FAIL);
		}
		else
			exit_status = (unsigned char)ft_atoi(args[1]);
	}
	exit_cleanup(shell, pipe);
	exit(exit_status);
}

static int	is_arg_valid(char *arg)
{
	if (ft_atol(arg) != (long)ft_atoi(arg))
		return (0);
	while (*arg == 32 || (*arg >= 9 && *arg <= 13))
		arg++;
	if (*arg == '-' || *arg == '+')
		arg++;
	if (!*arg)
		return (0);
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

static void	exit_cleanup(t_shell *shell, int pipe)
{
	if (!pipe)
		ft_fprintf(1, "exit\n");
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (shell->ast)
		free_ast(&shell->ast);
	ft_free_arr(&shell->envp);
	close(STDERR_FILENO);
}
