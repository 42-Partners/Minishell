/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 10:22:49 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/24 10:22:49 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "ast.h"
#include "error_handling.h"

#include <fcntl.h>

#define _GNU_SOURCE

int			read_and_expand(char **delimiter, char **content, t_shell *shell);
int			write_here_doc(int *fd, char *content);
int			needs_expand(char **delimiter);
static int	read_here_docs(t_cmd_node cmd, t_shell *shell);

int	read_all_here_docs(t_ast_node *ast, t_shell *shell)
{
	int	ret;

	ret = OK;
	if (ast->type == CMD)
		return (read_here_docs(ast->t_node.cmd_node, shell));
	else if (ast->type == LOGICAL)
	{
		ret = read_all_here_docs(ast->t_node.logical_node.left, shell);
		if (ret != OK)
			return (ret);
		return (read_all_here_docs(ast->t_node.logical_node.right, shell));
	}
	else if (ast->type == PIPE)
	{
		ret = read_all_here_docs(ast->t_node.pipe_node.left, shell);
		if (ret != OK)
			return (ret);
		return (read_all_here_docs(ast->t_node.pipe_node.right, shell));
	}
	return (OK);
}

static int	read_here_docs(t_cmd_node cmd, t_shell *shell)
{
	char	*content;
	int		ret;
	int		i;

	ret = OK;
	i = -1;
	while (++i < cmd.redirect_count)
	{
		if (cmd.redirects[i]->type != HERE_DOC)
			continue ;
		content = ft_strdup("");
		if (!content)
			return (ft_fprintf(2, ERR_MALLOC), ERROR);
		ret = read_and_expand(&(cmd.redirects[i]->file_name), &content, shell);
		if (ret != OK)
			return (ret);
		ret = write_here_doc(&(cmd.redirects[i]->fd), content);
		free(content);
		if (ret != OK)
			return (ret);
	}
	return (OK);
}
