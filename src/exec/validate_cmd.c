/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:43:28 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/10 17:45:08 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error_handling.h"
#include "minishell.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int	get_bin_paths(char **envv, char ***bin_paths);
static int	verify_cmd_in_bin_paths(char *cmd, char **bin_paths, char **aux);
static char	*construct_path(char *bin_path, char *cmd);

int	validate_cmd(char *cmd, t_shell *shell)
{
	char	**bin_paths;
	char	*aux;
	char	*cmd_expanded;
	int		ret;

	cmd_expanded = ft_strdup(cmd);
	if (!cmd_expanded)
		return (ERROR);
	ret = expand_string(&cmd_expanded, shell);
	if (ret != OK)
		return (free(cmd_expanded), ERROR);
	if (access(cmd_expanded, X_OK) == 0)
		return (free(cmd_expanded), OK);
	ret = get_bin_paths(shell->envv, &bin_paths);
	if (ret != OK)
		return (free(cmd_expanded), ret);
	ret = verify_cmd_in_bin_paths(cmd_expanded, bin_paths, &aux);
	free(cmd_expanded);
	ft_free_arr(&bin_paths);
	if (ret != OK)
		return (ret);
	free(aux);
	return (OK);
}

int	get_cmd_path(char **exec, char *cmd, char *envv[])
{
	char	**bin_paths;
	int		ret;

	ret = 1;
	if (access(cmd, X_OK) == 0)
	{
		*exec = ft_strdup(cmd);
		if (!*exec)
			return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
		return (OK);
	}
	ret = get_bin_paths(envv, &bin_paths);
	if (ret != OK)
		return (ret);
	ret = verify_cmd_in_bin_paths(cmd, bin_paths, exec);
	ft_free_arr(&bin_paths);
	if (ret != OK)
		return (ret);
	return (OK);
}

static int	verify_cmd_in_bin_paths(char *cmd, char **bin_paths, char **aux)
{
	while (*bin_paths)
	{
		*aux = construct_path(*bin_paths, cmd);
		if (!*aux)
			return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
		if (access(*aux, X_OK) == 0)
			return (OK);
		free(*aux);
		bin_paths++;
	}
	ft_putstr_fd("Command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	return (FAIL);
}

static char	*construct_path(char *bin_path, char *cmd)
{
	char	*res;
	size_t	len;

	len = ft_strlen(bin_path) + ft_strlen(cmd) + 2;
	res = ft_calloc(len, sizeof(char));
	if (!res)
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
	ft_strlcpy(res, bin_path, len);
	if (ft_strlen(res) > 0 && res[ft_strlen(res) -1] != '/')
		ft_strlcat(res, "/", len);
	ft_strlcat(res, cmd, len);
	return (res);
}

static int	get_bin_paths(char **envv, char ***bin_paths)
{
	while (*envv)
	{
		if (ft_strncmp(*envv, "PATH=", 5) == 0)
			break ;
		envv++;
	}
	if (*envv == NULL)
		return (FAIL);
	*bin_paths = ft_split((*envv + 5), ':');
	if (!*bin_paths)
		return (ft_putstr_fd(ERR_MALLOC, 2), ERROR);
	return (OK);
}
