/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 16:12:29 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/05 18:38:32 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H

# define ERR_SYNTAX "Error: syntax error\n"
# define ERR_UNCLOSED_QUOTE "Error: syntax error: unclosed quote\n"
# define ERR_CMD_NOT_FOUND "Error: command not found: "
# define ERR_MALLOC "Error: malloc error\n"
# define ERR_INVALID_CHAR "Error: unsupported character\n"
# define ERR_INVALID_REDIRECT "Error: invalid redirection\n"
# define ERR_HEREDOC "Error: here-doc error\n"  

typedef enum e_error_type
{
	ERROR = -1, // erro grave, encerra minishell
	OK = 0, // erro leve, retorna novo prompt
	FAIL = 1 // tudo certo
}	t_error_type;

#endif