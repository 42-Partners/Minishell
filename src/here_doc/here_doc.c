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

#define _GNU_SOURCE

#include "minishell.h"
#include "libft.h"
#include "ast.h"

#include <fcntl.h>

static int	read_here_docs(t_cmd_node cmd);
static char	*get_here_doc_content(char *delimiter);
static char	*get_here_doc_line(void);

int	read_all_here_docs(t_ast_node *ast)
{
	if (ast->type == CMD)
		return (read_here_docs(ast->t_node.cmd_node));
	else if (ast->type == LOGICAL)
	{
		if (read_all_here_docs(ast->t_node.logical_node.left) != -1)
			return (read_all_here_docs(ast->t_node.logical_node.right));
	}
	else if (ast->type == PIPE)
	{
		if (read_all_here_docs(ast->t_node.pipe_node.left) != -1)
			return (read_all_here_docs(ast->t_node.pipe_node.right));
	}
	return (-1);
}

static int	read_here_docs(t_cmd_node cmd)
{
	int		i;
	char	*content;
	int		aux[2];

	i = -1;
	while (++i < cmd.redirect_count)
	{
		if (cmd.redirects[i]->type != HERE_DOC)
			continue ;
		content = get_here_doc_content(cmd.redirects[i]->file_name);
		if (!content)
			return (
				ft_printf("An error ocurred while reading here_doc :(\n"), -1);
		if (pipe(aux) == -1)
			return (free(content), -1);
		cmd.redirects[i]->fd = aux[0];
		write(aux[1], content, ft_strlen(content));
		close (aux[1]);
		free(content);
	}
	return (1);
}

static char	*get_here_doc_content(char *delimiter)
{
	char	*content;
	char	*buff;
	char	*aux;
	int		delimiter_size;

	signal(SIGINT, heredoc_handler);
	delimiter_size = ft_strlen(delimiter);
	content = ft_strdup("");
	while (content && g_signal == 0)
	{
		buff = get_here_doc_line();
		if (!buff)
			break ;
		if (ft_strncmp(buff, delimiter, delimiter_size) == 0
			&& (buff[delimiter_size] == '\n' || buff[delimiter_size] == '\0'))
			break ;
		aux = ft_strjoin(content, buff);
		free(content);
		content = aux;
		free(buff);
	}
	signal(SIGINT, signal_handler);
	if (g_signal != 0)
		return (free(content), NULL);
	return (free(buff), content);
}

static char	*get_here_doc_line(void)
{
	char	*buf;

	write(1, "> ", 2);
	buf = get_next_line(0);
	if (!buf)
		write(1, "\n", 1);
	return (buf);
}
