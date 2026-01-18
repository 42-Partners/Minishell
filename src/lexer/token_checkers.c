/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:30:17 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/04 20:27:04 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int	is_invalid_token(int c)
{
	return (c == ';' || c == '(' || c == ')');
}

int	is_operator(int c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_word(int c)
{
	return (!is_invalid_token(c) && !ft_isspace(c) && !is_operator(c));
}
