/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:50:05 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/27 15:59:35 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

#include <stdlib.h>

static t_token	*set_token(t_token **token, char *input);
static char		*find_end_of_command(char *input);
int				get_operator(t_token **token, char **input);
int				get_word(t_token **token, char **input);
int				is_invalid_token(int c);
int				is_operator(int c);
int				is_quote(int c);

t_token	*tokenize(char **input)
{
	t_token	*token;
	char	*line;
	char	*end_cmd;

	token = NULL;
	end_cmd = find_end_of_command(*input);
	if (end_cmd)
	{
		line = ft_substr(*input, 0, end_cmd - *input);
		*input = end_cmd + 1;
		token = set_token(&token, line);
		free(line);
	}
	else
	{
		line = *input;
		token = set_token(&token, line);
		*input = ft_strchr(*input, '\0');
	}
	return (token);
}

static t_token	*set_token(t_token **token, char *input)
{
	int	ret;

	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			break ;
		if (is_invalid_token(*input))
		{
			ft_putstr_fd("syntax error: invalid token\n", 2);
			return (free_token(token), NULL);
		}
		else if (is_operator(*input))
			ret = get_operator(token, &input);
		else
			ret = get_word(token, &input);
		if (!ret)
			return (free_token(token), NULL);
	}
	return (*token);
}

static char	*find_end_of_command(char *input)
{
	char	quote;
	int		i;

	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return (NULL);
			i++;
		}
		else if (input[i] == '\n')
			return (&input[i]);
		else
			i++;
	}
	return (NULL);
}
