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
static int	ft_getenv_index(char *env, char *envv[], int *index);
static int	expand_envv(char **envv[]);

int	ft_getenv(char *env, char *envv[], char **result)
{
	int	index;

	index = 0;
	if (ft_getenv_index(env, envv, &index))
		return (ERROR);
	if (index < 0)
		return (OK);
	*result = ft_strdup(envv[index] + ft_strlen(env) + 1);
	if (!*result)
		return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
	return (OK);
}

int	ft_setenv(char *name, char *value, char **envv[])
{
	char	*full_env;
	int		index;

	index = 0;
	if (ft_getenv_index(name, *envv, &index) != OK)
		return (ERROR);
	full_env = build_env(name, value);
	if (!full_env)
		return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
	if (index < 0)
	{
		if (expand_envv(envv) != OK)
			return (free(full_env), ERROR);
		while ((*envv)[++index])
			;
		(*envv)[index] = full_env;
	}
	else
	{
		free((*envv)[index]);
		(*envv)[index] = full_env;
	}
	return (OK);
}

static int	ft_getenv_index(char *env, char *envv[], int *index)
{
	char	*aux;

	aux = build_env(env, NULL);
	if (!aux)
		return (ERROR);
	while (envv[*index] != NULL)
	{
		if (ft_strncmp(envv[*index], aux, ft_strlen(aux)) == 0)
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

static int	expand_envv(char **envv[])
{
	char	**duplicate;
	int		i;

	i = 0;
	while ((*envv)[i])
		i++;
	duplicate = malloc((i + 2) * sizeof(char *));
	if (!duplicate)
		return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
	i = -1;
	while ((*envv)[++i])
	{
		duplicate[i] = ft_strdup((*envv)[i]);
		if (!duplicate[i])
		{
			ft_free_arr(&duplicate);
			return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
		}
	}
	duplicate[i] = NULL;
	duplicate[i + 1] = NULL;
	ft_free_arr(envv);
	*envv = duplicate;
	return (OK);
}
