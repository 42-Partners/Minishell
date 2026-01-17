/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:39:45 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/16 18:41:02 by gustaoli         ###   ########.fr       */
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

static int	input_process(char *input, t_shell *shell);
static int	parse_and_execute(t_token *token, t_shell *shell);

int	main(int argc, char *argv[], char *envv[])
{
	t_shell	shell;
	char	*input;

	(void)argc;
	(void)argv;
	shell.envv = ft_str_arr_dup(envv);
	shell.ast = NULL;
	if (!shell.envv)
		return (ERROR);
	shell.status = 0;
	register_sig_handlers();
	while (1)
	{
		input = readline(PROMPT);
		g_signal = 0;
		if (input_process(input, &shell) == ERROR)
			break ;
	}
	ft_free_arr(&(shell.envv));
	close(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (OK);
}

static int	input_process(char *input, t_shell *shell)
{
	t_token	*token;
	char	*line;
	int		ret;

	token = NULL;
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
		ret = tokenize(&token, &line);
		if (ret != OK)
			return (free(input), ret);
		ret = parse_and_execute(token, shell);
		if (ret != OK)
			return (free(input), ret);
	}
	return (free(input), OK);
}

static int	parse_and_execute(t_token *token, t_shell *shell)
{
	int			ret;

	shell->ast = build_ast(token);
	free_token(&token);
	ret = OK;
	if (!shell->ast)
		return (ERROR);
	ret = validate_ast(&shell->ast);
	if (ret != OK)
		return (ret);
	ret = check_cmds(&shell->ast, shell);
	if (ret != OK)
	{
		if (ret == FAIL)
			shell->status = 127;
		return (ret);
	}
	if (read_all_here_docs(shell->ast, shell) != OK)
		return (free_ast(&shell->ast), ret);
	exec_ast(shell->ast, shell, 0);
	free_ast(&shell->ast);
	shell->ast = NULL;
	return (OK);
}
