/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_level_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:01:38 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/19 14:01:38 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ast.h"

#include <stdlib.h>

t_ast_node	*handle_low_level(t_token *tokens);
t_ast_node	*handle_high_level(t_node_type type,
				t_token *right_tokens, t_token *left_tokens);
static void	*new_high_level_node( t_node_type type,
				t_token *right_tokens, t_token *left_tokens);

t_ast_node	*handle_high_level(t_node_type type,
				t_token *right_tokens, t_token *left_tokens)
{
	t_ast_node	*ret;
	void		*ret_sub_node;

	if (type != LOGICAL && type != PIPE)
		return (NULL);
	ret = malloc(sizeof(t_ast_node));
	if (!ret)
		return (NULL);
	ret->type = type;
	ret_sub_node = new_high_level_node(type, right_tokens, left_tokens);
	if (type == LOGICAL)
		ret->t_node.logical_node = *((t_logical_node *)ret_sub_node);
	else if (type == PIPE)
		ret->t_node.pipe_node = *((t_pipe_node *)ret_sub_node);
	else
		return (free(ret), NULL);
	free(ret_sub_node);
	return (ret);
}

t_ast_node	*handle_low_level(t_token *tokens)
{
	t_ast_node	*ret;
	t_cmd_node	*cmd_node;

	if (!tokens)
		return (NULL);
	ret = malloc(sizeof(t_ast_node));
	if (!ret)
		return (NULL);
	ret->type = CMD;
	cmd_node = consume_tokens(tokens);
	if (!cmd_node)
	{
		debug_flag("consume_tokens coudn't handle tokens and retorned NULL!");
		free(ret);
		return (NULL);
	}
	ret->t_node.cmd_node = *cmd_node;
	free(cmd_node);
	return (ret);
}

static void	*new_high_level_node( t_node_type type,
	t_token *left_tokens, t_token *right_tokens)
{
	void	*ret;

	ret = NULL;
	if (type == LOGICAL)
		ret = malloc(sizeof(t_logical_node));
	else if (type == PIPE)
		ret = malloc(sizeof(t_pipe_node));
	if (!ret)
		return (NULL);
	if (type == LOGICAL)
	{
		((t_logical_node *)ret)->left = build_ast(left_tokens);
		((t_logical_node *)ret)->right = build_ast(right_tokens);
	}
	else if (type == PIPE)
	{
		((t_pipe_node *)ret)->left = build_ast(left_tokens);
		((t_pipe_node *)ret)->right = build_ast(right_tokens);
	}
	return (ret);
}
