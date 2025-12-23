/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:25:58 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/12/23 04:34:52 by devrafaelly      ###   ########.fr       */
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

// exec
int		validate_cmd(char *cmd, char **envv);
char	*get_cmd_path(char *cmd, char *envv[]);
void	check_cmds(t_ast_node **ast, char *envv[]);

// variable_expansion
void	expand_ast(t_ast_node *ast);

#endif