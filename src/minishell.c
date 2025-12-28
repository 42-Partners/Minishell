/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:39:45 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/27 19:42:39 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"
#include "ast.h"
#include "exec.h"
#include "error_handling.h"

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
	while (OK)
	{
		input = readline(PROMPT);
		g_signal = 0;
		if (input_process(input, envv, &status) == ERROR)
			break ;
	}
	return (0);
}

static int	input_process(char *input, char *envv[], int *status)
{
	t_token	*token;
	char	*line;
	int		ret;

	line = input;
	ret = 1;
	if (!line)
		return (ERROR);
	while (ft_isspace(*line))
		line++;
	if (!*line)
		return (free(input), OK);
	add_history(input);
	while (*line)
	{
		token = tokenize(&line);
		if (!token)
			return (free(input), ERROR);
		ret = parse_and_execute(token, envv, status);
		if (ret != OK)
			return (free(input), ret);
	}
	return (free(input), OK);
}

static int	parse_and_execute(t_token *token, char *envv[], int *status)
{
	t_ast_node	*ast;

	ast = build_ast(token);
	free_token(&token);
	if (!ast)
		return (ERROR);
	if (!validate_ast(&ast))
		return (FAIL);
	if (!check_cmds(&ast, envv))
		return (*status = 127, FAIL);
	if (read_all_here_docs(ast) == ERROR)
	{
		free_ast(&ast);
		return (FAIL);
	}
	exec_ast(ast, envv, status);
	free_ast(&ast);
	return (OK);
}
