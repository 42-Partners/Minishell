/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 22:14:41 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/20 01:43:58 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"

typedef struct s_ast_node	t_ast_node;

typedef enum e_node_type
{
	CMD,
	LOGICAL,
	PIPE
}	t_node_type;

typedef enum e_redirect_type
{
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HERE_DOC
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
	}			t_node;
}	t_ast_node;

typedef struct s_shell_env
{
	int		*status;
	char	***envv;
}	t_shell_env;

void		get_redirects(t_cmd_node **node, t_token *tokens);
t_node_type	detect_next_node_type(t_token *tokens);
t_ast_node	*build_ast(t_token *tokens);
t_cmd_node	*consume_tokens(t_token *tokens);
t_ast_node	*handle_low_level(t_token *tokens);
t_ast_node	*handle_high_level(t_node_type type,
				t_token *right_tokens, t_token *left_tokens);
void		validate_ast(t_ast_node **ast);
void		free_ast(t_ast_node **ast);

/*DEBUG*/
void		print_ast(t_ast_node *ast);
void		debug_flag(char *print_mgs);

#endif
