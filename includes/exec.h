/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:51:10 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/27 18:52:05 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ast.h"

int		validate_cmd(char *cmd, char **envv);
char	*get_cmd_path(char *cmd, char *envv[]);
int		check_cmds(t_ast_node **ast, char *envv[]);
int		exec_redirects(t_cmd_node *node);
int		exec_ast(t_ast_node *node, char *envv[], int *status);
int		exec_cmd(t_cmd_node cmd, char *envv[]);

#endif