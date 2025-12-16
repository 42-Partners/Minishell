/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 22:14:41 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/15 23:56:53 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef struct s_ast_node	t_ast_node;

typedef enum e_node_type
{
	CMD,
	LOGICAL,
	PIPE,
	HERE_DOC
}	t_node_type;

typedef enum e_redirect_type
{
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND
}	t_redirect_type;

typedef enum e_logical_type
{
	AND,
	OR
}	t_logical_type;

typedef struct s_redirect
{
	int				fd;
	char			*file_name;
	t_redirect_type	type;
}	t_redirect;

typedef struct s_cmd_node
{
	char		*cmd;
	char		**args;
	int			redirect_count;
	t_redirect	**redirects;
}	t_cmd_node;

typedef struct s_here_doc_node
{
	char			*delimiter;
	char			*tmp_file;
	t_ast_node		*child;
}	t_here_doc_node;

typedef struct s_pipe_node
{
	t_ast_node	*right;
	t_ast_node	*left;
}	t_pipe_node;

typedef struct s_logical_node
{
	t_logical_type	type;
	t_ast_node		*right;
	t_ast_node		*left;
}	t_logical_node;

typedef struct s_ast_node
{
	t_node_type	type;
	union		u_node
	{
		t_cmd_node		cmd_node;
		t_pipe_node		pipe_node;
		t_logical_node	logical_node;
		t_here_doc_node	here_doc_node;
	}			t_node;
}	t_ast_node;

#endif
