/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:39:45 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/14 09:58:29 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	input_process(t_token **token, char *input);

int	main(void)
{
	t_token	*token;
	char	*input;

	token = NULL;
	register_sig_handlers();
	while (1)
	{
		input = readline("42Partners@minishell: ");
		if (!input_process(&token, input))
			break ;
	}
	return (0);
}

static int	input_process(t_token **token, char *input)
{
	if (!input || ft_strcmp(input, "exit") == 0)
	{
		if (input)
			free(input);
		return (0);
	}
	if (*input)
	{
		add_history(input);
		*token = tokenize(*token, input);
		if (!*token)
		{
			free(input);
			return (1);
		}
		free_token(token);
	}
	free(input);
	return (1);
}
