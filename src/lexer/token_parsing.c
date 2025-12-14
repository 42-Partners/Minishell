/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:31:57 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/13 18:36:23 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	get_operator(t_token **token, char **input)
{
	int	ret;

	ret = 0;
	if (**input == '>' && *(*(input) + 1) == '>')
	{
		ret = token_add_back(token, ">>", TOKEN_REDIRECT_APPEND);
		(*input)++;
	}
	else if (**input == '<' && *(*(input) + 1) == '<')
	{
		ret = token_add_back(token, "<<", TOKEN_HEREDOC);
		(*input)++;
	}
	else if (**input == '|')
		ret = token_add_back(token, "|", TOKEN_PIPE);
	else if (**input == '>')
		ret = token_add_back(token, ">", TOKEN_REDIRECT_OUT);
	else if (**input == '<')
		ret = token_add_back(token, "<", TOKEN_REDIRECT_IN);
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
	{
		ft_putstr_fd("syntax error: unclosed quote\n", 2);
		return (0);
	}
	size = end - start;
	value = ft_substr(start, 0, size);
	if (!value)
	{
		perror("malloc error");
		return (ret);
	}
	ret = token_add_back(token, value, TOKEN_WORD);
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
	while ((*input)[i] && !invalid_token((*input)[i])
		&& !ft_isspace((*input)[i]) && !is_operator((*input)[i])
		&& !is_quote((*input)[i]))
		i++;
	value = ft_substr(*input, 0, i);
	if (!value)
	{
		perror("Error");
		return (ret);
	}
	ret = token_add_back(token, value, TOKEN_WORD);
	free(value);
	*input += i;
	return (ret);
}
