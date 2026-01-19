/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parentesis_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:33:51 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/17 19:33:51 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ast.h"
#include "libft.h"
#include "error_handling.h"

#include <stdlib.h>

static int	isolate(t_token **tokens, t_token **leftovers);
static int	handle_tokens(t_ast_node **ast, t_token *left, t_token *right);
static int	unite_nodes(t_ast_node **ast,
				t_ast_node *right, t_ast_node *left, t_token_type type);
static int	set_node(void **node, t_token_type type);

int	parentesis_handler(t_ast_node **ast, t_token *tokens)
{
	t_token	*leftovers;
	int		ret;

	*ast = NULL;
	leftovers = NULL;
	if (tokens->type != TOKEN_OPEN_PARENTESIS)
		return (
			ft_fprintf(2, "syntax error near '%s'\n", tokens->value), FAIL);
	tokens = tokens->next;
	if (!tokens)
		return (ft_fprintf(2, "syntax error near token '('\n"), FAIL);
	if (tokens->type == TOKEN_CLOSE_PARENTESIS)
		return (ft_fprintf(2, "syntax error near unexpected token ')'\n"), FAIL);
	ret = isolate(&tokens, &leftovers);
	if (ret != OK)
		return (ret);
	ret = handle_tokens(ast, tokens, leftovers);
	free_token(&tokens);
	free_token(&leftovers);
	return (ret);
}

static int	isolate(t_token **tokens, t_token **leftovers)
{
	t_token	*aux;
	int		parentesis_lv;

	parentesis_lv = 1;
	aux = *tokens;
	while (aux)
	{
		if (aux->type == TOKEN_OPEN_PARENTESIS)
			parentesis_lv++;
		else if (aux->type == TOKEN_CLOSE_PARENTESIS)
			parentesis_lv--;
		if (parentesis_lv == 0)
			break ;
		aux = aux->next;
	}
	if (parentesis_lv != 0)
		return (ft_fprintf(2, "unclosed '('\n"), FAIL);
	*leftovers = divide_right(*tokens, aux);
	if (!*leftovers && aux->next)
		return (ERROR);
	*tokens = divide_left(*tokens, aux);
	if (!*tokens)
		return (free_token(leftovers), ERROR);
	return (OK);
}

static int	handle_tokens(t_ast_node **ast, t_token *left, t_token *right)
{
	int			ret;
	t_ast_node	*right_node;
	t_ast_node	*left_node;

	ret = OK;
	if (right
		&& ((right->type != TOKEN_AND && right->type != TOKEN_OR
				&& right->type != TOKEN_PIPE) || !right->next))
		return (ft_fprintf(2, "syntax error near token ')'\n"), FAIL);
	else if (!right)
		return (build_ast(ast, left));
	ret = build_ast(&right_node, right->next);
	if (ret != OK)
		return (free_ast(&right_node), ret);
	ret = build_ast(&left_node, left);
	if (ret != OK)
	{
		free_ast(&right_node);
		return (free_ast(&left_node), ret);
	}
	return (unite_nodes(ast, right_node, left_node, right->type));
}

static int	unite_nodes(t_ast_node **ast,
		t_ast_node *right, t_ast_node *left, t_token_type union_type)
{
	void	*node;

	node = NULL;
	*ast = malloc(sizeof(t_ast_node));
	if (!*ast)
		return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
	if (set_node(&node, union_type) != OK)
		return (ERROR);
	if (union_type == TOKEN_AND || union_type == TOKEN_OR)
	{
		((t_logical_node *)node)->right = right;
		((t_logical_node *)node)->left = left;
		(*ast)->t_node.logical_node = *(t_logical_node *)node;
		(*ast)->type = LOGICAL_AND;
		if (union_type == TOKEN_OR)
			(*ast)->type = LOGICAL_OR;
	}
	else if (union_type == TOKEN_PIPE)
	{
		((t_pipe_node *)node)->right = right;
		((t_pipe_node *)node)->left = left;
		(*ast)->t_node.pipe_node = *(t_pipe_node *)node;
		(*ast)->type = PIPE;
	}
	return (free(node), OK);
}

static int	set_node(void **node, t_token_type type)
{
	if (type == TOKEN_PIPE)
		*node = malloc(sizeof(t_pipe_node));
	else if (type == TOKEN_OR || type == TOKEN_AND)
		*node = malloc(sizeof(t_logical_node));
	if (!*node)
		return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
	else if (type == TOKEN_AND)
		((t_logical_node *)*node)->type = AND;
	else if (type == TOKEN_OR)
		((t_logical_node *)*node)->type = OR;
	return (OK);
}
