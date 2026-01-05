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
#include "exec.h"
#include "libft.h"
#include "error_handling.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

static void	exec_and_redirect(char *exec, t_cmd_node *cmd, char *envv[]);
static void	launch_command(t_cmd_node *cmd, char *envv[], char *exec, int **status);
static int	wait_child(int pid);

int	exec_cmd(t_cmd_node *cmd, char *envv[], int **status)
{
	pid_t	pid;
	char	*exec;
	int		ret;

	ret = OK;
	exec = NULL;
	if (cmd->cmd)
		ret = get_cmd_path(&exec, cmd->cmd, envv);
	if (ret != OK)
		return (ret);
	pid = fork();
	if (pid == ERROR)
		ft_putstr_fd("Fork error\n", 2);
	if (pid == OK)
		launch_command(cmd, envv, exec, status);
	if (cmd->cmd)
		free(exec);
	**status = wait_child(pid);
	if (**status > 0)
		return (FAIL);
	return (OK);
}

static void	launch_command(t_cmd_node *cmd, char *envv[], char *exec, int **status)
{
	expand_cmd(cmd, *status, envv);
	if (!cmd->cmd)
	{
		exec_redirects(cmd);
		execve("/usr/bin/true", (char[]){NULL}, envv);
		perror("Error");
		exit (FAIL);
	}
	else
		exec_and_redirect(exec, cmd, envv);
}

static void	exec_and_redirect(char *exec, t_cmd_node *cmd, char *envv[])
{
	int	i;

	if (exec_redirects(cmd) == ERROR)
		exit(FAIL);
	i = 3;
	while (i < 1024)
		close(i++);
	execve(exec, cmd->args, envv);
	perror("Error");
	exit(FAIL);
}

static int	wait_child(int pid)
{
	int	ret;

	waitpid(pid, &ret, 0);
	while (wait(NULL) > 0)
		;
	return (ret >> 8);
}
