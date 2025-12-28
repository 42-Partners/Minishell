/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 01:58:11 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/21 01:58:11 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

#include <stdlib.h>

static void	free_cmd(t_cmd_node node);

void	free_ast(t_ast_node **ast)
{
	t_ast_node	*node;

	if (!ast || !*ast)
		return ;
	node = *ast;
	if (node->type == CMD)
		free_cmd(node->t_node.cmd_node);
	else if (node->type == LOGICAL)
	{
		free_ast(&node->t_node.logical_node.left);
		free_ast(&node->t_node.logical_node.right);
	}
	else if (node->type == PIPE)
	{
		free_ast(&node->t_node.pipe_node.left);
		free_ast(&node->t_node.pipe_node.right);
	}
	free(node);
	*ast = NULL;
}

static void	free_cmd(t_cmd_node node)
{
	int	i;

	i = 0;
	if (node.args)
	{
		while (node.args[i])
			free(node.args[i++]);
	}
	i = 0;
	while (i < node.redirect_count)
	{
		if (node.redirects[i]->file_name)
			free(node.redirects[i]->file_name);
		free(node.redirects[i++]);
	}
	free(node.args);
	free(node.redirects);
}
