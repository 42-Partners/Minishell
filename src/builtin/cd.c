/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 17:55:26 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/14 17:02:19 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error_handling.h"

#include <stdio.h>

static int	get_cd(t_shell *shell, char **argv, char **cd);
static int	change_directory(char **argv, char *cd);
static void	cleanup(char *pwd, char *oldpwd);

int	ft_cd(t_shell *shell, char **argv)
{
	char	*cd;
	char	*pwd;
	char	*oldpwd;

	shell->status = 1;
	if (*(++argv) && *(argv + 1))
		return (ft_putstr_fd("cd: too many arguments\n", 2), FAIL);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("cd"), ERROR);
	cd = NULL;
	if (get_cd(shell, argv, &cd) != OK)
		return (ERROR);
	if (change_directory(argv, cd) != OK)
		return (FAIL);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("cd"), FAIL);
	if (ft_setenv("OLDPWD", oldpwd, &shell->envv) != OK)
		return (cleanup(pwd, oldpwd), ERROR);
	if (ft_setenv("PWD", pwd, &shell->envv) != OK)
		return (cleanup(pwd, oldpwd), ERROR);
	cleanup(pwd, oldpwd);
	shell->status = 0;
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

static void	cleanup(char *pwd, char *oldpwd)
{
	free(oldpwd);
	free(pwd);
}
