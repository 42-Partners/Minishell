/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:22:09 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/31 21:35:54 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_pwd(char **args, char *envp[], int *status)
{
	char	*pwd;

	if (!args || !*args)
		execve("/usr/bin/false", (char *[]){NULL}, envp);
	if (*(args + 1))
	{
		ft_putendl_fd("pwd: too many arguments :(", STDOUT_FILENO);
		execve("/usr/bin/false", (char *[]){NULL}, envp);
	}
	pwd = ft_getenv("PWD", envp);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	execve("/usr/bin/true", (char *[]){NULL}, envp);
}
