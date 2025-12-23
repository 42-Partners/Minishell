/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 04:13:33 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/23 04:47:49 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

void	append_fragment(char **result, char *s, int start, int i);
void	handle_dollar(char **result, char *s, int *index);
void	expand_env(char **result, char *s, int *index);
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

void	handle_double_quote(char **result, char *s, int *index)
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
			handle_dollar(result, s, &i);
			start = i;
		}
		else
			i++;
	}
	append_fragment(result, s, start, i);
	i++;
	*index = i;
}

void	handle_dollar(char **result, char *s, int *index)
{
	int	i;

	i = *index + 1;
	if (ft_isalpha(s[i]) || s[i] == '_')
		expand_env(result, s, &i);
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
