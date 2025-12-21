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

extern volatile sig_atomic_t	g_signal;

typedef struct s_env
{
}	t_env;

// signal
void	register_sig_handlers(void);

#endif