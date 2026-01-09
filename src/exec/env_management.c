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

static char	*build_env(char *name, char *value);
static int	ft_getenv_index(char *env, char *envv[]);
static int	expand_envv(char **envv[]);

char	*ft_getenv(char *env, char *envv[])
{
	int	index;

	index = ft_getenv_index(env, envv);
	if (index < 0)
		return (NULL);
	return (ft_strdup(envv[index] + ft_strlen(env) + 1));
}

int	ft_setenv(char *name, char *value, char **envv[])
{
	int		index;
	char	*full_env;

	index = ft_getenv_index(name, *envv);
	full_env = build_env(name, value);
	if (!full_env)
		return (ft_printf("Malloc Error:"), -1);
	if (index < 0)
	{
		if (expand_envv(envv) < 0)
			return (ft_printf("Malloc Error:"), -1);
		while ((*envv)[++index])
			;
		(*envv)[index] = full_env;
	}
	else
	{
		free((*envv)[index]);
		(*envv)[index] = full_env;
	}
	return (1);
}

static int	ft_getenv_index(char *env, char *envv[])
{
	int		i;
	char	*aux;

	i = 0;
	aux = build_env(env, NULL);
	if (!aux)
		return (-1);
	while (envv[i] != NULL)
	{
		if (ft_strncmp(envv[i], aux, ft_strlen(aux)) == 0)
			return (free(aux), i);
		i++;
	}
	free(aux);
	return (-1);
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
		return (-1);
	i = -1;
	while ((*envv)[++i])
	{
		duplicate[i] = ft_strdup((*envv)[i]);
		if (!duplicate[i])
		{
			while (--i >= 0)
				free(duplicate[i]);
			return (free(duplicate), -1);
		}
	}
	duplicate[i] = NULL;
	duplicate[i + 1] = NULL;
	ft_free_arr(envv);
	*envv = duplicate;
	return (1);
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
		return (ft_printf("Malloc error:"), NULL);
	aux = ft_strjoin(full_env, "=");
	free(full_env);
	if (!aux)
		return (ft_printf("Malloc error:"), NULL);
	full_env = ft_strjoin(aux, value);
	free(aux);
	if (!full_env)
		return (ft_printf("Malloc error:"), NULL);
	return (full_env);
}
