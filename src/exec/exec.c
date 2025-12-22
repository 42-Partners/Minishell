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

#include "ast.h"
#include "minishell.h"

#include <stdlib.h>

static int	check_cmd_node(t_ast_node *node, char *envv[]);

void	check_cmds(t_ast_node **ast, char *envv[])
{
	if (!*ast)
		return;
	if (check_cmd_node(*ast, envv) == -1)
		free_ast(ast);
}

static int	check_cmd_node(t_ast_node *node, char *envv[])
{
	if (node->type == CMD && node->t_node.cmd_node.cmd)
		return (validate_cmd(node->t_node.cmd_node.cmd, envv));
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
