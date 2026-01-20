/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:23:27 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/19 21:48:13 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "error_handling.h"

int			needs_expand(char *delimiter, char **clean_delimiter, int *quote);
static int	get_clean_delimiter(char *delimiter, char **clean_delimiter);
static int	get_here_doc_content(char **content, char *delimiter);
static char	*get_here_doc_line(void);

int	read_and_expand(char *delimiter, char **content, t_shell *shell)
{
	char	*clean_delimiter;
	int		quote;
	int		ret;

	clean_delimiter = NULL;
	quote = 0;
	if (needs_expand(delimiter, &clean_delimiter, &quote) != OK)
		return (ERROR);
	ret = get_here_doc_content(content, clean_delimiter);
	free(clean_delimiter);
	if (ret != OK)
		return (ret);
	if (!quote)
		expand_string(content, shell);
	return (ret);
}

int	needs_expand(char *delimiter, char **clean_delimiter, int *quote)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (ft_isquote(delimiter[i]))
			*quote = 1;
		i++;
	}
	if (*quote)
	{
		if (get_clean_delimiter(delimiter, clean_delimiter) != OK)
			return (ERROR);
	}
	else
	{
		*clean_delimiter = ft_strdup(delimiter);
		if (!*clean_delimiter)
			return (ERROR);
	}
	return (OK);
}

static int	get_clean_delimiter(char *delimiter, char **clean_delimiter)
{
	int	i;
	int	j;

	*clean_delimiter = malloc(ft_strlen(delimiter) + 1);
	if (!*clean_delimiter)
		return (ERROR);
	i = 0;
	j = 0;
	while (delimiter[i])
	{
		if (delimiter[i] != '\'' && delimiter[i] != '"')
			(*clean_delimiter)[j++] = delimiter[i];
		i++;
	}
	(*clean_delimiter)[j] = '\0';
	return (OK);
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
