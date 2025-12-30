/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 04:13:33 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/28 19:32:06 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include "lexer.h"

void	append_fragment(char **result, char *s, int start, int i);
void	handle_dollar(char **result,
			char *s, int *index, t_shell_env shell);
void	expand_env(char **result, char *s, int *index, char *envv[]);
char	*strjoin_free(char *s1, char *s2);

void	handle_single_quote(char **result, char *s, int *index)
{
	int	i;

	i = *index + 1;
	while (s[i] && s[i] != '\'')
		i++;
	append_fragment(result, s, *index + 1, i);
	*index = i + 1;
}

void	handle_double_quote(char **result,
			char *s, int *index, t_shell_env shell)
{
	int	start;
	int	i;

	i = *index + 1;
	start = i;
	while (s[i] && s[i] != '"')
	{
		if (s[i] == '$')
		{
			append_fragment(result, s, start, i);
			handle_dollar(result, s, &i, shell);
			start = i;
		}
		else
			i++;
	}
	append_fragment(result, s, start, i);
	i++;
	*index = i;
}

void	handle_dollar(char **result,
	char *s, int *index, t_shell_env shell)
{
	int		i;
	char	*aux;

	i = *index + 1;
	if (ft_isalpha(s[i]) || s[i] == '_')
		expand_env(result, s, &i, *shell.envv);
	else if (s[i] == '?')
	{
		aux = ft_itoa(*shell.status);
		*result = strjoin_free(*result, aux);
		free(aux);
		i++;
	}
	else
		*result = strjoin_free(*result, "$");
	*index = i;
}

void	handle_literal(char **result, char *s, int *index)
{
	int	i;

	i = *index;
	while (s[i] && !is_quote(s[i]) && s[i] != '$')
		i++;
	append_fragment(result, s, *index, i);
	*index = i;
}
