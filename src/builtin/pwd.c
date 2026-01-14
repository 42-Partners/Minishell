/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:22:09 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/14 17:35:20 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error_handling.h"

#include <stdio.h>

int	ft_pwd(t_shell *shell, char **args)
{
	char	*pwd;

	shell->status = 1;
	if (*(args + 1))
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (FAIL);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("pwd"), FAIL);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	shell->status = 0;
	return (OK);
}
