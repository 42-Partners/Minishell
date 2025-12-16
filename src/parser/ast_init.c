/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 07:52:13 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/16 10:05:03 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "ast.h"

t_ast_node	*init_ast_node(t_token **tokens);

t_ast_node	*init_ast_node(t_token **tokens)
{
	t_ast_node	*ast;
	t_token		*aux;

	ast = malloc(sizeof(t_ast_node *));
	if (!ast)
		return (NULL);
	if ((*tokens)->type == TOKEN_WORD)
	{
		aux = tokens + 1;
		if ((aux && aux->type == TOKEN_PIPE || aux->type == TOKEN_WORD) || !aux)
			ast->type = CMD;
		else
			(void)ast; // handle redirect
	}
	else if ((*tokens)->type == TOKEN_HEREDOC)
		(void)ast; // handle here_doc
	else if ((*tokens)->type == TOKEN_PIPE)
		(void)ast; // handle pipe
	return (ast);
}
