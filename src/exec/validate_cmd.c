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
		return (ERROR); //! aqui depende do que vamos fazer com o retorno dessa função
	aux = verify_cmd_in_bin_paths(cmd, bin_paths);
	ft_free_arr(bin_paths);
	if (aux == NULL)
	{
		ft_printf("Command not found: %s\n", cmd); //! aqui tambem pode ser erro de malloc, retorna diferente
		return (FAIL);
	}
	free(aux);
	return (OK);
}

char	*get_cmd_path(char *cmd, char *envv[])
{
	char	**bin_paths;
	char	*aux;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd)); // se NULL, erro de malloc
	bin_paths = get_bin_paths(envv);
	if (!bin_paths)
		return (NULL); //! erro de malloc ou caminho nao encontrado
	aux = verify_cmd_in_bin_paths(cmd, bin_paths);
	ft_free_arr(bin_paths);
	if (!aux)
	{
		ft_printf("Command not found: %s\n", cmd); //! aqui tambem pode ser erro de malloc + tem que estar na saida de erro
		return (NULL); //!depende
	}
	return (aux);
}

static char	*verify_cmd_in_bin_paths(char *cmd, char **bin_paths) //! outra funçao com mesmo retorno mas duas ações
{
	char	*full_bin_path;

	while (*bin_paths)
	{
		full_bin_path = construct_path(*bin_paths, cmd);
		if (!full_bin_path)
			return (NULL); //!erro de malloc
		if (access(full_bin_path, X_OK) == 0)
			return (full_bin_path);
		free(full_bin_path);
		bin_paths++;
	}
	return (NULL); //!cmd nao encontrado
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

static char	**get_bin_paths(char **envv) //! temos que pensar em algo aqui, podemos adicionar uma variavel de erro talvez.
{
	char	**res;

	while (*envv)
	{
		if (ft_strncmp(*envv, "PATH=", 5) == 0)
			break ;
		envv++;
	}
	if (*envv == NULL)
		return (NULL); //! nao encontrou
	res = ft_split((*envv + 5), ':');
	if (!res)
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL); //!erro de malloc
	return (res);
}
