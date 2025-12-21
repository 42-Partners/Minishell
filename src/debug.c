/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:23:05 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/20 04:27:57 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ast.h"
#include <stdio.h>

void		debug_flag(char *print_mgs);
void		print_tokens(t_token *tokens, char *custom);
void		print_ast(t_ast_node *ast);
static char	*get_token_type(t_token token);
static void	print_idents_text(int ident_level, char *txt);
static void	print_ast_identaded(t_ast_node *ast, int ident_level);

void	print_ast(t_ast_node *ast)
{
	if (!ast)
	printf("AST NULL\n");
	else
	{
		printf("\nAST:\n");
		print_ast_identaded(ast, 0);
		printf("\n");
	}
}

static void	print_ast_identaded(t_ast_node *ast, int ident_level)
{
	int	i;

	i = 0;
	if (!ast)
	{
		print_idents_text(ident_level, "<NULL/>");
		return ;
	}
	if (ast->type == CMD)
	{
		print_idents_text(ident_level, NULL);
		printf("<CMD NODE redirect_count=%d> %s",
			ast->t_node.cmd_node.redirect_count, ast->t_node.cmd_node.cmd);
		if (ast->t_node.cmd_node.args)
		{
			printf(" args=[");
			i = 0;
			while (ast->t_node.cmd_node.args[i])
			{
				printf("\"%s\"", ast->t_node.cmd_node.args[i]);
				if (ast->t_node.cmd_node.args[i + 1])
					printf(", ");
				i++;
			}
			printf("]");
		}
		printf("<CMD NODE/>\n");
	}
	else if (ast->type == PIPE)
	{
		print_idents_text(ident_level, "<PIPE NODE>");
		print_ast_identaded(ast->t_node.pipe_node.left, ident_level + 1);
		print_ast_identaded(ast->t_node.pipe_node.right, ident_level + 1);
		print_idents_text(ident_level, "<PIPE NODE/>");
	}
}

static void	print_idents_text(int ident_level, char *txt)
{
	int	i;

	i = -1;
	while (++i < ident_level)
		printf("	");
	if (txt)
		printf("%s\n", txt);
}

void	debug_flag(char *print_mgs)
{
	printf("%s\n", print_mgs);
}

void	print_tokens(t_token *tokens, char *custom)
{
	int	silent;

	silent = 0;
	if (custom)
	{
		if (*custom == '@')
			silent = ((*(custom++) * 0) + 1);
		if (custom)
			printf("%s", custom);
	}
	if (!tokens)
		printf("NULL TOKENS");
	while (tokens)
	{
		printf("<TOKEN type=%s", get_token_type(*tokens));
		if (tokens->type == TOKEN_WORD && !silent)
			printf(" content =\"%s\"", tokens->value);
		printf("/>");
		tokens = tokens->next;
	}
	printf("\n");
}

static char	*get_token_type(t_token token)
{
	if (token.type == TOKEN_WORD)
		return ("WORD");
	else if (token.type == TOKEN_HEREDOC)
		return ("HERE_DOC");
	else if (token.type == TOKEN_PIPE)
		return ("PIPE");
	else if (token.type == TOKEN_REDIRECT_IN)
		return ("RED_IN");
	else if (token.type == TOKEN_REDIRECT_OUT)
		return ("RED_OUT");
	else if (token.type == TOKEN_REDIRECT_APPEND)
		return ("RED_APPEND");
	else
		return ("ERROR");
}
