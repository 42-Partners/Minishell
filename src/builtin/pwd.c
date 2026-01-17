/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:22:09 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/17 18:54:03 by devrafaelly      ###   ########.fr       */
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
	ft_getenv("PWD", shell->envv, &pwd);
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
			return (1);
		}
		ft_printf("%s\n", pwd);
		free(pwd);
	}
	return (0);
}
