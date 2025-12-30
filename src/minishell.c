/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:39:45 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/29 21:49:47 by gustaoli         ###   ########.fr       */
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
	envv = ft_str_arr_dup(envv);
	status = 0;
	register_sig_handlers();
	while (1)
	{
		input = readline(PROMPT);
		g_signal = 0;
		if (input_process(input, envv, &status) < 0)
			break ;
	}
	ft_free_arr(&envv);
	close(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
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
		return (-1);
	while (ft_isspace(*line))
		line++;
	if (!*line)
		return (free(input), 1);
	add_history(input);
	while (*line)
	{
		token = tokenize(&line);
		if (!token)
			return (free(input), -1);
		ret = parse_and_execute(token, envv, status);
		if (ret != 1)
			return (free(input), ret);
	}
	return (free(input), 1);
}

static int	parse_and_execute(t_token *token, char *envv[], int *status)
{
	t_ast_node	*ast;

	ast = build_ast(token);
	free_token(&token);
	if (!ast)
		return (-1);
	validate_ast(&ast);
	if (!ast)
		return (0);
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
	return (1);
}
