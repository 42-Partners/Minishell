/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:16:20 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/30 08:36:57 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_echo(char **args, char *envp[])
{
	int	i;
	int	endline;

	i = 0;
	endline = 1;
	while (args[++i])
	{
		if (ft_strcmp(args[i], "-n") == 0)
			endline = 0;
		else
			break ;
	}
	while (args[i])
		ft_putstr_fd(args[i++], STDOUT_FILENO);
	if (endline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	execve("/usr/bin/true", (char *[]){NULL}, envp);
}
