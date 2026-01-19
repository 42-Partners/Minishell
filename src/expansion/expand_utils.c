/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 23:51:37 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/14 20:45:19 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error_handling.h"

#include <stdlib.h>

static int	is_var_char(int c);

int	expand_env(char **result, char *cmd, int *index, char *envp[])
{
	char	*env;
	char	*fragment;
	int		i;

	i = *index;
	while (cmd[i] && is_var_char(cmd[i]))
		i++;
	fragment = ft_substr(cmd, *index, i - *index);
	if (!fragment)
		return (ERROR);
	env = NULL;
	if (ft_getenv(fragment, envp, &env) != OK)
		return (free(fragment), ERROR);
	if (!env)
		*result = ft_strjoin_free(*result, "");
	else
		*result = ft_strjoin_free(*result, env);
	free(env);
	free(fragment);
	if (!*result)
		return (ERROR);
	*index = i;
	return (OK);
}

int	append_fragment(char **result, char *cmd, int start, int i)
{
	char	*fragment;

	fragment = ft_substr(cmd, start, i - start);
	if (!fragment)
		return (ERROR);
	*result = ft_strjoin_free(*result, fragment);
	free(fragment);
	if (!*result)
		return (ERROR);
	return (OK);
}

static int	is_var_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}
