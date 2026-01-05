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

#include "ast.h"
#include "minishell.h"
#include "libft.h"

#include <unistd.h>
#include <sys/wait.h>

static void	exec_and_redirect(char *exec, t_cmd_node *cmd, char *envv[]);
static int	wait_child(int pid);

int	exec_cmd(t_cmd_node *cmd, int *status, char *envv[])
{
	pid_t	pid;
	char	*exec;

	exec = NULL;
	if (cmd->cmd)
		exec = get_cmd_path(cmd->cmd, envv);
	pid = fork();
	if (pid == -1)
		return (ft_printf("Fork error:\n"), -1);
	if (pid == 0)
	{
		expand_cmd(cmd, status, envv);
		if (!cmd->cmd)
		{
			exec_redirects(cmd);
			execve("/usr/bin/true", (char *[]){NULL}, envv);
		}
		else
			exec_and_redirect(exec, cmd, envv);
	}
	if (cmd->cmd)
		free(exec);
	return (wait_child(pid));
}

static void	exec_and_redirect(char *exec, t_cmd_node *cmd, char *envv[])
{
	int	i;

	if (exec_redirects(cmd) == -1)
		exit(1);
	i = 3;
	while (i < 1024)
		close(i++);
	execve(exec, cmd->args, envv);
	exit(1);
}

static int	wait_child(int pid)
{
	int	ret;

	waitpid(pid, &ret, 0);
	while (wait(NULL) > 0)
		;
	return (ret >> 8);
}
