/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:25:58 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/12/16 20:13:23 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "42Partners@minishell: "

# include <signal.h>
# include <unistd.h>
# include <readline/readline.h> 
# include "libft.h"

typedef struct s_env
{
}	t_env;

extern volatile sig_atomic_t	g_signal;

/* signal */
void	register_sig_handlers(void);
void	signal_handler(int signum);

#endif