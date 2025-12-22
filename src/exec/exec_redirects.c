/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:01:26 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/22 15:01:26 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "ast.h"
#include "libft.h"

static int	redirect(t_redirect *red);

int	exec_redirects(t_cmd_node *node)
{
	int	i;

	i = -1;
	if (!node)
		return (-1);
	while (++i < node->redirect_count)
	{
		if (redirect(node->redirects[i]) == -1)
			return (-1);
	}
	return (1);
}

static int	redirect(t_redirect *red)
{
	int	ret;

	if (red->type == REDIRECT_OUT)
		red->fd = open(red->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (red->type == REDIRECT_IN)
		red->fd = open(red->file_name, O_RDONLY);
	else if (red->type == REDIRECT_APPEND)
		red->fd = open(red->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (red->fd < 0)
	{
		ft_printf("%s: No such file or directory :(\n", red->file_name);
		return (-1);
	}
	if (red->type == REDIRECT_IN || red->type == HERE_DOC)
		ret = dup2(red->fd, STDIN_FILENO);
	else
		ret = dup2(red->fd, STDOUT_FILENO);
	close(red->fd);
	return (ret);
}
