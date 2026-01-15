/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:46:37 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/14 20:15:26 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error_handling.h"

static int	set_var(t_shell *shell, char **args);
static int	is_valid_var_name(char *arg);
static void	cleanup(char *name, char *value);

int	ft_export(t_shell *shell, char **args)
{
	shell->status = 1;
	args++;
	if (!*args)
		return (OK);
	if ((*args)[0] == '-')
		return (ft_putstr_fd("export: invalid option\n", 2), FAIL);
	if (!ft_isalpha((*args)[0]) && (*args)[0] != '_')
		return (ft_putstr_fd("export: not a valid identifier\n", 2), FAIL);
	while (*args)
	{
		if (!is_valid_var_name(*args))
			return (ft_putstr_fd("export: invalid name\n", 2), FAIL);
		if (set_var(shell, args) != OK)
			return (ERROR);
		args++;
	}
	shell->status = 0;
	return (OK);
}

static int	set_var(t_shell *shell, char **args)
{
	char	*assign;
	char	*name;
	char	*value;

	assign = ft_strchr(*args, '=');
	if (!assign)
	{
		ft_setenv(*args, NULL, &shell->envv);
		args++;
		return (OK);
	}
	name = ft_substr(*args, 0, assign - *args);
	if (!name)
		return (ERROR);
	value = ft_strdup(assign + 1);
	if (!value)
		return (ERROR);
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
	while (*arg)
	{
		if (*arg == '=')
			break ;
		if (!ft_isalnum(*arg) && *arg != '_')
			return (0);
		arg++;
	}
	return (1);
}

static void	cleanup(char *name, char *value)
{
	free(name);
	free(value);
}
