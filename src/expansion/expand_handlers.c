/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 04:13:33 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/19 02:11:36 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "libft.h"
#include "lexer.h"
#include "error_handling.h"

int			append_fragment(char **result, char *s, int start, int i);
int			expand_env(char **result, char *cmd, int *index, char *envp[]);
static int	handle_invalid_var_name(char **result, char *cmd, int *index);

int	handle_dollar(char **result, char *cmd, int *index, t_shell *shell)
{
	int		i;
	char	*aux;

	i = *index + 1;
	if (ft_isalpha(cmd[i]) || cmd[i] == '_')
	{
		if (expand_env(result, cmd, &i, shell->envp) != OK)
			return (ERROR);
	}
	else if (cmd[i] == '?')
	{
		aux = ft_itoa(shell->status);
		if (!aux)
			return (ERROR);
		*result = ft_strjoin_free(*result, aux);
		free(aux);
		i++;
	}
	else
	{
		if (handle_invalid_var_name(result, cmd, &i) != OK)
			return (ERROR);
	}
	*index = i;
	return (OK);
}

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

int	handle_double_quote(char **result, char *cmd, int *index, t_shell *shell)
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
			if (handle_dollar(result, cmd, &i, shell) != OK)
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

int	handle_literal(char **result, char *cmd, int *index)
{
	int	i;

	i = *index;
	while (cmd[i] && !ft_isquote(cmd[i]) && cmd[i] != '$')
		i++;
	if (append_fragment(result, cmd, *index, i) != OK)
		return (ERROR);
	*index = i;
	return (OK);
}

static int	handle_invalid_var_name(char **result, char *cmd, int *index)
{
	if (cmd[*index] == '\0')
	{
		*result = ft_strjoin_free(*result, "$");
		if (!*result)
			return (ERROR);
	}
	else
		(*index)++;
	return (OK);
}
