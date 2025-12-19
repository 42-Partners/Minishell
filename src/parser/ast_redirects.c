/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:58:27 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/17 15:58:27 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ast.h"

#include <stdlib.h>

void			get_redirects(t_cmd_node **node, t_token *tokens);
static void		parse_redirect_tokens(t_redirect ***redirect, t_token *tokens);
static void		handle_redirect_token(t_redirect **redirect, t_token *token);

void	get_redirects(t_cmd_node **node, t_token *tokens)
{
	t_token	*aux;
	int		i;

	i = 0;
	aux = tokens;
	while (aux
		&& (aux->type == TOKEN_HEREDOC || aux->type == TOKEN_REDIRECT_IN
			|| aux->type == TOKEN_REDIRECT_OUT
			|| aux->type == TOKEN_REDIRECT_APPEND))
	{
		i++;
		aux = aux->next;
	}
	if (i == 0)
	{
		(*node)->redirects = NULL;
		(*node)->redirect_count = 0;
	}
	else
	{
		(*node)->redirects = malloc(sizeof(t_redirect *) * (i + 1));
		parse_redirect_tokens(&(*node)->redirects, tokens);
		if (!(*node)->redirects)
			free(*node);
	}
}

static void	parse_redirect_tokens(t_redirect ***redirect, t_token *tokens)
{
	int	i;

	if (!(*redirect))
		return ;
	i = 0;
	while (tokens
		&& (tokens->type == TOKEN_HEREDOC || tokens->type == TOKEN_REDIRECT_IN
			|| tokens->type == TOKEN_REDIRECT_OUT
			|| tokens->type == TOKEN_REDIRECT_APPEND))
	{
		(*redirect)[i] = malloc(sizeof(t_redirect));
		if (!(*redirect)[i])
		{
			while (i >= 0)
				free((*redirect)[--i]);
			free(*redirect);
			return ;
		}
		handle_redirect_token(&((*redirect)[i]), tokens);
		if (tokens->next == TOKEN_WORD)
			tokens = tokens->next->next;
		else
			tokens = tokens->next;
	}
	(*redirect)[i] = NULL;
}

static void	handle_redirect_token(t_redirect **redirect, t_token *token)
{
	if (!redirect || !*redirect || !token)
	{
		debug_flag("bad use of handle_redirect_token!");
		return ;
	}
	(*redirect)->file_name = NULL;
	(*redirect)->fd = -1;
	if (token->type == TOKEN_HEREDOC)
	{
		(*redirect)->type = HERE_DOC;
		(*redirect)->fd = 0;
		if (token->next && token->next == TOKEN_WORD)
			(*redirect)->file_name = token->next->value;
		return ;
	}
	if (token->type == TOKEN_REDIRECT_IN)
		(*redirect)->type = REDIRECT_IN;
	else if (token->type == TOKEN_REDIRECT_OUT)
		(*redirect)->type = REDIRECT_OUT;
	else if (token->type == TOKEN_REDIRECT_APPEND)
		(*redirect)->type = REDIRECT_APPEND;
	if (!token->next || token->next->type != TOKEN_WORD)
		return ;
	(*redirect)->file_name = token->next->value;
}
