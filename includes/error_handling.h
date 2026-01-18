/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 16:12:29 by devrafaelly       #+#    #+#             */
/*   Updated: 2026/01/15 19:25:15 by gustaoli         ###   ########.fr       */
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
	ERROR = -1,
	OK = 0,
	FAIL = 1
}	t_error_type;

#endif