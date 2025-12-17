/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:23:05 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/16 21:28:53 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "ast.h"
#include <stdio.h>

void	print_tokens(t_token *tokens, char *custom);
static char	*get_token_type(t_token token);

void	print_tokens(t_token *tokens, char *custom)
{
	int	silent;

	silent = 0;
	if (custom)
	{
		if (*custom == '@')
			silent = ((*(custom++) * 0) + 1);
		if (custom)
			printf("%s", custom);
	}
	if (!tokens)
		printf("NULL TOKENS");
	while (tokens)
	{
		printf("<TOKEN type=%s", get_token_type(*tokens));
		if (tokens->type == TOKEN_WORD && !silent)
			printf(" content =\"%s\"", tokens->value);
		if (tokens->quote_type != 0 && !silent)
			printf(" quote=%c", tokens->quote_type);
		printf("/>");
		tokens = tokens->next;
	}
	printf("\n");
}

static char	*get_token_type(t_token token)
{
	if (token.type == TOKEN_WORD)
		return ("WORD");
	else if (token.type == TOKEN_HEREDOC)
		return ("HERE_DOC");
	else if (token.type == TOKEN_PIPE)
		return ("PIPE");
	else if (token.type == TOKEN_REDIRECT_IN)
		return ("RED_IN");
	else if (token.type == TOKEN_REDIRECT_OUT)
		return ("RED_OUT");
	else if (token.type == TOKEN_REDIRECT_APPEND)
		return ("RED_APPEND");
	else
		return ("ERROR");
}
