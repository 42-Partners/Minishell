/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:31:57 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/17 19:25:55 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "error_handling.h"

#include <stdlib.h>

int	token_add_back(t_token **token, char *value, t_token_type type);
int	get_highlevel_operator(t_token **token, char **input);
int	is_word(int c);

int	get_operator(t_token **token, char **input)
{
	int	ret;

	ret = 0;
	if ((*input)[0] == '&' || (*input)[0] == '|')
		ret = get_highlevel_operator(token, input);
	else if ((*input)[0] == '>' && (*input)[1] == '>')
	{
		ret = token_add_back(token, ">>", TOKEN_REDIRECT_APPEND);
		(*input)++;
	}
	else if ((*input)[0] == '<' && (*input)[1] == '<')
	{
		ret = token_add_back(token, "<<", TOKEN_HEREDOC);
		(*input)++;
	}
	else if ((*input)[0] == '>')
		ret = token_add_back(token, ">", TOKEN_REDIRECT_OUT);
	else if ((*input)[0] == '<')
		ret = token_add_back(token, "<", TOKEN_REDIRECT_IN);
	else if ((*input)[0] == '(')
		ret = token_add_back(token, "(", TOKEN_OPEN_PARENTESIS);
	else if ((*input)[0] == ')')
		ret = token_add_back(token, ")", TOKEN_CLOSE_PARENTESIS);
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
		if (ft_isquote((*input)[i]))
		{
			quote = (*input)[i++];
			while ((*input)[i] && (*input)[i] != quote)
				i++;
			if (!(*input)[i])
				return (ft_fprintf(2, "syntax error: unclosed quote\n"), FAIL);
		}
		i++;
	}
	value = ft_substr(*input, 0, i);
	if (!value)
		return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
	ret = token_add_back(token, value, TOKEN_WORD);
	free(value);
	*input += i;
	return (ret);
}

int	get_highlevel_operator(t_token **token, char **input)
{
	if ((*input)[0] == '|' && (*input)[1] != '|')
		return (token_add_back(token, "|", TOKEN_PIPE));
	else if ((*input)[0] == '&' && (*input)[1] == '&')
		return ((*input)++, token_add_back(token, "||", TOKEN_AND));
	else if ((*input)[0] == '|' && (*input)[1] == '|')
		return ((*input)++, token_add_back(token, "||", TOKEN_OR));
	else if ((*input)[0] == '&')
		return (ft_putstr_fd("sintax error near '&'\n", 2), FAIL);
	return (ERROR);
}
