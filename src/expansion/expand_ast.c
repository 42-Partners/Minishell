/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:38:34 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/23 04:48:09 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

#include <stdlib.h>

static void	expand_string(char **s);
void		handle_single_quote(char **result, char *s, int *index);
void		handle_double_quote(char **result, char *s, int *index);
void		handle_dollar(char **result, char *s, int *index);
void		handle_literal(char **result, char *s, int *index);
void		expand_env(char **result, char *s, int *index);

void	expand_ast(t_ast_node *ast)
{
	int	i;

	if (!ast)
		return ;
	i = 0;
	if (ast->type == CMD)
	{
		while (ast->t_node.cmd_node.args[i])
			expand_string(&ast->t_node.cmd_node.args[i++]);
	}
	else if (ast->type == PIPE)
	{
		expand_ast(ast->t_node.pipe_node.left);
		expand_ast(ast->t_node.pipe_node.right);
	}
}

static void	expand_string(char **s)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	while ((*s)[i])
	{
		if ((*s)[i] == '\'')
			handle_single_quote(&result, *s, &i);
		else if ((*s)[i] == '"')
			handle_double_quote(&result, *s, &i);
		else if ((*s)[i] == '$')
			handle_dollar(&result, *s, &i);
		else
			handle_literal(&result, *s, &i);
	}
	free(*s);
	*s = result;
}
