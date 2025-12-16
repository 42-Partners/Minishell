/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:30:17 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/15 23:51:27 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int	invalid_token(int c)
{
	return (c == ';' || c == '(' || c == ')');
}

int	is_operator(int c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_quote(int c)
{
	return (c == '"' || c == '\'');
}

int	is_word(int c)
{
	return (!invalid_token(c) && !ft_isspace(c)
		&& !is_operator(c) && !is_quote(c));
}
