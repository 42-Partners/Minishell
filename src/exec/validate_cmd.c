/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:43:28 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/22 12:38:31 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "libft.h"

static char	**get_bin_paths(char **envv);
static void	free_paths(char **paths);
static char	*verify_cmd_in_bin_paths(char *cmd, char **bin_paths);
static char	*construct_path(char *bin_path, char *cmd);

int	validate_cmd(char *cmd, char **envv)
{
	char	**bin_paths;
	char	*aux;

	if (access(cmd, X_OK) == 0)
		return (1);
	bin_paths = get_bin_paths(envv);
	aux = verify_cmd_in_bin_paths(cmd, bin_paths);
	if (aux == NULL)
	{
		ft_printf("Command not found: %s\n", cmd);
		free_paths(bin_paths);
		return (-1);
	}
	free(aux);
	free_paths(bin_paths);
	return (1);
}

char	*get_cmd_path(char *cmd, char *envv[])
{
	char	**bin_paths;
	char	*aux;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	bin_paths = get_bin_paths(envv);
	aux = verify_cmd_in_bin_paths(cmd, bin_paths);
	if (aux == NULL)
	{
		ft_printf("Command not found: %s\n", cmd);
		free_paths(bin_paths);
		return (NULL);
	}
	free_paths(bin_paths);
	return (aux);
}

static char	*verify_cmd_in_bin_paths(char *cmd, char **bin_paths)
{
	char	*full_bin_path;

	while (*bin_paths != NULL)
	{
		full_bin_path = construct_path(*bin_paths, cmd);
		if (access(full_bin_path, X_OK) == 0)
			return (full_bin_path);
		bin_paths++;
		free(full_bin_path);
	}
	return (NULL);
}

static char	*construct_path(char *bin_path, char *cmd)
{
	char	*res;
	char	*aux;

	res = ft_calloc(ft_strlen(bin_path)
			+ ft_strlen(cmd) + 2, sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcat(res, bin_path, ft_strlen(bin_path) + 1);
	aux = res + ft_strlen(res);
	if (*aux != '/')
		ft_strlcat(aux, "/", 2);
	aux = res + ft_strlen(res);
	ft_strlcat(aux, cmd, ft_strlen(cmd) + 1);
	return (res);
}

static char	**get_bin_paths(char **envv)
{
	char	**res;

	while (*envv != NULL)
	{
		if (ft_strncmp(*envv, "PATH=", 5) == 0)
			break ;
		envv++;
	}
	res = ft_split((*envv + 5), ':');
	if (!res)
		return (NULL);
	return (res);
}

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free(paths);
}
