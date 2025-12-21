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
#include "minishell.h"

#include <stdlib.h>

t_cmd_node			*consume_tokens(t_token *tokens);
static int			count_args(t_token *tokens);
static void			get_args(t_cmd_node **node, t_token *tokens);
static	t_cmd_node	*new_cmd_node(void);
static void			fill_args(t_cmd_node **node, t_token *tokens);

t_cmd_node	*consume_tokens(t_token *tokens)
{
	t_cmd_node	*ret;

	ret = new_cmd_node();
	if (!ret)
		return (NULL);
	get_args(&ret, tokens);
	get_redirects(&ret, tokens);
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
		{
			ret->cmd = ft_strdup(tokens->value);
			break ;
		}
		if (tokens->type != TOKEN_WORD)
		{
			tokens = tokens->next;
			if (tokens)
				tokens = tokens->next;
		}
		else
			tokens = tokens->next;
	}
	return (ret);
}

static int	count_args(t_token *tokens)
{
	int	arg_size;

	arg_size = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
		{
			arg_size++;
			tokens = tokens->next;
		}
		else
		{
			tokens = tokens->next;
			if (tokens)
				tokens = tokens->next;
		}
	}
	return (arg_size);
}

static void	get_args(t_cmd_node **node, t_token *tokens)
{
	if (!node || !*node)
		return ;
	if (!tokens || count_args(tokens) == 0)
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
	fill_args(node, tokens);
}

static void	fill_args(t_cmd_node **node, t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
		{
			(*node)->args[i++] = ft_strdup(tokens->value);
			tokens = tokens->next;
		}
		else
		{
			tokens = tokens->next;
			if (tokens)
				tokens = tokens->next;
		}
	}
	(*node)->args[i] = NULL;
}

static t_cmd_node	*new_cmd_node(void)
{
	t_cmd_node	*ret;

	ret = malloc(sizeof(t_cmd_node));
	if (!ret)
		return (NULL);
	ret->cmd = NULL;
	ret->args = NULL;
	ret->redirect_count = 0;
	ret->redirects = NULL;
	return (ret);
}
