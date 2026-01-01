/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:38:34 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/25 17:24:19 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

#include <stdlib.h>

static int	expand_string(char **s, int *status);
int		handle_single_quote(char **result, char *s, int *index);
int		handle_double_quote(char **result, char *s, int *index,
				int *status);
int		handle_dollar(char **result, char *s, int *index, int *status);
int		handle_literal(char **result, char *s, int *index);
int		expand_env(char **result, char *s, int *index);

int	expand_ast(t_ast_node *ast, int *status)
{
	int	ret;
	int	i;

	if (!ast)
		return (ERROR);
	ret = OK;
	i = 0;
	if (ast->type == CMD)
	{
		if (ast->t_node.cmd_node.cmd)
			ret = expand_string(&(ast->t_node.cmd_node.cmd), status);
		while (ast->t_node.cmd_node.args[i] && ret == OK)
			ret = expand_string(&(ast->t_node.cmd_node.args[i++]), status);
		i = 0;
		while (i < ast->t_node.cmd_node.redirect_count && ret == OK)
			ret = expand_string(&(ast->t_node.cmd_node.redirects[i++]->file_name),
				status);
	}
	if (ret != OK)
		return (ERROR);
	return (OK);
}

static int	expand_string(char **cmd, int *status)
{
	char	*result;
	int		ret;
	int		i;

	ret = OK;
	i = 0;
	result = ft_strdup("");
	if (!result)
		return (ERROR);
	while ((*cmd)[i] && ret == OK)
	{
		if ((*cmd)[i] == '\'')
			ret = handle_single_quote(&result, *cmd, &i);
		else if ((*cmd)[i] == '"')
			ret = handle_double_quote(&result, *cmd, &i, status);
		else if ((*cmd)[i] == '$')
			ret = handle_dollar(&result, *cmd, &i, status);
		else
			ret = handle_literal(&result, *cmd, &i);
	}
	if (ret != OK)
		return (free(result), ERROR);
	free(*cmd);
	*cmd = result;
	return (OK);
}
