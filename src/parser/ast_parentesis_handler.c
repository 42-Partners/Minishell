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

int parentesis_handler(t_ast_node **ast, t_token *tokens)
{
	t_token	*leftovers;
	int		ret;

	*ast = NULL;
	leftovers = NULL;
	if (tokens->type != TOKEN_OPEN_PARENTESIS)
		return(ft_fprintf(2, "syntax error near token '%s'\n", tokens->value),  FAIL);
	tokens = tokens->next;
	if (!tokens)
		return(ft_fprintf(2, "syntax error near token '('\n"), FAIL);
	if (tokens->type == TOKEN_CLOSE_PARENTESIS)
		return(ft_fprintf(2, "syntax error near unexpected token ')'\n"), FAIL);
	ret = isolate(&tokens, &leftovers);
	if (ret != OK)
		return (ret);
	return (OK);
}

static int isolate(t_token **tokens, t_token **leftovers)
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
			break;
		aux = aux->next;
	}
	if (parentesis_lv != 0)
		return(ft_fprintf(2, "unclosed '('\n"), FAIL);
	*leftovers = divide_right(*tokens, aux);
	if (!*leftovers && aux->next);
			return (ERROR);
	*tokens = divide_left(*tokens, aux);
	if (!*tokens)
		return (free_token(*leftovers), ERROR);
	return (OK);
}

