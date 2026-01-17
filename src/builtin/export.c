/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:46:37 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/17 14:22:37 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error_handling.h"

static int	set_var(t_shell *shell, char *args);
static int	is_valid_var_name(char *arg);
static void	cleanup(char *name, char *value);

int	ft_export(t_shell *shell, char **args)
{
	int	status;

	status = 0;
	args++;
	if (!*args)
		return (status);
	if ((*args)[0] == '-')
	{
		status = 1;
		ft_fprintf(2, "export: %s: invalid option\n", *args);
		return (status);
	}
	while (*args)
	{
		if (!is_valid_var_name(*args))
			status = 1;
		else if (set_var(shell, *args) != OK)
			return (-1);
		args++;
	}
	return (status);
}

static int	set_var(t_shell *shell, char *args)
{
	char	*assign;
	char	*name;
	char	*value;

	assign = ft_strchr(args, '=');
	if (!assign)
	{
		if (ft_setenv(args, "", &shell->envv) != OK)
			return (ERROR);
		return (OK);
	}
	name = ft_substr(args, 0, assign - args);
	if (!name)
		return (ERROR);
	value = ft_strdup(assign + 1);
	if (!value)
		return (free(name), ERROR);
	if (ft_setenv(name, value, &shell->envv) != OK)
	{
		cleanup(name, value);
		return (ERROR);
	}
	cleanup(name, value);
	return (OK);
}

static int	is_valid_var_name(char *arg)
{
	if (!arg || !*arg)
	{
		ft_fprintf(2, "export: not a valid identifier\n");
		return (0);
	}
	if (!ft_isalpha (*arg) && *arg != '_')
	{
		ft_fprintf(2, "export: %s: not a valid identifier\n", arg);
		return (0);
	}
	while (*(++arg))
	{
		if (*arg == '=')
			break ;
		if (!ft_isalnum(*arg) && *arg != '_')
		{
			ft_fprintf(2, "export: %s: not a valid identifier\n", arg);
			return (0);
		}
	}
	return (1);
}

static void	cleanup(char *name, char *value)
{
	free(name);
	free(value);
}
