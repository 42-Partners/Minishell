/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:22:23 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/13 18:33:05 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

int	token_add_back(t_token **token, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*temp;

	new = new_token(value, type);
	if (!token || !new)
		return (0);
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
