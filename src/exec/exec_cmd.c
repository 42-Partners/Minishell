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

int	exec_cmd(t_cmd_node cmd, char *envv[])
{
	pid_t	pid;
	char	*exec;
	int		i;

	if (!cmd.cmd)
		return (1);
	exec = get_cmd_path(cmd.cmd, envv);
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Fork error:\n");
		return (-1);
	}
	if (pid == 0)
	{
		i = 3;
		while (i < 1024)
			close(i++);
		execve(exec, cmd.args, envv);
		return (-1);
	}
	while (wait(NULL) > 0)
		;
	free(exec);
	return (1);
}
