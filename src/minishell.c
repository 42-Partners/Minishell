/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:39:45 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/23 04:41:50 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"
#include "ast.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	input_process(char *input, char *envv[]);
static int	is_exit_cmd(char *input);
static int	parse_and_expand(t_token *tokens, char *envv[]);

int	main(int argc, char *argv[], char *envv[])
{
	char	*input;

	(void)argc;
	(void)argv;
	register_sig_handlers();
	while (1)
	{
		input = readline(PROMPT);
		if (!input_process(input, envv))
			break ;
	}
	return (0);
}

static int	input_process(char *input, char *envv[])
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
	return (parse_and_expand(token, envv));
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

static int	parse_and_expand(t_token *token, char *envv[])
{
	t_ast_node	*ast;
	int			ret;

	print_tokens(token, "@Tokens= ");
	ast = build_ast(token);
	free_token(&token);
	if (!ast)
		return (1);
	validate_ast(&ast);
	check_cmds(&ast, envv);
	expand_ast(ast);
	print_ast(ast);
	free_ast(&ast);
	return (1);
}
