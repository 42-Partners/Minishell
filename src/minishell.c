/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:39:45 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/05 20:35:18 by devrafaelly      ###   ########.fr       */
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
	int			ret;

	ast = build_ast(token);
	free_token(&token);
	ret = OK;
	if (!ast)
		return (ERROR);
	ret = validate_ast(&ast);
	if (ret != OK)
		return (free_ast(&ast), ret);
	ret = check_cmds(&ast, envv);
	if (ret == FAIL)
	{
		*status = 127;
		return (ret);
	}
	else if (ret == ERROR)
		return (free_ast(&ast), ret);
	if (read_all_here_docs(ast, status) != OK)
		return (free_ast(&ast), ret);
	exec_ast(ast, envv, status);
	free_ast(&ast);
	return (OK);
}
