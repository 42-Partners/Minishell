/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devrafaelly <devrafaelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:39:45 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/12 16:07:12 by devrafaelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("42Partners@minishell: ");
		if (!input || ft_strcmp(input, "exit") == 0)
		{
			if (input)
				free(input);
			break ;
		}
		if (*input)
			add_history(input);
		free(input);
	}
	return (0);
}
