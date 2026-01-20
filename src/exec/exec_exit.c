/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:56:21 by gustaoli          #+#    #+#             */
/*   Updated: 2026/01/20 16:13:26 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>

void	exec_exit(t_shell *shell, int status)
{
	get_next_line(-1);
	if (shell->ast)
		free_ast(&shell->ast);
	ft_free_arr(&shell->envp);
	exit(status);
}
