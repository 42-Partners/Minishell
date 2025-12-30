/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 06:45:55 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/30 08:41:20 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include "minishell.h"

int	ft_echo(char **args, char *envp[]);

int	is_builtin(t_cmd_node *cmd)
{
	char	*cmd_expanded;

	cmd_expanded; //dup and expand cmd
	if (!cmd->cmd)
		return (0);
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (1);
	return (0);
}

void	exec_builtin(t_cmd_node *cmd, char **envp[], int *status)
{
	pid_t	pid;
	int		ret;

	//expand cmd
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Fork error:\n");
		exit(1);
	}
	if (pid == 0)
	{
		if (exec_redirects(cmd) == -1)
			exit(1);
		find_builtin(cmd->cmd, cmd->args, envp);
		exit(0);
	}
	ret = waitpid(pid, &ret, 0);
	*status = ret >> 8;
}

static void	find_builtin(char *cmd, char **args, char *envp[])
{
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(args, envp);
}
