/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:46:37 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/31 22:14:12 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_export(char **args, char **envp[], int *status)
{
	char	*expanded_arg;
	char	*assign;

	while (*(++args))
	{
		expanded_arg = NULL; //expand arg
		assign = ft_strchr(expanded_arg, '=');
		if (!assign)
			continue ;
		expanded_arg[assign - expanded_arg] = '\0';
		ft_setenv(expanded_arg, &(expanded_arg[1 + assign - expanded_arg]));
		free(expanded_arg);
	}
	return (0);
}
