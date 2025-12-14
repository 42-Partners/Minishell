/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:50:05 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/13 18:57:28 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_token	*tokenize(t_token *token, char *input)
{
	int	ret;

	ret = 0;
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			break ;
		if (invalid_token(*input))
		{
			ft_putstr_fd("syntax error: invalid token\n", 2);
			return (free_token(&token), NULL);
		}
		else if (is_operator(*input))
			ret = get_operator(&token, &input);
		else if (is_quote(*input))
			ret = get_quote(&token, &input);
		else
			ret = get_word(&token, &input);
		if (!ret)
			return (free_token(&token), NULL);
	}
	return (token);
}
