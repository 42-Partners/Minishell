/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:38:34 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/14 19:30:06 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "libft.h"
#include "error_handling.h"

#include <stdlib.h>

int	expand_string(char **cmd, t_shell *shell);
int	handle_single_quote(char **result, char *s, int *index);
int	handle_double_quote(char **result, char *s, int *index, t_shell *shell);
int	handle_dollar(char **result, char *s, int *index, t_shell *shell);
int	handle_literal(char **result, char *s, int *index);

int	expand_cmd(t_cmd_node *cmd, t_shell *shell)
{
	int	ret;
	int	i;

	if (!cmd)
		return (ERROR);
	ret = OK;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			ret = expand_string(&cmd->args[i++], shell);
			if (ret != OK)
				return (ERROR);
		}
		cmd->cmd = cmd->args[0];
	}
	i = 0;
	while (i < cmd->redirect_count)
	{
		ret = expand_string(&(cmd->redirects[i++]->file_name), shell);
		if (ret != OK)
			return (ERROR);
	}
	return (OK);
}

int	expand_string(char **cmd, t_shell *shell)
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
			ret = handle_double_quote(&result, *cmd, &i, shell);
		else if ((*cmd)[i] == '$')
			ret = handle_dollar(&result, *cmd, &i, shell);
		else
			ret = handle_literal(&result, *cmd, &i);
	}
	if (ret != OK)
		return (free(result), ERROR);
	free(*cmd);
	*cmd = result;
	return (OK);
}
