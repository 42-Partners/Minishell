/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:25:58 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/12/27 18:52:14 by devrafaelly      ###   ########.fr       */
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

// variable_expansion
int	expand_ast(t_ast_node *ast, int *status);

// here_doc
int		read_all_here_docs(t_ast_node *ast);

#endif