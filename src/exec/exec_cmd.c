/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:33:02 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/23 12:33:02 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "exec.h"
#include "libft.h"
#include "error_handling.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int			is_builtin(t_cmd_node *cmd);
int			exec_builtin(t_cmd_node *cmd, t_shell *shell);
static void	exec_and_redirect(char *exec, t_cmd_node *cmd, char *envv[]);
static void	launch_command(t_cmd_node *cmd, char *exec, t_shell *shell);
static int	wait_child(int pid);

int	exec_cmd(t_cmd_node *cmd, t_shell *shell)
{
	pid_t	pid;
	char	*exec;
	int		ret;

	ret = OK;
	exec = NULL;
	expand_cmd(cmd, shell);
	if (!cmd->cmd)
		return (OK);
	if (is_builtin(cmd))
		return (exec_builtin(cmd, shell));
	ret = get_cmd_path(&exec, cmd->cmd, shell->envv);
	if (ret != OK)
		return (ret);
	pid = fork();
	if (pid == -1)
		return (perror("Error"), FAIL);
	if (pid == 0)
		launch_command(cmd, exec, shell);
	free(exec);
	shell->status = wait_child(pid);
	if (shell->status > 0)
		return (FAIL);
	return (OK);
}

static void	launch_command(t_cmd_node *cmd, char *exec, t_shell *shell)
{
	if (!cmd->cmd)
	{
		exec_redirects(cmd);
		execve("/usr/bin/true", (char *[]){NULL}, shell->envv);
		perror("Error");
		exit (0);
	}
	else
		exec_and_redirect(exec, cmd, shell->envv);
}

static void	exec_and_redirect(char *exec, t_cmd_node *cmd, char *envv[])
{
	int	i;

	if (exec_redirects(cmd) == ERROR)
		exit(0);
	i = 3;
	while (i < 1024)
		close(i++);
	execve(exec, cmd->args, envv);
	perror("Error");
	exit(0);
}

static int	wait_child(int pid)
{
	int	ret;

	waitpid(pid, &ret, 0);
	while (wait(NULL) > 0)
		;
	return (ret >> 8);
}
