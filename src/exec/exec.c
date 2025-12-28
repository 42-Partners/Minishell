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
#include "exec.h"
#include "error_handling.h"

static int	check_cmd_node(t_ast_node *node, char *envv[]);
static int	exec_high_level_node(t_ast_node *node, char *envv[], int *stts);

int	check_cmds(t_ast_node **ast, char *envv[])
{
	if (!*ast)
		return (ERROR);
	if (check_cmd_node(*ast, envv) == FAIL)
		return (free_ast(ast), FAIL);
	return (OK);
}	

int	exec_ast(t_ast_node *node, char *envv[], int *status)
{
	if (node->type == CMD)
	{
		*status = exec_cmd(node->t_node.cmd_node, envv);
		return (*status);
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
		return (OK); //! aqui estava 1, mas se nao tem CMD e nao é um redirect, nao é erro de malloc la na funçao consume_tokens?
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
	return (FAIL);
}
