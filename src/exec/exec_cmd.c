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

static int	redirect_without_cmd(t_cmd_node *cmd);
static void	exec_and_redirect(char *exec, t_cmd_node *cmd, char *envv[]);
static void	wait_child(void);

int	exec_cmd(t_cmd_node cmd, char *envv[])
{
	pid_t	pid;
	char	*exec;

	if (!cmd.cmd)
		return (redirect_without_cmd(&cmd));
	exec = get_cmd_path(cmd.cmd, envv);
	if (!exec)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Fork error:\n");
		return (-1);
	}
	if (pid == 0)
		exec_and_redirect(exec, &cmd, envv);
	wait_child();
	return (free(exec), 1);
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

static int	redirect_without_cmd(t_cmd_node *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_printf("Fork error:\n");
		return (-1);
	}
	if (pid == 0)
	{
		if (exec_redirects(cmd) != -1)
			return (-1);
		exit(0);
	}
	return (0);
}

static void	wait_child(void)
{
	while (wait(NULL) > 0)
		;
}
