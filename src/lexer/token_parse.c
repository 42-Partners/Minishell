/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:31:57 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/19 03:20:28 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

#include <stdlib.h>

int	token_add_back(t_token **token, char *value, t_token_type type);
int	is_quote(int c);
int	is_word(int c);

int	get_operator(t_token **token, char **input)
{
	int	ret;

	if ((*input)[0] == '>' && (*input)[1] == '>')
	{
		ret = token_add_back(token, ">>", TOKEN_REDIRECT_APPEND);
		(*input)++;
	}
	else if ((*input)[0] == '<' && (*input)[1] == '<')
	{
		ret = token_add_back(token, "<<", TOKEN_HEREDOC);
		(*input)++;
	}
	else if ((*input)[0] == '|')
		ret = token_add_back(token, "|", TOKEN_PIPE);
	else if ((*input)[0] == '>')
		ret = token_add_back(token, ">", TOKEN_REDIRECT_OUT);
	else if ((*input)[0] == '<')
		ret = token_add_back(token, "<", TOKEN_REDIRECT_IN);
	(*input)++;
	return (ret);
}

int	get_word(t_token **token, char **input)
{
	char	*value;
	char	quote;
	size_t	i;
	int		ret;

	i = 0;
	while ((*input)[i] && is_word((*input)[i]))
	{
		if (is_quote((*input)[i]))
		{
			quote = (*input)[i++];
			while ((*input)[i] && (*input)[i] != quote)
				i++;
			if (!(*input)[i])
				return (ft_putstr_fd("syntax error: unclosed quote\n", 2), 0);
		}
		i++;
	}
	value = ft_substr(*input, 0, i);
	if (!value)
		return (ft_putstr_fd("malloc error\n", 2), 0);
	ret = token_add_back(token, value, TOKEN_WORD);
	free(value);
	*input += i;
	return (ret);
}
