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

static void	exec_and_redirect(char *exec, t_cmd_node *cmd, t_shell *shell);
static void	launch_command(t_cmd_node *cmd, char *exec, t_shell *shell);
static int	wait_child(int pid);

int	exec_cmd(t_cmd_node *cmd, t_shell *shell, int pipe)
{
	pid_t	pid;
	char	*exec;
	int		ret;

	handle_wildcard(&cmd, shell);
	expand_cmd(cmd, shell);
	exec = NULL;
	if (cmd->cmd)
	{
		if (is_builtin(cmd->cmd))
			return (exec_builtin(cmd, shell, pipe));
		ret = get_cmd_path(&exec, cmd->cmd, shell->envp);
		if (ret != OK)
			return (ret);
	}
	pid = fork();
	if (pid == 0)
		launch_command(cmd, exec, shell);
	if (pid == -1)
		return (ft_putstr_fd("pipe Error :(", 2), ERROR);
	shell->status = wait_child(pid);
	free(exec);
	if (shell->status > 0)
		return (FAIL);
	return (OK);
}

static void	launch_command(t_cmd_node *cmd, char *exec, t_shell *shell)
{
	if (!cmd->cmd)
	{
		exec_redirects(cmd);
		free(exec);
		exec_exit(shell, OK);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_and_redirect(exec, cmd, shell);
	}
}

static void	exec_and_redirect(char *exec, t_cmd_node *cmd, t_shell *shell)
{
	int	i;

	if (exec_redirects(cmd) == ERROR)
		exec_exit(shell, FAIL);
	i = 3;
	while (i < 1024)
		close(i++);
	execve(exec, cmd->args, shell->envp);
	ft_putstr_fd("execve failed :(\n", 2);
	free(exec);
	exec_exit(shell, FAIL);
}

static int	wait_child(int pid)
{
	int	status;
	int	sig;

	ignore_sig_handlers();
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	register_sig_handlers();
	sig = status & 0x7F;
	if (sig != 0)
	{
		if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		return (128 + sig);
	}
	return ((status >> 8) & 0xFF);
}
