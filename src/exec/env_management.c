/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:09:28 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/28 16:09:28 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error_handling.h"

static char	*build_env(char *name, char *value);
static int	ft_getenv_index(char *env, char *envp[], int *index);
static int	expand_envp(char **envp[]);

int	ft_getenv(char *env, char *envp[], char **result)
{
	int	index;

	index = 0;
	if (ft_getenv_index(env, envp, &index))
		return (ERROR);
	if (index < 0)
	{
		*result = NULL;
		return (OK);
	}
	*result = ft_strdup(envp[index] + ft_strlen(env) + 1);
	if (!*result)
		return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
	return (OK);
}

int	ft_setenv(char *name, char *value, char **envp[])
{
	char	*full_env;
	int		index;

	index = 0;
	if (ft_getenv_index(name, *envp, &index) != OK)
		return (ERROR);
	full_env = build_env(name, value);
	if (!full_env)
		return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
	if (index < 0)
	{
		if (expand_envp(envp) != OK)
			return (free(full_env), ERROR);
		while ((*envp)[++index])
			;
		(*envp)[index] = full_env;
	}
	else
	{
		free((*envp)[index]);
		(*envp)[index] = full_env;
	}
	return (OK);
}

static int	ft_getenv_index(char *env, char *envp[], int *index)
{
	char	*aux;

	aux = build_env(env, NULL);
	if (!aux)
		return (ERROR);
	while (envp[*index] != NULL)
	{
		if (ft_strncmp(envp[*index], aux, ft_strlen(aux)) == 0)
			return (free(aux), OK);
		(*index)++;
	}
	free(aux);
	*index = -1;
	return (OK);
}

static char	*build_env(char *name, char *value)
{
	char	*full_env;
	char	*aux;

	if (!name)
		return (NULL);
	if (!value)
		value = "";
	full_env = ft_strdup(name);
	if (!full_env)
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
	aux = ft_strjoin(full_env, "=");
	free(full_env);
	if (!aux)
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
	full_env = ft_strjoin(aux, value);
	free(aux);
	if (!full_env)
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
	return (full_env);
}

static int	expand_envp(char **envp[])
{
	char	**duplicate;
	int		i;

	i = 0;
	while ((*envp)[i])
		i++;
	duplicate = malloc((i + 2) * sizeof(char *));
	if (!duplicate)
		return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
	i = -1;
	while ((*envp)[++i])
	{
		duplicate[i] = ft_strdup((*envp)[i]);
		if (!duplicate[i])
		{
			ft_free_arr(&duplicate);
			return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
		}
	}
	duplicate[i] = NULL;
	duplicate[i + 1] = NULL;
	ft_free_arr(envp);
	*envp = duplicate;
	return (OK);
}
