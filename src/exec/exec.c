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
	int	ret;

	if (!*ast)
		return (ERROR);
	ret = check_cmd_node(*ast, envv);
	if (ret != OK)
		return (free_ast(ast), ret);
	return (OK);
}

int	exec_ast(t_ast_node *node, char *envv[], int *status)
{
	int	ret;

	ret = OK;
	if (node->type == CMD)
	{
		ret = exec_cmd(&(node->t_node.cmd_node), envv, &status);
		return (ret);
	}
	return (exec_high_level_node(node, envv, status));
}

static int	exec_high_level_node(t_ast_node *node, char *envv[], int *stts)
{
	int	ret;

	ret = OK;
	if (node->type == LOGICAL)
	{
		ret = exec_ast(node->t_node.logical_node.left, envv, stts);
		if (ret == OK)
		{
			if (node->t_node.logical_node.type == AND)
				return (exec_ast(node->t_node.logical_node.right, envv, stts));
			return (ret);
		}
		else if (node->t_node.logical_node.type == OR && ret != ERROR)
			return (exec_ast(node->t_node.logical_node.right, envv, stts));
	}
	else if (node->type == PIPE)
	{
		if (exec_ast(node->t_node.pipe_node.left, envv, stts) != ERROR)
			return (exec_ast(node->t_node.pipe_node.right, envv, stts));
	}
	return (ERROR);
}

static int	check_cmd_node(t_ast_node *node, char *envv[])
{
	int	ret;

	ret = OK;
	if (node->type == CMD)
	{
		if (node->t_node.cmd_node.cmd != NULL)
			ret = validate_cmd(node->t_node.cmd_node.cmd, envv);
		return (ret);
	}
	else if (node->type == LOGICAL)
	{
		ret = check_cmd_node(node->t_node.logical_node.left, envv);
		if (ret == OK)
			return (check_cmd_node(node->t_node.logical_node.right, envv));
	}
	else if (node->type == PIPE)
	{
		ret = check_cmd_node(node->t_node.pipe_node.left, envv);
		if (ret == OK)
			return (check_cmd_node(node->t_node.pipe_node.right, envv));
	}
	return (ret);
}
