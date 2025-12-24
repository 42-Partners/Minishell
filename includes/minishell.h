/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:25:58 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/12/24 13:15:34 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "42Partners@minishell: "

# include "ast.h"

# include <signal.h>

extern volatile sig_atomic_t	g_signal;

// signal
void	register_sig_handlers(void);
void	signal_handler(int signum);
void	heredoc_handler(int signum);

// exec
int		validate_cmd(char *cmd, char **envv);
char	*get_cmd_path(char *cmd, char *envv[]);
void	check_cmds(t_ast_node **ast, char *envv[]);
int		exec_redirects(t_cmd_node *node);
int		exec_ast(t_ast_node *node, char *envv[]);
int		exec_cmd(t_cmd_node cmd, char *envv[]);

// variable_expansion
void	expand_ast(t_ast_node *ast);

// here_doc
int	read_all_here_docs(t_ast_node *ast);

#endif