/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:43:28 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/27 20:11:27 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "libft.h"
#include "error_handling.h"

static char	**get_bin_paths(char **envv);
static char	*verify_cmd_in_bin_paths(char *cmd, char **bin_paths);
static char	*construct_path(char *bin_path, char *cmd);

int	validate_cmd(char *cmd, char **envv)
{
	char	**bin_paths;
	char	*aux;

	if (access(cmd, X_OK) == 0)
		return (OK);
	bin_paths = get_bin_paths(envv);
	if (!bin_paths)
		return (ERROR); //! aqui eu nao sei qual colocar, a funçao retorna NULL pra erro de malloc (ERROR) e NULL pra caso nao encontre PATH= certo? Mas isso deveria parar o minishell?
	aux = verify_cmd_in_bin_paths(cmd, bin_paths);
	if (aux == NULL)
	{
		ft_printf("Command not found: %s\n", cmd); //! aqui tambem pode ser erro de malloc, retorna diferente
		ft_free_arr(bin_paths);
		return (FAIL);
	}
	free(aux);
	ft_free_arr(bin_paths);
	return (OK);
}

char	*get_cmd_path(char *cmd, char *envv[])
{
	char	**bin_paths;
	char	*aux;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	bin_paths = get_bin_paths(envv);
	if (!bin_paths)
		return (NULL);
	aux = verify_cmd_in_bin_paths(cmd, bin_paths);
	if (aux == NULL)
	{
		ft_printf("Command not found: %s\n", cmd); //! aqui tambem pode ser erro de malloc
		ft_free_arr(bin_paths);
		return (NULL);
	}
	ft_free_arr(bin_paths);
	return (aux);
}

static char	*verify_cmd_in_bin_paths(char *cmd, char **bin_paths)
{
	char	*full_bin_path;

	while (*bin_paths != NULL)
	{
		full_bin_path = construct_path(*bin_paths, cmd); //! aqui tem malloc, mas nao tem verificaçao
		if (!full_bin_path) // adicionei aqui
			return (NULL);
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
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
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
	if (*envv == NULL)
		return (NULL);
	res = ft_split((*envv + 5), ':');
	if (!res)
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
	return (res);
}
