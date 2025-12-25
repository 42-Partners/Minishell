/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:38:34 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/25 16:46:06 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

#include <stdlib.h>

static void	expand_string(char **s, int* status);
void		handle_single_quote(char **result, char *s, int *index);
void		handle_double_quote(char **result, char *s, int *index, int* status);
void		handle_dollar(char **result, char *s, int *index, int* status);
void		handle_literal(char **result, char *s, int *index);
void		expand_env(char **result, char *s, int *index);

void	expand_ast(t_ast_node *ast, int *stts)
{
	int	i;

	if (!ast)
		return ;
	i = 0;
	if (ast->type == CMD)
	{
		if (ast->t_node.cmd_node.cmd)
			expand_string(&(ast->t_node.cmd_node.cmd), stts);
		while (ast->t_node.cmd_node.args[i])
			expand_string(&ast->t_node.cmd_node.args[i++], stts);
		i = 0;
		while (i < ast->t_node.cmd_node.redirect_count)
			expand_string(&(ast->t_node.cmd_node.redirects[i]->file_name), stts);
	}
}

static void	expand_string(char **s, int* status)
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
			handle_double_quote(&result, *s, &i, status);
		else if ((*s)[i] == '$')
			handle_dollar(&result, *s, &i, status);
		else
			handle_literal(&result, *s, &i);
	}
	free(*s);
	*s = result;
}
