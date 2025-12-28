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
#include "libft.h"
#include "error_handling.h"

#include <stdlib.h>

static void		parse_redirect_tokens(t_redirect ***redirect, t_token *tokens);
static void		handle_redirect_token(t_redirect **redirect, t_token *token);

void	get_redirects(t_cmd_node **node, t_token *tokens) //! verificar
{
	t_token	*aux;
	int		i;

	i = 0;
	aux = tokens;
	while (aux)
	{
		if (aux->type == TOKEN_HEREDOC || aux->type == TOKEN_REDIRECT_IN
			|| aux->type == TOKEN_REDIRECT_OUT
			|| aux->type == TOKEN_REDIRECT_APPEND)
			i++;
		aux = aux->next;
	}
	(*node)->redirect_count = i;
	if (i == 0)
		(*node)->redirects = NULL;
	else
	{
		(*node)->redirects = malloc(sizeof(t_redirect *) * (i + 1));
		if (!(*node)->redirects)
			return (ft_putstr_fd(ERR_MALLOC, 2), free(*node));
		parse_redirect_tokens(&(*node)->redirects, tokens);
	}
}

static void	parse_redirect_tokens(t_redirect ***redirect, t_token *tokens)
{
	int	i;

	if (!(*redirect)) 
		return ;
	i = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_HEREDOC || tokens->type == TOKEN_REDIRECT_IN
			|| tokens->type == TOKEN_REDIRECT_OUT
			|| tokens->type == TOKEN_REDIRECT_APPEND)
		{
			(*redirect)[i] = malloc(sizeof(t_redirect));
			if (!(*redirect)[i])
			{
				while (i > 0)
					free((*redirect)[--i]);
				free(*redirect);
				return ;
			}
			handle_redirect_token(&((*redirect)[i]), tokens);
			i++;
		}
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
		if (token->next && token->next->type == TOKEN_WORD)
			(*redirect)->file_name = ft_strdup(token->next->value);
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
	(*redirect)->file_name = ft_strdup(token->next->value);
}
