/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:25:58 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/12/22 12:06:39 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "42Partners@minishell: "

# include <signal.h>
# include "ast.h"

extern volatile sig_atomic_t	g_signal;

typedef struct s_env
{
}	t_env;

// signal
void	register_sig_handlers(void);

// exec
int		validate_cmd(char *cmd, char **envv);
char	*get_path(char *cmd, char *envv[]);
void	check_cmds(t_ast_node **ast, char *envv[]);

#endif