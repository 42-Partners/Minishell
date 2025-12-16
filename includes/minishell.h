/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:25:58 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/12/15 20:56:45 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "42Partners@minishell: "

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include "libft.h"

typedef struct s_env
{
}	t_env;

extern volatile sig_atomic_t	g_signal;

/* signal */
void	register_sig_handlers(void);
void	signal_handler(int signum);

#endif