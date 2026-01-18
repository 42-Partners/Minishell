/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:56:21 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/14 21:02:08 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>

void	exec_exit(t_shell *shell, int status)
{
	if (shell->ast)
		free_ast(&shell->ast);
	ft_free_arr(&shell->envv);
	exit(status);
}
