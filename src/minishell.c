/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:39:45 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/26 16:17:54 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"
#include "ast.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	input_process(char *input, char *envv[], int *status);
static int	parse_and_execute(t_token *tokens, char *envv[], int *status);

int	main(int argc, char *argv[], char *envv[])
{
	char	*input;
	int		status;

	(void)argc;
	(void)argv;
	status = 0;
	register_sig_handlers();
	while (1)
	{
		input = readline(PROMPT);
		g_signal = 0;
		if (!input_process(input, envv, &status))
			break ;
	}
	return (0);
}

static int	input_process(char *input, char *envv[], int *status)
{
	t_token	*token;
	int		i;

	i = 0;
	if (!input)
		return (0);
	while (ft_isspace(input[i]))
		i++;
	if (!input[i])
		return (free(input), 1);
	add_history(input);
	token = tokenize(&input[i]);
	free(input);
	if (!token)
		return (1);
	return (parse_and_execute(token, envv, status) == 0);
}

static int	parse_and_execute(t_token *token, char *envv[], int *status)
{
	t_ast_node	*ast;

	ast = build_ast(token);
	free_token(&token);
	if (!ast)
		return (1);
	validate_ast(&ast);
	if (!ast)
		return (1);
	check_cmds(&ast, envv);
	if (!ast)
		return (*status = 127, 0);
	if (read_all_here_docs(ast) == -1)
	{
		free_ast(&ast);
		return (0);
	}
	exec_ast(ast, envv, status);
	free_ast(&ast);
	return (0);
}
