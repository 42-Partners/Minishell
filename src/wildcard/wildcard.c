/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 04:14:47 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/19 06:17:31 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "libft.h"
#include "error_handling.h"

#include <dirent.h>

static int	replace_wildcard(t_cmd_node **cmd, int wildcard_index, char *pwd);
static int	count_matches(char *pwd);
static char	**insert_matches(char **old_args,
				int star_idx, char *pwd, int count);
static int	ft_arr_len(char **arr);

int	handle_wildcard(t_cmd_node **cmd, t_shell *shell)
{
	int		i;
	char	*pwd;

	if (!(*cmd)->args)
		return (OK);
	i = 0;
	if (ft_getenv("PWD", shell->envp, &pwd) != OK)
		return (ERROR);
	while ((*cmd)->args[++i])
	{
		if ((*cmd)->args[i][0] == '*' && (*cmd)->args[i][1] == 0)
		{
			if (replace_wildcard(cmd, i, pwd) != OK)
				return (free(pwd), ERROR);
			i = 1;
		}
	}
	return (free(pwd), OK);
}

static int	count_matches(char *pwd)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(pwd);
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

static char	**insert_matches(char **old_args,
	int star_idx, char *pwd, int count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**new_args;
	int				i;
	int				k;

	new_args = ft_calloc(ft_arr_len(old_args) + count, sizeof(char *));
	if (!new_args)
		return (NULL);
	i = -1;
	k = 0;
	while (++i < star_idx)
		new_args[k++] = ft_strdup(old_args[i]);
	dir = opendir(pwd);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			new_args[k++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	while (old_args[++i])
		new_args[k++] = ft_strdup(old_args[i]);
	return (new_args);
}

static int	replace_wildcard(t_cmd_node **cmd, int wildcard_index, char *pwd)
{
	int		match_count;
	char	**new_args;

	match_count = count_matches(pwd);
	if (match_count == 0)
		return (OK);
	new_args = insert_matches((*cmd)->args, wildcard_index, pwd, match_count);
	if (!new_args)
		return (ERROR);
	ft_free_arr(&(*cmd)->args);
	(*cmd)->args = new_args;
	return (OK);
}

static int	ft_arr_len(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
