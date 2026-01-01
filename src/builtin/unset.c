/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 22:31:12 by gustaoli          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/12/31 23:34:58 by gustaoli         ###   ########.fr       */
=======
/*   Updated: 2026/01/01 01:05:26 by gustaoli         ###   ########.fr       */
>>>>>>> Stashed changes
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
	if (!arg || !ft_isalpha(*arg))
		return (ft_printf("unset: invalid parameter name\n"), -1);
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
