/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 22:54:01 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/20 15:41:24 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PIPE,
	TOKEN_WORD,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_OPEN_PARENTESIS,
	TOKEN_CLOSE_PARENTESIS
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

int		tokenize(t_token **token, char **input);
int		token_add_back(t_token **token, char *value, t_token_type type);
t_token	*new_token(char *value, t_token_type type);
void	free_token(t_token **token);
t_token	*divide_left(t_token *token_head, t_token *father);
t_token	*divide_right(t_token *token_head, t_token *father);

#endif