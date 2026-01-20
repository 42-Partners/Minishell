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

static int		parse_redirect_tokens(t_redirect ***redirect, t_token *tokens);
static int		handle_redirect_token(t_redirect **redirect, t_token *token);
static int		count_redirects(t_token *tokens);

int	get_redirects(t_cmd_node **node, t_token *tokens)
{
	int	ret;
	int	i;

	ret = OK;
	i = count_redirects(tokens);
	(*node)->redirect_count = i;
	if (i == 0)
		(*node)->redirects = NULL;
	else
	{
		(*node)->redirects = malloc(sizeof(t_redirect *) * (i + 1));
		if (!(*node)->redirects)
		{
			ft_fprintf(2, ERR_MALLOC);
			return (ERROR);
		}
		ret = parse_redirect_tokens(&(*node)->redirects, tokens);
		if (ret != OK)
			return (ret);
	}
	return (OK);
}

static int	parse_redirect_tokens(t_redirect ***redirect, t_token *tokens)
{
	int	ret;
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == 4 || tokens->type == 5
			|| tokens->type == 6 || tokens->type == 7)
		{
			(*redirect)[i] = malloc(sizeof(t_redirect));
			if (!(*redirect)[i])
			{
				ft_fprintf(2, ERR_MALLOC);
				return (free_redirect_array(redirect), ERROR);
			}
			ret = handle_redirect_token(&((*redirect)[i]), tokens);
			if (ret != OK)
				return (free_redirect_array(redirect), ret);
			i++;
		}
		tokens = tokens->next;
	}
	(*redirect)[i] = NULL;
	return (OK);
}

static int	handle_redirect_token(t_redirect **redirect, t_token *token)
{
	(*redirect)->file_name = NULL;
	(*redirect)->fd = -1;
	if (token->type == TOKEN_HEREDOC)
	{
		(*redirect)->type = HERE_DOC;
		(*redirect)->fd = 0;
	}
	else if (token->type == TOKEN_REDIRECT_IN)
		(*redirect)->type = REDIRECT_IN;
	else if (token->type == TOKEN_REDIRECT_OUT)
		(*redirect)->type = REDIRECT_OUT;
	else if (token->type == TOKEN_REDIRECT_APPEND)
		(*redirect)->type = REDIRECT_APPEND;
	if (!token->next || token->next->type != TOKEN_WORD)
	{
		ft_fprintf(2,
			"syntax error near token '%s'\n", token->value);
		return (FAIL);
	}
	(*redirect)->file_name = ft_strdup(token->next->value);
	if (!(*redirect)->file_name)
		return (ft_fprintf(2, ERR_MALLOC), ERROR);
	return (OK);
}

static int	count_redirects(t_token *tokens)
{
	int		count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_HEREDOC || tokens->type == TOKEN_REDIRECT_IN
			|| tokens->type == TOKEN_REDIRECT_OUT
			|| tokens->type == TOKEN_REDIRECT_APPEND)
			count++;
		tokens = tokens->next;
	}
	return (count);
}
