/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 04:13:33 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/25 17:21:54 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

int	append_fragment(char **result, char *s, int start, int i);
int	handle_dollar(char **result, char *s, int *index, int *status);
int	expand_env(char **result, char *s, int *index);
char	*strjoin_free(char *s1, char *s2);

int	handle_single_quote(char **result, char *cmd, int *index)
{
	int	i;

	i = *index + 1;
	while (cmd[i] && cmd[i] != '\'')
		i++;
	if (append_fragment(result, cmd, *index + 1, i) == ERROR)
		return (ERROR);
	*index = i + 1;
	return (OK);
}

int	handle_double_quote(char **result, char *cmd, int *index, int *status)
{
	int	i;
	int	start;

	i = *index + 1;
	start = i;
	while (cmd[i] && cmd[i] != '"')
	{
		if (cmd[i] == '$')
		{
			if (append_fragment(result, cmd, start, i) != OK)
				return (ERROR);
			if (handle_dollar(result, cmd, &i, status) != OK)
				return (ERROR);
			start = i;
		}
		else
			i++;
	}
	if (append_fragment(result, cmd, start, i) != OK)
		return (ERROR);
	i++;
	*index = i;
	return (OK);
}

int	handle_dollar(char **result, char *cmd, int *index, int *status)
{
	int		i;
	char	*aux;

	i = *index + 1;
	if (ft_isalpha(cmd[i]) || cmd[i] == '_')
	{
		if (expand_env(result, cmd, &i) != OK)
			return (ERROR);
	}
	else if (cmd[i] == '?')
	{
		aux = ft_itoa(*status);
		if (!aux)
			return (ERROR);
		*result = strjoin_free(*result, aux);
		free(aux);
		i++;
	}
	else
		*result = strjoin_free(*result, "$");
	if (!*result)
		return (ERROR);
	*index = i;
	return (OK);
}

int	handle_literal(char **result, char *cmd, int *index)
{
	int	i;

	i = *index;
	while (cmd[i] && !is_quote(cmd[i]) && cmd[i] != '$')
		i++;
	if (append_fragment(result, cmd, *index, i) != OK)
		return (ERROR);
	*index = i;
	return (OK);
}
