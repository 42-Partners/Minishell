/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 17:55:26 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/17 19:41:12 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error_handling.h"

#include <stdio.h>

static char	*get_cd(t_shell *shell, char **argv);
static void	update_envv(t_shell *shell, char *target, char *oldpwd);
static void	cleanup(char *pwd, char *oldpwd);

int	ft_cd(t_shell *shell, char **argv)
{
	char	*target;
	char	*oldpwd;

	if (argv[1] && argv[2])
		return (ft_fprintf(2, "cd: too many arguments\n"), 2);
	target = get_cd(shell, argv);
	if (!target)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_getenv("PWD", shell->envv, &oldpwd);
		if (!oldpwd)
			return (free(target), 1);
	}
	if (chdir(target) < 0)
	{
		perror("cd");
		return (cleanup(target, oldpwd), 1);
	}
	update_envv(shell, target, oldpwd);
	cleanup(target, oldpwd);
	return (0);
}

static char	*get_cd(t_shell *shell, char **argv)
{
	char	*pwd;

	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
	{
		if (ft_getenv("HOME", shell->envv, &pwd) != OK)
			return (NULL);
		if (!*pwd)
			return (ft_fprintf(2, "cd: HOME not set\n"), NULL);
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		if (ft_getenv("OLDPWD", shell->envv, &pwd) != OK)
			return (NULL);
		if (!*pwd)
			return (ft_fprintf(2, "cd: OLDPWD not set\n"), NULL);
		ft_printf("%s\n", pwd);
	}
	else
		pwd = ft_strdup(argv[1]);
	return (pwd);
}

static void	update_envv(t_shell *shell, char *target, char *oldpwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
		ft_setenv("PWD", pwd, &shell->envv);
	else
		ft_setenv("PWD", target, &shell->envv);
	ft_setenv("OLDPWD", oldpwd, &shell->envv);
	free(pwd);
}

static void	cleanup(char *pwd, char *oldpwd)
{
	free(oldpwd);
	free(pwd);
}
