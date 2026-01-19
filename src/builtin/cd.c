/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 17:55:26 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/18 17:40:17 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error_handling.h"

#include <stdio.h>

static int	get_cd(t_shell *shell, char **argv, char **pwd);
static int	get_oldpwd(t_shell *shell, char **oldpwd);
static int	update_envv(t_shell *shell, char *target, char *oldpwd);
static void	cleanup(char *pwd, char *oldpwd);

int	ft_cd(t_shell *shell, char **argv)
{
	char	*target;
	char	*oldpwd;
	int		ret;

	shell->status = 1;
	if (argv[1] && argv[2])
		return (ft_fprintf(2, "cd: too many arguments\n"), 2);
	ret = get_cd(shell, argv, &target);
	if (ret != OK)
		return (ret);
	if (get_oldpwd(shell, &oldpwd) != OK)
		return (free(target), ERROR);
	if (chdir(target) < 0)
	{
		perror("cd");
		return (cleanup(target, oldpwd), FAIL);
	}
	if (update_envv(shell, target, oldpwd))
		return (cleanup(target, oldpwd), ERROR);
	cleanup(target, oldpwd);
	shell->status = 0;
	return (OK);
}

static int	get_cd(t_shell *shell, char **argv, char **pwd)
{
	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
	{
		if (ft_getenv("HOME", shell->envv, pwd) != OK)
			return (ERROR);
		if (!pwd)
			return (ft_fprintf(2, "cd: HOME not set\n"), FAIL);
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		if (ft_getenv("OLDPWD", shell->envv, pwd) != OK)
			return (ERROR);
		if (!pwd)
			return (ft_fprintf(2, "cd: OLDPWD not set\n"), FAIL);
		ft_printf("%s\n", pwd);
	}
	else
	{
		*pwd = ft_strdup(argv[1]);
		if (!*pwd)
			return (ERROR);
	}
	return (OK);
}

static int	get_oldpwd(t_shell *shell, char **oldpwd)
{
	*oldpwd = getcwd(NULL, 0);
	if (!*oldpwd)
	{
		if (ft_getenv("PWD", shell->envv, oldpwd) != OK || !*oldpwd)
			return (ERROR);
	}
	return (OK);
}

static int	update_envv(t_shell *shell, char *target, char *oldpwd)
{
	char	*pwd;
	int		ret;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ret = ft_setenv("PWD", pwd, &shell->envv);
		free(pwd);
	}
	else
		ret = ft_setenv("PWD", target, &shell->envv);
	if (ret != OK)
		return (ERROR);
	ft_setenv("OLDPWD", oldpwd, &shell->envv);
	if (ret != OK)
		return (ERROR);
	return (OK);
}

static void	cleanup(char *pwd, char *oldpwd)
{
	free(oldpwd);
	free(pwd);
}
