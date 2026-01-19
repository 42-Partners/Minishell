/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:22:09 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/19 02:11:36 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error_handling.h"

#include <stdio.h>

int	ft_pwd(t_shell *shell, char **args)
{
	char	*pwd;

	(void)args;
	pwd = NULL;
	shell->status = 1;
	ft_getenv("PWD", shell->envp, &pwd);
	if (pwd)
	{
		ft_printf("%s\n", pwd);
		free(pwd);
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			perror("pwd");
			return (FAIL);
		}
		ft_printf("%s\n", pwd);
		free(pwd);
	}
	shell->status = 0;
	return (OK);
}
