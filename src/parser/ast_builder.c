/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 07:52:13 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/20 02:03:11 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ast.h"
#include "error_handling.h"

#include <stdlib.h>
#include <stdio.h>

static t_token		*getfather_token(t_token *tokens, t_node_type father_type);
static t_token		*divide_left(t_token *token_head, t_token *father);
static t_token		*divide_right(t_token *token_head, t_token *father);
static t_node_type	detect_next_node_type(t_token *tokens);

int	build_ast(t_ast_node **ast, t_token *tokens)
{
	t_token		*tk_node;
	int			ret;
	t_node_type	next_node_type;

	next_node_type = detect_next_node_type(tokens);
	if (next_node_type == CMD)
		ret = handle_low_level(ast, tokens);
	else
	{
		tk_node = getfather_token(tokens, next_node_type);
		ret = handle_high_level(ast, next_node_type,
				divide_right(tokens, tk_node), divide_left(tokens, tk_node));
	}
	if (ret != OK)
		return (*ast = NULL, ret);
	return (OK);
}

static t_token	*getfather_token(t_token *tokens, t_node_type father_type)
{
	t_token_type	father_token_type;

	father_token_type = TOKEN_PIPE;
	if (father_type == LOGICAL_AND)
		father_token_type = TOKEN_AND;
	if (father_type == LOGICAL_OR)
		father_token_type = TOKEN_OR;
	while (tokens)
	{
		if (tokens->type == father_token_type)
			break ;
		tokens = tokens->next;
	}
	return (tokens);
}

static t_node_type	detect_next_node_type(t_token *tokens)
{
	t_node_type	highest_level;

	highest_level = CMD;
	while (tokens)
	{
		if (tokens->type == TOKEN_AND)
			return (LOGICAL_AND);
		else if (tokens->type == TOKEN_OR)
			return (LOGICAL_OR);
		else if (tokens->type == TOKEN_PIPE && highest_level == CMD)
			highest_level = PIPE;
		tokens = tokens->next;
	}
	return (highest_level);
}

static t_token	*divide_left(t_token *token_head, t_token *father)
{
	t_token	*token;
	t_token	*aux;
	int		ret;

	if (!token_head || !father || token_head == father)
		return (NULL);
	token = new_token(token_head->value, token_head->type);
	if (!token)
		return (NULL);
	aux = token_head->next;
	while (aux)
	{
		if (aux == father)
			break ;
		ret = token_add_back(&token, aux->value, aux->type);
		if (ret != OK)
			return (free_token(&token), NULL);
		aux = aux->next;
	}
	return (token);
}

static t_token	*divide_right(t_token *token_head, t_token *father)
{
	t_token	*token;
	t_token	*aux;
	int		ret;

	if (!token_head || !father)
		return (NULL);
	while (token_head && token_head != father)
		token_head = token_head->next;
	if (!token_head || !token_head->next)
		return (NULL);
	else
		token_head = token_head->next;
	token = new_token(token_head->value, token_head->type);
	if (!token)
		return (NULL);
	aux = token_head->next;
	while (aux)
	{
		ret = token_add_back(&token, aux->value, aux->type);
		if (ret != OK)
			return (free_token(&token), NULL);
		aux = aux->next;
	}
	return (token);
}
