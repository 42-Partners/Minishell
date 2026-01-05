/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:38:34 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/30 01:03:57 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

#include <stdlib.h>

void		expand_string(char **s, int *status, char *envv[]);
void		handle_single_quote(char **result, char *s, int *index);
void		handle_double_quote(char **result, char *s, int *index,
				t_shell_env shell);
void		handle_dollar(char **result,
				char *s, int *index, t_shell_env shell);
void		handle_literal(char **result, char *s, int *index);
void		expand_env(char **result, char *s, int *index, char *envv[]);

void	expand_cmd(t_cmd_node *cmd, int *status, char *envv[])
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->cmd)
	{
		i = -1;
		while (cmd->args[++i])
			expand_string(&cmd->args[i], status, envv);
		cmd->cmd = cmd->args[0];
	}
	i = -1;
	while (++i < cmd->redirect_count)
		expand_string(&(cmd->redirects[i]->file_name),
			status, envv);
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
			handle_double_quote(&result, *s, &i, (t_shell_env){status, &envv});
		else if ((*s)[i] == '$')
			handle_dollar(&result, *s, &i, (t_shell_env){status, &envv});
		else
			handle_literal(&result, *s, &i);
	}
	free(*s);
	*s = result;
}
