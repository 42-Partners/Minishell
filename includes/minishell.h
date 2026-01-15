/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:25:58 by rafaoliv          #+#    #+#             */
/*   Updated: 2026/01/14 21:00:54 by gustaoli         ###   ########.fr       */
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
	int			status;
	char		**envv;
	t_ast_node	*ast;
}	t_shell;

// signal
void	register_sig_handlers(void);
void	signal_handler(int signum);
void	heredoc_handler(int signum);

// variable_expansion
int		expand_cmd(t_cmd_node *cmd, t_shell *shell);
int		expand_string(char **cmd, t_shell *shell);

// here_doc
int		read_all_here_docs(t_ast_node *ast, t_shell *shell);

// env management
int		ft_getenv(char *env, char *envv[], char **result);
int		ft_setenv(char *name, char *value, char **envv[]);

// builtin
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd_node *cmd, t_shell *shell);

// exit
void	exec_exit(t_shell *shell, int status);

#endif