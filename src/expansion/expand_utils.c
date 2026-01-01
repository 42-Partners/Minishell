/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 23:51:37 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/23 04:47:07 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

static int	is_var_char(int c);
char		*strjoin_free(char *s1, char *s2);

int	expand_env(char **result, char *cmd, int *index)
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
	env = getenv(fragment);
	if (!env)
		*result = strjoin_free(*result, "");
	else
		*result = strjoin_free(*result, env);
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
	*result = strjoin_free(*result, fragment);
	free(fragment);
	if (!*result)
		return (ERROR);
	return (OK);
}

static int	is_var_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	str_len;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = 0;
	if (s2)
		s2_len = ft_strlen(s2);
	str_len = s1_len + s2_len;
	str = malloc(str_len + 1);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	str[str_len] = '\0';
	free(s1);
	s1 = str;
	return (s1);
}
