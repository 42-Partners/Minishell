/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 23:23:58 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/21 23:23:58 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "exec.h"
#include "libft.h"
#include "error_handling.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int			handle_pipe(t_ast_node *node, t_shell *shell,
				pid_t *pid_left, pid_t *pid_right);
void		exec_pipe_child(t_ast_node *node, t_shell *shell,
				int pipe_cmd[2], int n);
static int	check_cmd_node(t_ast_node *node, t_shell *shell);
static int	exec_high_level_node(t_ast_node *node, t_shell *shell);

int	check_cmds(t_ast_node **ast, t_shell *shell)
{
	int		ret;

	if (!*ast)
		return (ERROR);
	ret = check_cmd_node(*ast, shell);
	if (ret != OK)
		return (free_ast(ast), ret);
	return (OK);
}

int	exec_ast(t_ast_node *node, t_shell *shell)
{
	int	ret;

	ret = OK;
	if (node->type == CMD)
	{
		ret = exec_cmd(&(node->t_node.cmd_node), shell);
		return (ret);
	}
	return (exec_high_level_node(node, shell));
}

static int	exec_high_level_node(t_ast_node *node, t_shell *shell)
{
	pid_t	pid_left;
	pid_t	pid_right;

	if (node->type == PIPE)
	{
		if (handle_pipe(node, shell, &pid_left, &pid_right) != OK)
			return (FAIL);
		waitpid(pid_left, NULL, 0);
		waitpid(pid_right, &shell->status, 0);
		shell->status = shell->status >> 8;
		return (OK);
	}
	return (ERROR);
}

static int	check_cmd_node(t_ast_node *node, t_shell *shell)
{
	int		ret;

	ret = OK;
	if (node->type == CMD)
	{
		if (node->t_node.cmd_node.cmd != NULL)
			ret = validate_cmd(node->t_node.cmd_node.cmd, shell);
		return (ret);
	}
	else if (node->type == LOGICAL)
	{
		ret = check_cmd_node(node->t_node.logical_node.left, shell);
		if (ret == OK)
			return (check_cmd_node(node->t_node.logical_node.right, shell));
	}
	else if (node->type == PIPE)
	{
		ret = check_cmd_node(node->t_node.pipe_node.left, shell);
		if (ret == OK)
			return (check_cmd_node(node->t_node.pipe_node.right, shell));
	}
	return (ret);
}
