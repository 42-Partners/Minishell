/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:09:31 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/21 17:09:31 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ast.h"
#include <stdio.h>

void		print_ast(t_ast_node *ast);
static void	print_cmd(t_cmd_node node, int ident_level);
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
	}
}

static void	print_ast_identaded(t_ast_node *ast, int ident_level)
{
	if (!ast)
	{
		print_idents_text(ident_level, "<NULL/>");
		return ;
	}
	if (ast->type == CMD)
		print_cmd(ast->t_node.cmd_node, ident_level);
	else if (ast->type == PIPE)
	{
		print_idents_text(ident_level, "<PIPE>");
		print_ast_identaded(ast->t_node.pipe_node.left, ident_level + 1);
		print_ast_identaded(ast->t_node.pipe_node.right, ident_level + 1);
		print_idents_text(ident_level, "<PIPE/>");
	}
	else if (ast->type == LOGICAL)
	{
		if (ast->t_node.logical_node.type == AND)
			print_idents_text(ident_level, "<LOGICAL AND>");
		if (ast->t_node.logical_node.type == OR)
			print_idents_text(ident_level, "<LOGICAL OR>");
		print_ast_identaded(ast->t_node.logical_node.left, ident_level + 1);
		print_ast_identaded(ast->t_node.logical_node.right, ident_level + 1);
		print_idents_text(ident_level, "<LOGICAL/>");
	}
}

static void	print_cmd(t_cmd_node node, int ident_level)
{
	int	i;

	i = 0;
	print_idents_text(ident_level, NULL);
	printf("<CMD> %s", node.cmd);
	if (node.args)
	{
		printf(" args=[");
		i = 0;
		while (node.args[i])
		{
			printf("\"%s\"", node.args[i]);
			if (node.args[i + 1])
				printf(", ");
			i++;
		}
		printf("]");
	}
	if (node.redirect_count > 0)
		printf(" redirects=%d ", node.redirect_count);
	printf("<CMD/>\n");
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
