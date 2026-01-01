/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 01:08:23 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/01 01:23:25 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_env(char **args, char *envp[])
{
	if (*args)
		return (ft_printf("env: bad usage :(\n"), -1);
	while (*envp)
	{
		ft_putendl_fd(*envp, STDOUT_FILENO);
		envp++;
	}
	execve("/usr/bin/true", (char *[]){NULL}, envp);
	return (1);
}
