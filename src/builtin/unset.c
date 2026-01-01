/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 22:31:12 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/31 23:34:58 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_unset(char **args, char **envp[], int *status)
{
	char	*arg_expanded;

	while (*args)
	{
		if (validate_arg_name(*args) == -1)
			continue ;
		ft_setenv(arg_expanded, NULL, envp);
		args++;
	}
}

static int	validate_arg_name(char *arg)
{
	while (*arg)
	{
		if (!ft_isalnum(*arg))
		{
			ft_printf("unset: invalid parameter name\n");
			return (-1);
		}
		*arg++;
	}
	return (1);
}
