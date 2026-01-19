/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:23:27 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/15 22:24:12 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "error_handling.h"

static int	get_here_doc_content(char **content, char *delimiter);
static char	*get_here_doc_line(void);

int	write_here_doc(int *fd, char *content)
{
	int		aux[2];

	if (pipe(aux) == -1)
		return (FAIL);
	write(aux[1], content, ft_strlen(content));
	close (aux[1]);
	*fd = aux[0];
	return (OK);
}

int	needs_expand(char **delimiter)
{
	int	quote;
	int	i;
	int	j;

	quote = 0;
	i = 0;
	while ((*delimiter)[i])
	{
		if (ft_isquote((*delimiter)[i]))
			quote = 1;
		i++;
	}
	i = 0;
	j = 0;
	if (quote)
	{
		while ((*delimiter)[i])
		{
			if ((*delimiter)[i] != '\'')
				(*delimiter)[j++] = (*delimiter)[i];
			i++;
		}
		(*delimiter)[j] = '\0';
	}
	return (quote);
}

int	read_and_expand(char **delimiter, char **content, t_shell *shell)
{
	int	quote;
	int	ret;

	quote = 0;
	quote = needs_expand(delimiter);
	ret = get_here_doc_content(content, *delimiter);
	if (ret != OK)
		return (ret);
	if (!quote)
		expand_string(content, shell);
	return (ret);
}

static int	get_here_doc_content(char **content, char *delimiter)
{
	char	*buff;
	int		delimiter_size;

	signal(SIGINT, heredoc_handler);
	delimiter_size = ft_strlen(delimiter);
	while (g_signal == 0)
	{
		buff = get_here_doc_line();
		if (!buff)
			break ;
		if (ft_strncmp(buff, delimiter, delimiter_size) == 0
			&& (buff[delimiter_size] == '\n' || buff[delimiter_size] == '\0'))
		{
			free(buff);
			break ;
		}
		*content = ft_strjoin_free(*content, buff);
		free(buff);
		if (!*content)
			return (ERROR);
	}
	signal(SIGINT, signal_handler);
	if (g_signal != 0)
		return (free(*content), FAIL);
	return (get_next_line(-1), OK);
}

static char	*get_here_doc_line(void)
{
	write(1, "> ", 2);
	return (get_next_line(0));
}
