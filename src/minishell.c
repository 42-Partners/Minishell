/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:39:45 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/19 03:15:31 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	input_process(char *input);
static	int	is_exit_cmd(char *input);

int	main(void)
{
	char	*input;

	register_sig_handlers();
	while (1)
	{
		input = readline(PROMPT);
		if (!input_process(input))
			break ;
	}
	return (0);
}

static int	input_process(char *input)
{
	t_token	*token;
	int		i;

	i = 0;
	if (!input)
		return (0);
	while (ft_isspace(input[i]))
		i++;
	if (is_exit_cmd(&input[i]))
		return (free(input), 0);
	if (!input[i])
		return (free(input), 1);
	add_history(input);
	token = tokenize(&input[i]);
	free(input);
	if (!token)
		return (1);
	free_token(&token);
	return (1);
}

static	int	is_exit_cmd(char *input)
{
	if (ft_strncmp(input, "exit", 4) == 0)
	{
		input += 4;
		while (ft_isspace(*input))
			input++;
		return (*input == '\0');
	}
	return (0);
}
