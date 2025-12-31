/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 17:55:26 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/31 20:18:00 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cd(char **argv, char *envp[], int *status)
{
	int		ret;
	char	*aux;

	if (!argv || *argv)
		return (1);
	if (*(++argv) && *(argv + 1))
		return (ft_printf("cd bad usage! :(\n"), 1);
	ret = -1;
	//expand arg
	aux = NULL;
	if (!*argv)
		aux = ft_getenv("HOME", envp);
	else if (ft_strcmp(*argv, "-") == 0)
		aux = ft_getenv("OLDPWD", envp);
	if (aux)
	{
		ret = chdir(aux);
		free(aux);
	}
	else
		ret = chdir(*argv);
	*status = ret < 0;
	return (ret);
}
