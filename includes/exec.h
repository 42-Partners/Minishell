/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:51:10 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/06 17:49:59 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ast.h"

int		validate_cmd(char *cmd, char **envv);
int		get_cmd_path(char **exec, char *cmd, char *envv[]);
int		check_cmds(t_ast_node **ast, char *envv[]);
int		exec_redirects(t_cmd_node *node);
int		exec_ast(t_ast_node *node, t_shell *shell);
int		exec_cmd(t_cmd_node *cmd, t_shell *shell);

#endif