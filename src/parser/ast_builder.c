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

#include <stdlib.h>
#include <stdio.h>

t_ast_node			*build_ast(t_token *tokens);
static t_token		*divide_left(t_token *token_head, t_token *father);
static t_token		*divide_right(t_token *token_head, t_token *father);
t_node_type			detect_next_node_type(t_token *tokens);

t_ast_node	*build_ast(t_token *tokens)
{
	t_ast_node	*ast;
	t_token		*aux;

	aux = tokens;
	while (aux)
	{
		if (aux->type == TOKEN_PIPE)
			break ;
		aux = aux->next;
	}
	if (detect_next_node_type(tokens) == CMD)
		ast = handle_low_level(tokens);
	else
		ast = handle_high_level(PIPE,
				divide_left(tokens, aux), divide_right(tokens, aux));
	debug_flag("build_ast OK");
	return (ast);
}

static t_token	*divide_left(t_token *token_head, t_token *father)
{
	t_token	*ret;
	t_token	*aux;

	if (!token_head || !father || token_head == father)
		return (NULL);
	ret = new_token(token_head->value,
			token_head->quote_type, token_head->type);
	if (!ret)
		return (NULL);
	aux = token_head->next;
	while (aux)
	{
		if (aux == father)
			break ;
		token_add_back(&ret, aux->value, aux->quote_type, aux->type);
		aux = aux->next;
	}
	return (ret);
}

static t_token	*divide_right(t_token *token_head, t_token *father)
{
	t_token	*ret;
	t_token	*aux;

	if (!token_head || !father)
		return (NULL);
	while (token_head && token_head != father)
		token_head = token_head->next;
	if (!token_head || !token_head->next)
		return (NULL);
	else
		token_head = token_head->next;
	ret = new_token(token_head->value,
			token_head->quote_type, token_head->type);
	if (!ret)
		return (NULL);
	aux = token_head->next;
	while (aux)
	{
		token_add_back(&ret, aux->value, aux->quote_type, aux->type);
		aux = aux->next;
	}
	return (ret);
}

t_node_type	detect_next_node_type(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			break ;
		tokens = tokens->next;
	}
	if (tokens && tokens->type == TOKEN_PIPE)
		return (PIPE);
	return (CMD);
}
