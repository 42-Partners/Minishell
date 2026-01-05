/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:38:34 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/05 20:35:29 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include "error_handling.h"

#include <stdlib.h>

int expand_string(char **s, int *status);
int	handle_single_quote(char **result, char *s, int *index);
int	handle_double_quote(char **result, char *s, int *index, int *status);
int	handle_dollar(char **result, char *s, int *index, int *status);
int	handle_literal(char **result, char *s, int *index);
int	expand_env(char **result, char *s, int *index);

int	expand_cmd(t_cmd_node *cmd, int *status, char *envv[])
{
	int	ret;
	int	i;

	if (!cmd)
        return ;
	ret = OK;
    if (cmd->cmd)
    {
        i = -1;
        while (cmd->args[++i])
		{
            ret = expand_string(&cmd->args[i], status, envv);
			if (ret != OK)
				return (ERROR);
		}
        cmd->cmd = cmd->args[0];
    }
    i = -1;
    while (++i < cmd->redirect_count)
	{
        ret = expand_string(&(cmd->redirects[i]->file_name), status, envv);
		if (ret != OK)
			return (ERROR);
	}
	return (OK);
}

int	expand_string(char **cmd, int *status, char *envv[])
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

void	expand_string(char **s, int *status, char *envv[])
{
	char		*result;
	int			i;

	i = 0;
	result = ft_strdup("");
	while ((*s)[i])
	{
		if ((*s)[i] == '\'')
			handle_single_quote(&result, *s, &i);
		else if ((*s)[i] == '"')
			handle_double_quote(&result, *s, &i, t_shell_env env);
		else if ((*s)[i] == '$')
			handle_dollar(&result, *s, &i, (t_shell_env){status, &envv});
		else
			handle_literal(&result, *s, &i);
	}
	free(*s);
	*s = result;
}
