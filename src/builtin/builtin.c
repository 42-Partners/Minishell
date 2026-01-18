/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 06:45:55 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/17 18:50:06 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "exec.h"
#include "libft.h"
#include "error_handling.h"

int			ft_echo(char **args);
int			ft_pwd(t_shell *shell, char **args);
int			ft_cd(t_shell *shell, char **argv);
int			ft_export(t_shell *shell, char **args);
int			ft_unset(t_shell *shell, char **args);
static int	find_builtin(t_shell *shell, char *cmd, char **args, int pipe);

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset"));
		|| !ft_strcmp(cmd, "exit"));
}

int	exec_builtin(t_cmd_node *cmd, t_shell *shell, int pipe)
{
	int	stdin;
	int	stdout;
	int	ret;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	ret = exec_redirects(cmd);
	if (ret != OK)
		return (ret);
	if (ft_strcmp(cmd->cmd, "exit") == 0)
	{
		close(stdin);
		close(stdout);
	}
	shell->status = find_builtin(shell, cmd->cmd, cmd->args, pipe);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
	return (OK);
}

static int	find_builtin(t_shell *shell, char *cmd, char **args, int pipe)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(shell, args));
	else if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(shell, args));
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(shell, args));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(shell, args));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(shell, args, pipe));
	return (FAIL);
}
