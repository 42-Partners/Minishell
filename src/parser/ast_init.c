/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 07:52:13 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/18 14:13:40 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "ast.h"

t_ast_node			*init_ast_node(t_token *tokens);
static t_token		*divide_left(t_token *token_head, t_token *father);
static t_token		*divide_right(t_token *token_head, t_token *father);
// static t_ast_node	*handle_high_level(t_token *right_tokens, t_token *left_tokens);
// static t_ast_node	*handle_low_level(t_token *tokens);

t_ast_node	*init_ast_node(t_token *tokens)
{
	t_ast_node	*ast;
	t_token		*aux;

	ast = malloc(sizeof(t_ast_node));
	if (!ast)
		return (NULL);
	aux = tokens;
	while (aux)
	{
		if (aux->type == TOKEN_PIPE)
			break;
		aux = aux->next;
	}
	if (aux)
		(void)aux;
		//handle pipe
	else
		(void)aux;
		//handle cmd
	print_tokens(divide_left(tokens, aux), "DIVIDED LEFT TOKENS= ");
	print_tokens(divide_right(tokens, aux), "DIVIDED RIGHT TOKENS= ");
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

static t_token		*divide_right(t_token *token_head, t_token *father)
{
	t_token	*ret;
	t_token	*aux;

	if (!token_head || !father)
		return (NULL);
	while (token_head && token_head != father)
		token_head = token_head->next;
	if (!token_head)
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

/*
static t_ast_node	*handle_high_level(t_token *right_tokens, t_token *left_tokens)
{
	free_token(right_tokens);
	free_token(left_tokens);
	return (NULL);
}

static t_ast_node	*handle_low_level(t_token *tokens)
{
	t_ast_node *ret;

	if (!tokens)
	{
		debug_flag("handle_low_level received NULL!");
		return (NULL);
	}
	ret = malloc(sizeof(t_ast_node));
	if (!ret)
		return (NULL);
	ret->type = CMD;
	ret->t_node = consume_tokens(tokens);
	if (!ret->t_node)
	{
		debug_flag("consume_tokens coudn't handle tokens and retorned NULL!");
		free(ret);
		return (NULL);
	}
	free_token(right_tokens);
	free_token(left_tokens);
	return (ret);
}
	*/
