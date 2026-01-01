/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustaoli <gustaoli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:33:02 by gustaoli          #+#    #+#             */
/*   Updated: 2025/12/23 12:33:02 by gustaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec.h"
#include "libft.h"

#include <unistd.h>
#include <sys/wait.h>

static int	redirect_without_cmd(t_cmd_node *cmd);
static void	exec_and_redirect(char *exec, t_cmd_node *cmd, char *envv[]);
static int	wait_child(int pid);

int	exec_cmd(t_cmd_node cmd, char *envv[])
{
	pid_t	pid;
	char	*exec;

	if (!cmd.cmd) //! precisa verificar o malloc em consume_token pra isso ser safe
		return (redirect_without_cmd(&cmd));
	exec = get_cmd_path(cmd.cmd, envv);
	if (!exec)
		return (ERROR);
	pid = fork();
	if (pid == -1)
		return (perror("Error"), ERROR);
	if (pid == 0)
		exec_and_redirect(exec, &cmd, envv);
	return (free(exec), wait_child(pid));
}

static void	exec_and_redirect(char *exec, t_cmd_node *cmd, char *envv[])
{
	int	i;

	if (exec_redirects(cmd) == ERROR)
		exit(1); //! isso encerra o shell? nesse caso precisamos encerrar
	i = 3;
	while (i < 1024)
		close(i++);
	execve(exec, cmd->args, envv); //! adicionar leitura de erro aqui, permissao negada, comando nao encontrado... 
	exit(1);
}

static int	redirect_without_cmd(t_cmd_node *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(1);
	}
	if (pid == 0)
	{
		if (exec_redirects(cmd) == ERROR)
			exit(1);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (0); // isso aqui vai ser guardado no status, nao sei se mexo porque OK é 1.
}

static int	wait_child(int pid)
{
	int	ret;

	waitpid(pid, &ret, 0);
	while (wait(NULL) > 0)
		;
	return (ret >> 8);
}
