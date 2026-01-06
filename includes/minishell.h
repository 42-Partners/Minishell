/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:25:58 by rafaoliv          #+#    #+#             */
/*   Updated: 2026/01/06 19:25:05 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "42Partners@minishell: "

# include "ast.h"

# include <signal.h>

extern volatile sig_atomic_t	g_signal;

typedef struct s_shell
{
	int		status;
	char	**envv;
}	t_shell;

// signal
void	register_sig_handlers(void);
void	signal_handler(int signum);
void	heredoc_handler(int signum);

// variable_expansion
int		expand_cmd(t_cmd_node *cmd, t_shell *shell);
int		expand_string(char **cmd, t_shell *shell);
char	*strjoin_free(char *s1, char *s2);

// here_doc
int		read_all_here_docs(t_ast_node *ast, t_shell *shell);

// env management
char	*ft_getenv(char *env, char *envv[]);
int		ft_setenv(char *name, char *value, char **envv[]);

#endif