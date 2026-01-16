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

static t_token		*divide_left(t_token *token_head, t_token *father);
static t_token		*divide_right(t_token *token_head, t_token *father);

int	build_ast(t_ast_node **ast, t_token *tokens)
{
	t_token		*aux;
	int			ret;

	aux = tokens;
	while (aux)
	{
		if (aux->type == TOKEN_PIPE)
			break ;
		aux = aux->next;
	}
	if (detect_next_node_type(tokens) == CMD)
	{
		ret = handle_low_level(ast, tokens);
		if (ret != OK)
			return (*ast = NULL, ret);
	}
	else
	{
		ret = handle_high_level(ast, PIPE,
				divide_right(tokens, aux), divide_left(tokens, aux));
		if (ret != OK)
			return (*ast = NULL, ret);
	}
	return (OK);
}

t_node_type	detect_next_node_type(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			return (PIPE);
		tokens = tokens->next;
	}
	return (CMD);
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
