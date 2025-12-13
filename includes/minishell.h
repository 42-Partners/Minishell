/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:25:58 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/12/13 18:53:38 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
}	t_ast;

typedef struct s_env
{
}	t_env;

t_token	*tokenize(t_token *token, char *input);
t_token	*new_token(char *value, t_token_type type);
void	free_token(t_token **token);
int		token_add_back(t_token **token, char *value, t_token_type type);
int		get_operator(t_token **token, char **input);
int		get_quote(t_token **token, char **input);
int		get_word(t_token **token, char **input);
int		invalid_token(int c);
int		is_operator(int c);
int		is_quote(int c);

#endif