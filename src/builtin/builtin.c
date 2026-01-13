/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 06:45:55 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/12 21:52:53 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "exec.h"
#include "libft.h"
#include "error_handling.h"

int			ft_echo(char **args);
static int	find_builtin(char *cmd, char **args);

int	is_builtin(t_cmd_node *cmd)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd_node *cmd, t_shell *shell)
{
	int	stdin;
	int	stdout;
	int	ret;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	ret = exec_redirects(cmd);
	if (ret != OK)
		return (ret);
	shell->status = find_builtin(cmd->cmd, cmd->args);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
	return (OK);
}

static int	find_builtin(char *cmd, char **args)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(args));
	return (OK);
}
