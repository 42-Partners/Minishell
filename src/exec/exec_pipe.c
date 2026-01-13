/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:53:54 by rafaoliv          #+#    #+#             */
/*   Updated: 2026/01/12 20:55:39 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "error_handling.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int			exec_ast(t_ast_node *node, t_shell *shell);
static void	exec_pipe_child(t_ast_node *node, t_shell *shell,
				int pipe_cmd[2], int n);

int	exec_pipe(t_ast_node *node, t_shell *shell,
	pid_t *pid_left, pid_t *pid_right)
{
	int		pipe_cmd[2];

	if (pipe(pipe_cmd) == -1)
		return (perror("Error"), FAIL);
	*pid_left = fork();
	if (*pid_left == -1)
	{
		close(pipe_cmd[0]);
		close(pipe_cmd[1]);
		return (perror("Error"), FAIL);
	}
	if (*pid_left == 0)
		exec_pipe_child(node, shell, pipe_cmd, 1);
	*pid_right = fork();
	if (*pid_right == -1)
	{
		close(pipe_cmd[0]);
		close(pipe_cmd[1]);
		return (perror("Error"), FAIL);
	}
	if (*pid_right == 0)
		exec_pipe_child(node, shell, pipe_cmd, 0);
	close(pipe_cmd[0]);
	close(pipe_cmd[1]);
	return (OK);
}

static void	exec_pipe_child(t_ast_node *node, t_shell *shell,
	int pipe_cmd[2], int n)
{
	if (n == 1)
	{
		dup2(pipe_cmd[n], STDOUT_FILENO);
		close(pipe_cmd[0]);
		close(pipe_cmd[1]);
		exec_ast(node->t_node.pipe_node.left, shell);
	}
	else if (n == 0)
	{
		dup2(pipe_cmd[n], STDIN_FILENO);
		close(pipe_cmd[0]);
		close(pipe_cmd[1]);
		exec_ast(node->t_node.pipe_node.right, shell);
	}
	exit(shell->status);
}
