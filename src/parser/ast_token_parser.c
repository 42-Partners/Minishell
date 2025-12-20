/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_token_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 07:17:25 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/20 04:48:19 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ast.h"

#include <stdlib.h>

t_cmd_node			*consume_tokens(t_token *tokens);
static int			count_args(t_token *tokens);
static void			get_args(t_cmd_node **node, t_token *tokens);

t_cmd_node	*consume_tokens(t_token *tokens)
{
	t_cmd_node	*ret;

	ret = malloc(sizeof(t_cmd_node));
	if (!ret)
		return (NULL);
	if (tokens->type == TOKEN_WORD)
	{
		ret->cmd = tokens->value;
		tokens = tokens->next;
		get_args(&(ret), tokens);
		if (!ret)
			return (NULL);
		while (tokens && tokens->type == TOKEN_WORD)
			tokens = tokens->next;
		get_redirects(&(ret), tokens);
	}
	else
		ret->cmd = NULL;
	return (ret);
}

static int	count_args(t_token *tokens)
{
	int	arg_size;

	arg_size = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			break ;
		if (tokens->type != TOKEN_WORD)
			tokens = tokens->next;
		else
			arg_size++;
		if (tokens)
			tokens = tokens->next;
	}
	return (arg_size);
}

static void	get_args(t_cmd_node **node, t_token *tokens)
{
	int	i;

	i = 0;
	if (!node || !*node)
		return ;
	if (!tokens && count_args(tokens) == 0)
	{
		(*node)->args = NULL;
		return ;
	}
	(*node)->args = malloc(sizeof(char *) * (count_args(tokens) + 1));
	if (!(*node)->args)
	{
		free(*node);
		*node = NULL;
		return ;
	}
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			break ;
		if (tokens->type != TOKEN_WORD)
			tokens = tokens->next;
		else
			(*node)->args[i++] = tokens->value;
		if (tokens)
			tokens = tokens->next;
	}
	(*node)->args[i] = NULL;
}
