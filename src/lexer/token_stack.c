/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:22:23 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/19 15:33:58 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

#include <stdlib.h>

t_token	*new_token(char *value, char quote_type, t_token_type type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(value);
	if (!node->value)
		return (free(node), NULL);
	node->quote_type = quote_type;
	node->next = NULL;
	return (node);
}

int	token_add_back(t_token **token, char *value,
			char quote_type, t_token_type type)
{
	t_token	*new;
	t_token	*temp;

	if (!token)
		return (0);
	new = new_token(value, quote_type, type);
	if (!new)
		return (ft_putstr_fd("malloc error\n", 2), 0);
	if (!*token)
		*token = new;
	else
	{
		temp = *token;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (1);
}

void	free_token(t_token **token)
{
	t_token	*temp;

	if (!token)
		return ;
	while (*token)
	{
		temp = (*token)->next;
		free((*token)->value);
		free(*token);
		*token = temp;
	}
}
