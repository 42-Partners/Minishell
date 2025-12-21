/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 22:54:01 by devrafaelly       #+#    #+#             */
/*   Updated: 2025/12/21 03:21:17 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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

t_token	*tokenize(char *input);
t_token	*new_token(char *value, t_token_type type);
int		token_add_back(t_token **token, char *value, t_token_type type);
void	free_token(t_token **token);

/* Debug (remove on project delivery) */
void	print_tokens(t_token *tokens, char *custom);
void	debug_flag(char *print_mgs);

#endif