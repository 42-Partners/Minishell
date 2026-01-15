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

#include "libft.h"
#include "lexer.h"
#include "ast.h"
#include "error_handling.h"

#include <stdlib.h>

static int	new_high_level_node(void **node, t_node_type type,
				t_token *right_tokens, t_token *left_tokens);
static int	fill_high_level_node(void **node, t_node_type type,
				t_token *right_tokens, t_token *left_tokens);
static void	cleanup(t_token *left, t_token *right, void *node);

int	handle_low_level(t_ast_node **ast, t_token *tokens)
{
	t_cmd_node	*cmd_node;
	int			ret;

	cmd_node = NULL;
	*ast = malloc(sizeof(t_ast_node));
	if (!*ast)
		return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
	(*ast)->type = CMD;
	ret = consume_tokens(&cmd_node, tokens);
	if (ret != OK)
		return (free(*ast), ret);
	(*ast)->t_node.cmd_node = *cmd_node;
	free(cmd_node);
	return (OK);
}

int	handle_high_level(t_ast_node **ast, t_node_type type,
	t_token *right_tokens, t_token *left_tokens)
{
	void	*sub_node;
	int		ret;

	if (!right_tokens || !left_tokens)
		return (ERROR);
	if (type != LOGICAL && type != PIPE)
		return (ERROR);
	*ast = malloc(sizeof(t_ast_node));
	if (!*ast)
		return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
	(*ast)->type = type;
	sub_node = NULL;
	ret = new_high_level_node(&sub_node, type, right_tokens, left_tokens);
	if (ret != OK)
		return (ret);
	if (type == LOGICAL)
		(*ast)->t_node.logical_node = *((t_logical_node *)sub_node);
	else if (type == PIPE)
		(*ast)->t_node.pipe_node = *((t_pipe_node *)sub_node);
	free(sub_node);
	return (OK);
}

static int	new_high_level_node(void **node, t_node_type type,
			t_token *right_tokens, t_token *left_tokens)
{
	int	ret;

	if (type == LOGICAL)
		*node = malloc(sizeof(t_logical_node));
	else if (type == PIPE)
		*node = malloc(sizeof(t_pipe_node));
	if (!*node)
		return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
	ret = fill_high_level_node(node, type, right_tokens, left_tokens);
	if (ret != OK)
		return (cleanup(left_tokens, right_tokens, *node), ret);
	cleanup(left_tokens, right_tokens, NULL);
	return (OK);
}

static int	fill_high_level_node(void **node, t_node_type type,
		t_token *right_tokens, t_token *left_tokens)
{
	int	ret;

	if (type == LOGICAL)
	{
		ret = build_ast(&((t_logical_node *)(*node))->left, left_tokens);
		if (ret != OK)
			return (ret);
		ret = build_ast(&((t_logical_node *)(*node))->right, right_tokens);
		if (ret != OK)
			return (ret);
	}
	else if (type == PIPE)
	{
		ret = build_ast(&((t_pipe_node *)(*node))->left, left_tokens);
		if (ret != OK)
			return (ret);
		ret = build_ast(&((t_pipe_node *)(*node))->right, right_tokens);
		if (ret != OK)
			return (ret);
	}
	return (OK);
}

static void	cleanup(t_token *left, t_token *right, void *node)
{
	free_token(&left);
	free_token(&right);
	if (node)
		free(node);
}
