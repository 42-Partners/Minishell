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

#include "libft.h"
#include "ast.h"
#include "error_handling.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	validate_ast_node(t_ast_node *node);
static int	validate_cmd(t_cmd_node cmd);
static int	validate_high_level(t_node_type type, t_ast_node *node);
static int	validate_ast_children(t_ast_node *left, t_ast_node *right);

int	validate_ast(t_ast_node **ast)
{
	int	ret;

	ret = OK;
	if (!ast || !*ast)
		return (ERROR);
	ret = validate_ast_node(*ast);
	if (ret != OK)
		return (free_ast(ast), ret);
	return (OK);
}

static int	validate_ast_node(t_ast_node *node)
{
	if (!node)
		return (ERROR);
	if (node->type == CMD)
		return (validate_cmd(node->t_node.cmd_node));
	else if (node->type == LOGICAL || node->type == PIPE)
		return (validate_high_level(node->type, node));
	return (OK);
}

static int	validate_cmd(t_cmd_node cmd)
{
	int	i;

	i = -1;
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
			return (FAIL);
		}
	}
	return (OK);
}

static int	validate_high_level(t_node_type type, t_ast_node *node)
{
	t_ast_node	*left;
	t_ast_node	*right;

	if (type == LOGICAL)
	{
		left = node->t_node.logical_node.left;
		right = node->t_node.logical_node.right;
		if ((!left || !right))
			ft_putstr_fd("syntax error near logical token\n", 2);
	}
	else if (type == PIPE)
	{
		left = node->t_node.pipe_node.left;
		right = node->t_node.pipe_node.right;
		if (!left || !right)
			return (ft_putstr_fd("syntax error near token '|'\n", 2), FAIL);
	}
	else
		return (ERROR);
	return (validate_ast_children(left, right));
}

static int	validate_ast_children(t_ast_node *left, t_ast_node *right)
{
	int	ret;

	ret = validate_ast_node(left);
	if (ret != OK)
		return (ret);
	ret = validate_ast_node(right);
	if (ret != OK)
		return (ret);
	return (OK);
}
