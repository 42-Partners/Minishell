/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:50:05 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/19 03:05:31 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

#include <stdlib.h>

int		get_operator(t_token **token, char **input);
int		get_word(t_token **token, char **input);
int		is_invalid_token(int c);
int		is_operator(int c);
int		is_quote(int c);

t_token	*tokenize(char *input)
{
	t_token	*token;
	int		ret;

	token = NULL;
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			break ;
		if (is_invalid_token(*input))
		{
			ft_putstr_fd("syntax error: invalid token\n", 2);
			return (free_token(&token), NULL);
		}
		else if (is_operator(*input))
			ret = get_operator(&token, &input);
		else
			ret = get_word(&token, &input);
		if (!ret)
			return (free_token(&token), NULL);
	}
	return (token);
}
