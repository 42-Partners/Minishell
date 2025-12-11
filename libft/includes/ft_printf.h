/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:37:51 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/12/10 14:04:08 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int	ft_printf(const char *format, ...);
int	ft_conversion_specifier(char c, va_list ap);
int	ft_print_char(int c);
int	ft_print_str(char *str);
int	ft_print_s_nbr(int n);
int	ft_print_u_nbr(unsigned int n);
int	ft_print_hexa(unsigned int n, char c);
int	ft_print_hexa_long(unsigned long n);
int	ft_print_pointer(void *ptr);

#endif