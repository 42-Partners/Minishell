/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:58:28 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/20 19:58:28 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	validate_ast_node(t_ast_node *node);
static int	validate_cmd(t_cmd_node cmd);
static int	validate_high_level(t_node_type type, t_ast_node *node);

void	validate_ast(t_ast_node **ast)
{
	if (!ast || !*ast)
		return ;
	if (validate_ast_node(*ast) < 0)
	{
		free_ast(ast);
		return ;
	}
	debug_flag("No sintax errors...");
}

static int	validate_ast_node(t_ast_node *node)
{
	if (!node)
		return (-1);
	if (node->type == CMD)
		return (validate_cmd(node->t_node.cmd_node));
	else if (node->type == LOGICAL || node->type == PIPE)
		return (validate_high_level(node->type, node));
	return (-1);
}

static int	validate_cmd(t_cmd_node cmd)
{
	int	i;

	i = -1;
	if (!cmd.cmd && cmd.redirect_count == 0)
		debug_flag("cmd_node in ast is blank!!");
	while (++i < cmd.redirect_count)
	{
		if (!cmd.redirects[i]->file_name)
		{
			write(1, "syntax error near token '", 25);
			if (cmd.redirects[i]->type == REDIRECT_IN)
				write(1, "<'\n", 3);
			else if (cmd.redirects[i]->type == REDIRECT_OUT)
				write(1, ">'\n", 3);
			else if (cmd.redirects[i]->type == REDIRECT_APPEND)
				write(1, ">>'\n", 4);
			else if (cmd.redirects[i]->type == HERE_DOC)
				write(1, "<<'\n", 4);
			return (-1);
		}
	}
	return (1);
}

static int	validate_high_level(t_node_type type, t_ast_node *node)
{
	t_ast_node	*left;
	t_ast_node	*right;

	if (type == LOGICAL)
	{
		left = node->t_node.logical_node.left;
		right = node->t_node.logical_node.right;
	}
	else if (type == PIPE)
	{
		left = node->t_node.pipe_node.left;
		right = node->t_node.pipe_node.right;
	}
	else
		return (-1);
	if (type == PIPE && (!left || !right))
		write(1, "syntax error near token '|'\n", 28);
	else if (type == LOGICAL && (!left || !right))
		write(1, "syntax error near logical token\n", 32);
	if (validate_ast_node(left) > 0 && validate_ast_node(right) > 0)
		return (1);
	return (-1);
}
