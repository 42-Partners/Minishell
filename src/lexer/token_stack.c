/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:22:23 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/17 22:47:37 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "error_handling.h"

#include <stdlib.h>

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
	node->type = type;
	node->value = ft_strdup(value);
	if (!node->value)
		return (free(node), NULL);
	node->next = NULL;
	return (node);
}

int	token_add_back(t_token **token, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*temp;

	new = new_token(value, type);
	if (!new)
		return (ERROR);
	if (!*token)
		*token = new;
	else
	{
		temp = *token;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (OK);
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

t_token	*divide_left(t_token *token_head, t_token *father)
{
	t_token	*token;
	t_token	*aux;
	int		ret;

	if (!token_head || !father || token_head == father)
		return (NULL);
	token = new_token(token_head->value, token_head->type);
	if (!token)
		return (NULL);
	aux = token_head->next;
	while (aux)
	{
		if (aux == father)
			break ;
		ret = token_add_back(&token, aux->value, aux->type);
		if (ret != OK)
			return (free_token(&token), NULL);
		aux = aux->next;
	}
	return (token);
}

t_token	*divide_right(t_token *token_head, t_token *father)
{
	t_token	*token;
	t_token	*aux;
	int		ret;

	if (!token_head || !father)
		return (NULL);
	while (token_head && token_head != father)
		token_head = token_head->next;
	if (!token_head || !token_head->next)
		return (NULL);
	else
		token_head = token_head->next;
	token = new_token(token_head->value, token_head->type);
	if (!token)
		return (NULL);
	aux = token_head->next;
	while (aux)
	{
		ret = token_add_back(&token, aux->value, aux->type);
		if (ret != OK)
			return (free_token(&token), NULL);
		aux = aux->next;
	}
	return (token);
}
