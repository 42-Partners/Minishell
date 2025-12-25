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

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "ast.h"
#include "minishell.h"
#include "ast.h"

static int	check_cmd_node(t_ast_node *node, char *envv[]);
static int	exec_high_level_node(t_ast_node *node, char *envv[], int *stts);

void	check_cmds(t_ast_node **ast, char *envv[])
{
	if (!*ast)
		return ;
	if (check_cmd_node(*ast, envv) == -1)
		free_ast(ast);
}

int	exec_ast(t_ast_node *node, char *envv[], int *status)
{
	int	ret;
	int	std[2];

	ret = -1;
	if (node->type == CMD)
	{
		std[0] = dup(STDIN_FILENO);
		std[1] = dup(STDOUT_FILENO);
		if (std[0] == -1 || std[1] == -1)
		{
			close(std[0]);
			close(std[1]);
			return (-1);
		}
		expand_ast(node, status);
		if (exec_redirects(&node->t_node.cmd_node) != -1)
			ret = exec_cmd(node->t_node.cmd_node, envv);
		dup2(std[0], STDIN_FILENO);
		dup2(std[1], STDOUT_FILENO);
		close(std[0]);
		close(std[1]);
		*status = ret;
		return (ret);
	}
	return (exec_high_level_node(node, envv, status));
}

static int	exec_high_level_node(t_ast_node *node, char *envv[], int *stts)
{
	int	ret;

	if (node->type == LOGICAL)
	{
		ret = exec_ast(node->t_node.logical_node.left, envv, stts);
		if (ret == 0)
		{
			if (node->t_node.logical_node.type == AND)
				return (exec_ast(node->t_node.logical_node.right, envv, stts));
			return (ret);
		}
		else if (node->t_node.logical_node.type == OR && ret != -1)
			return (exec_ast(node->t_node.logical_node.right, envv, stts));
	}
	else if (node->type == PIPE)
	{
		if (exec_ast(node->t_node.pipe_node.left, envv, stts) != -1)
			return (exec_ast(node->t_node.pipe_node.right, envv, stts));
	}
	return (-1);
}

static int	check_cmd_node(t_ast_node *node, char *envv[])
{
	if (node->type == CMD)
	{
		if (node->t_node.cmd_node.cmd != NULL)
			return (validate_cmd(node->t_node.cmd_node.cmd, envv));
		return (1);
	}
	else if (node->type == LOGICAL)
	{
		if (check_cmd_node(node->t_node.logical_node.left, envv) != -1)
			return (check_cmd_node(node->t_node.logical_node.right, envv));
	}
	else if (node->type == PIPE)
	{
		if (check_cmd_node(node->t_node.pipe_node.left, envv) != -1)
			return (check_cmd_node(node->t_node.pipe_node.right, envv));
	}
	return (-1);
}
