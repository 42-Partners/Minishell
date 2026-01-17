/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 22:31:12 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/17 14:49:14 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ast.h"
#include "error_handling.h"

static int	validate_arg_name(char *arg);
static char	**remove_env_var(t_shell *shell, char *arg);
static char	**get_new_env(char **env, char **updated_env, char *arg);

int	ft_unset(t_shell *shell, char **args)
{
	char	**new_envv;
	int		status;
	int		i;

	status = 0;
	i = 0;
	while (args[++i])
	{
		if (validate_arg_name(args[i]) == 1)
			status = 1;
		else
		{
			new_envv = remove_env_var(shell, args[i]);
			if (!new_envv)
				return (-1);
			shell->envv = new_envv;
		}
	}
	return (status);
}

static int	validate_arg_name(char *arg)
{
	char	*str;

	if (!arg || !*arg)
	{
		ft_fprintf(2, "unset: not a valid identifier\n");
		return (1);
	}
	str = arg;
	if (str && (ft_isalpha(*str) || *str == '_'))
	{
		while (*str && (ft_isalnum(*str) || *str == '_'))
			str++;
	}
	if (*str)
	{
		ft_fprintf(2, "unset: %s: not a valid identifier\n", arg);
		return (1);
	}
	else
		return (0);
}

static char	**remove_env_var(t_shell *shell, char *arg)
{
	char	**env;
	char	**updated_env;
	int		i;

	env = shell->envv;
	i = 0;
	while (env[i])
		i++;
	updated_env = malloc((i + 1) * sizeof(char *));
	if (!updated_env)
		return (ft_fprintf(2, ERR_MALLOC), NULL);
	updated_env = get_new_env(env, updated_env, arg);
	if (!updated_env)
		return (NULL);
	free_array((void ***)&shell->envv);
	return (updated_env);
}

static char	**get_new_env(char **env, char **updated_env, char *arg)
{
	int		arg_len;
	int		i;
	int		j;

	arg_len = 0;
	while (arg[arg_len] && arg[arg_len] != '=')
		arg_len++;
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], arg, arg_len) != 0
			|| env[i][arg_len] != '=')
		{
			updated_env[j] = ft_strdup(env[i]);
			if (!updated_env[j++])
			{
				free_array((void ***)&updated_env);
				return (ft_fprintf(2, ERR_MALLOC), NULL);
			}
		}
		i++;
	}
	updated_env[j] = NULL;
	return (updated_env);
}
