/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:51:10 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/16 18:41:28 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ast.h"

int		validate_cmd(t_cmd_node *cmd, t_shell *shell);
int		get_cmd_path(char **exec, char *cmd, char *envv[]);
int		check_cmds(t_ast_node **ast, t_shell *shell);
int		exec_redirects(t_cmd_node *node);
int		exec_ast(t_ast_node *node, t_shell *shell, int pipe);
int		exec_cmd(t_cmd_node *cmd, t_shell *shell, int pipe);

#endif