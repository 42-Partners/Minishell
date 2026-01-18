/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 01:08:23 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/18 18:42:14 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error_handling.h"

int	ft_env(t_shell *shell, char **args)
{
	int	i;

	shell->status = 1;
	if (args[1])
	{
		ft_fprintf(2, "env: bad usage\n");
		return (FAIL);
	}
	i = 0;
	while (shell->envv[i])
	{
		ft_fprintf(1, "%s\n", shell->envv[i]);
		i++;
	}
	shell->status = 0;
	return (OK);
}
