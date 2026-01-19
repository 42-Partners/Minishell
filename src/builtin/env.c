/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 01:08:23 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/19 18:34:04 by rafaoliv         ###   ########.fr       */
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
	while (shell->envp[i])
	{
		ft_fprintf(1, "%s\n", (shell->envp)[i]);
		i++;
	}
	shell->status = 0;
	return (OK);
}
