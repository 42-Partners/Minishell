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
#include "error_handling.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	validate_ast_node(t_ast_node *node);
static int	validate_cmd(t_cmd_node cmd);
static int	validate_high_level(t_node_type type, t_ast_node *node);

int	validate_ast(t_ast_node **ast)
{
	if (!ast || !*ast)
		return (ERROR);
	if (!validate_ast_node(*ast))
		return (free_ast(ast), FAIL);
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
	return (-1);
}

static int	validate_cmd(t_cmd_node cmd)
{
	int	i;

	i = -1;
	if (!cmd.cmd && cmd.redirect_count == 0)
		debug_flag("cmd_node in ast is blank!!"); //! se nao tiver cmd é problema de malloc la na *consume_tokens, porem ela nao imprime mensagem de erro
	while (++i < cmd.redirect_count)
	{
		if (!cmd.redirects[i]->file_name)
		{
			write(1, "syntax error near unexpected token '", 25);
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
	}
	else if (type == PIPE)
	{
		left = node->t_node.pipe_node.left;
		right = node->t_node.pipe_node.right;
	}
	else
		return (-1);
	if (type == PIPE && (!left || !right))
		write(1, "syntax error near unexpected token '|'\n", 28);
	else if (type == LOGICAL && (!left || !right))
		write(1, "syntax error near logical token\n", 32);
	if (validate_ast_node(left) > 0 && validate_ast_node(right) > 0)
		return (1);
	return (-1);
}
