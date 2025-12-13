/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:30:17 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/13 18:30:33 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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
