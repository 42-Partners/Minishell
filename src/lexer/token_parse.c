/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:31:57 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/16 02:36:14 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

#include <stdlib.h>

int	token_add_back(t_token **token, char *value,
		char quote_type, t_token_type type);
int	is_word(int c);

int	get_operator(t_token **token, char **input)
{
	int	ret;

	ret = 0;
	if ((*input)[0] == '>' && (*input)[1] == '>')
	{
		ret = token_add_back(token, ">>", 0, TOKEN_REDIRECT_APPEND);
		(*input)++;
	}
	else if ((*input)[0] == '<' && (*input)[1] == '<')
	{
		ret = token_add_back(token, "<<", 0, TOKEN_HEREDOC);
		(*input)++;
	}
	else if (**input == '|')
		ret = token_add_back(token, "|", 0, TOKEN_PIPE);
	else if (**input == '>')
		ret = token_add_back(token, ">", 0, TOKEN_REDIRECT_OUT);
	else if (**input == '<')
		ret = token_add_back(token, "<", 0, TOKEN_REDIRECT_IN);
	(*input)++;
	return (ret);
}

int	get_quote(t_token **token, char **input)
{
	char	*value;
	char	*start;
	char	*end;
	size_t	size;
	int		ret;

	start = *input + 1;
	end = ft_strchr(start, **input);
	ret = 0;
	if (!end)
		return (ft_putstr_fd("syntax error: unclosed quote\n", 2), 0);
	size = end - start;
	value = ft_substr(start, 0, size);
	if (!value)
		return (ft_putstr_fd("malloc error\n", 2), 0);
	ret = token_add_back(token, value, **input, TOKEN_WORD);
	free(value);
	*input = end + 1;
	return (ret);
}

int	get_word(t_token **token, char **input)
{
	char	*value;
	size_t	i;
	int		ret;

	i = 0;
	ret = 0;
	while ((*input)[i] && is_word((*input)[i]))
		i++;
	value = ft_substr(*input, 0, i);
	if (!value)
		return (ft_putstr_fd("malloc error\n", 2), 0);
	ret = token_add_back(token, value, 0, TOKEN_WORD);
	free(value);
	*input += i;
	return (ret);
}
