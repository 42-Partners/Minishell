/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:46:37 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/19 18:29:17 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error_handling.h"

int			ft_env(t_shell *shell, char **args);
static int	set_var(t_shell *shell, char *args);
static int	is_valid_var_name(char *arg);
static void	cleanup(char *name, char *value);

int	ft_export(t_shell *shell, char **args)
{
	int	i;

	shell->status = 0;
	if (!args[1])
		return (ft_env(shell, args));
	if (args[1][0] == '-')
	{
		shell->status = 1;
		ft_fprintf(2, "export: %s: invalid option\n", args[1]);
		return (FAIL);
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
			shell->status = 1;
		else if (set_var(shell, args[i]) != OK)
		{
			shell->status = 1;
			return (ERROR);
		}
		i++;
	}
	return (OK);
}

static int	set_var(t_shell *shell, char *args)
{
	char	*assign;
	char	*name;
	char	*value;

	assign = ft_strchr(args, '=');
	if (!assign)
	{
		if (ft_setenv(args, "", &shell->envp) != OK)
			return (ERROR);
		return (OK);
	}
	name = ft_substr(args, 0, assign - args);
	if (!name)
		return (ERROR);
	value = ft_strdup(assign + 1);
	if (!value)
		return (free(name), ERROR);
	if (ft_setenv(name, value, &shell->envp) != OK)
	{
		cleanup(name, value);
		return (ERROR);
	}
	cleanup(name, value);
	return (OK);
}

static int	is_valid_var_name(char *arg)
{
	int	i;

	if (!arg || !*arg)
	{
		ft_fprintf(2, "export: not a valid identifier\n");
		return (0);
	}
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_fprintf(2, "export: %s: not a valid identifier\n", arg);
		return (0);
	}
	i = 1;
	while (arg[i])
	{
		if (arg[i] == '=')
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_fprintf(2, "export: %s: not a valid identifier\n", arg);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	cleanup(char *name, char *value)
{
	free(name);
	free(value);
}
