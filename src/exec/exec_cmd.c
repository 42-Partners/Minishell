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

static int	wait_child(int pid);

int	exec_cmd(t_cmd_node cmd, char *envv[])
{
	pid_t	pid;
	char	*exec;
	int		i;
	int		ret;

	if (!cmd.cmd)
		return (1);
	exec = get_cmd_path(cmd.cmd, envv);
	if (!exec)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (ft_printf("Fork error:\n"), -1);
	if (pid == 0)
	{
		i = 3;
		while (i < 1024)
			close(i++);
		execve(exec, cmd.args, envv);
		return (-1);
	}
	ret = wait_child(pid);
	return (free(exec), ret);
}

static int	wait_child(int pid)
{
	int	ret;

	waitpid(pid, &ret, 0);
	while (wait(NULL) > 0)
		;
	return (ret >> 8);
}
