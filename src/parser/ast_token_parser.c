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
#include "libft.h"
#include "error_handling.h"

#include <stdlib.h>

static int			count_args(t_token *tokens);
static int			get_args(t_cmd_node **node, t_token *tokens);
static	t_cmd_node	*new_cmd_node(void);
static int			fill_args(t_cmd_node **node, t_token *tokens);
void				free_array(void **array, int count);

t_cmd_node	*consume_tokens(t_token *tokens)
{
	t_cmd_node	*ret;

	ret = new_cmd_node();
	if (!ret)
		return (NULL);
	if (get_args(&ret, tokens) != OK)
		return (free(ret), NULL);
	if (get_redirects(&ret, tokens) != OK)
		return (free(ret), NULL);
	if (ret->args)
		ret->cmd = ret->args[0];
	return (ret);
}

static int	count_args(t_token *tokens)
{
	int				arg_size;
	t_token_type	last;

	last = TOKEN_WORD;
	arg_size = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD && last == TOKEN_WORD)
		{
			arg_size++;
			tokens = tokens->next;
		}
		else
		{
			last = tokens->type;
			tokens = tokens->next;
		}
	}
	return (arg_size);
}

static int	get_args(t_cmd_node **node, t_token *tokens)
{
	int	n_args;

	n_args = count_args(tokens);
	if (!node || !*node)
		return (ERROR);
	if (!tokens || n_args == 0)
		(*node)->args = NULL;
	else if (n_args == 1)
		(*node)->args = malloc(sizeof(char *) * 2);
	else
	{
		(*node)->args = malloc(sizeof(char *) * (n_args + 1));
		if (!(*node)->args)
		{
			ft_putstr_fd(ERR_MALLOC, 2);
			free(*node);
			*node = NULL;
			return (ERROR);
		}
	}
	fill_args(node, tokens);
	return (OK);
}

static int	fill_args(t_cmd_node **node, t_token *tokens)
{
	int				i;
	t_token_type	last;

	i = 0;
	last = TOKEN_WORD;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD && last == TOKEN_WORD)
		{
			(*node)->args[i++] = ft_strdup(tokens->value);
			if (!(*node)->args[i])
			{
				ft_putstr_fd(ERR_MALLOC, 2);
				return (free_array((void **)(*node)->args, i), ERROR);
			}
			tokens = tokens->next;
		}
		else
		{
			last = tokens->type;
			tokens = tokens->next;
		}
	}
	(*node)->args[i] = NULL;
	return (OK);
}

static t_cmd_node	*new_cmd_node(void)
{
	t_cmd_node	*ret;

	ret = malloc(sizeof(t_cmd_node));
	if (!ret)
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
	ret->cmd = NULL;
	ret->args = NULL;
	ret->redirect_count = 0;
	ret->redirects = NULL;
	return (ret);
}
