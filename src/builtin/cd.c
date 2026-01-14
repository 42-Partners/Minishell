/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 17:55:26 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/14 15:40:48 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error_handling.h"

#include <stdio.h>

static int	get_cd(t_shell *shell, char **argv, char **cd);
static int	change_directory(char **argv, char *cd);

int	ft_cd(t_shell *shell, char **argv)
{
	char	*cd;
	char	*pwd;
	char	*oldpwd;

	if (*(++argv) && *(argv + 1))
		return (ft_printf("cd: too many arguments\n"), 1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("cd"), FAIL);
	cd = NULL;
	if (get_cd(shell, argv, &cd) != OK)
		return (ERROR);
	change_directory(argv, cd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("cd"), FAIL);
	if (ft_setenv("OLDPWD", oldpwd, &shell->envv) != OK)
		return (ERROR);
	if (ft_setenv("PWD", pwd, &shell->envv) != OK)
		return (ERROR);
	free(oldpwd);
	free(pwd);
	return (OK);
}

static int	get_cd(t_shell *shell, char **argv, char **cd)
{
	if (!*argv || ft_strcmp(*argv, "~") == 0)
	{
		if (ft_getenv("HOME", shell->envv, cd) != OK)
			return (ERROR);
		if (!*cd)
		{
			ft_putstr_fd("Error: cd: HOME not set\n", 2);
			shell->status = 1;
			return (FAIL);
		}
	}
	else if (ft_strcmp(*argv, "-") == 0)
	{
		if (ft_getenv("OLDPWD", shell->envv, cd) != OK)
			return (ERROR);
		if (!*cd)
		{
			ft_putstr_fd("Error: cd: OLDPWD not set\n", 2);
			shell->status = 1;
			return (FAIL);
		}
		ft_printf("%s\n", *cd);
	}
	return (OK);
}

static int	change_directory(char **argv, char *cd)
{
	if (cd)
	{
		if (chdir(cd) < 0)
		{
			free(cd);
			return (perror("Error: cd"), FAIL);
		}
		free(cd);		
	}
	else
	{
		if (chdir(*argv) < 0)
			return (perror("Error: cd"), FAIL);
	}
	return (OK);
}
