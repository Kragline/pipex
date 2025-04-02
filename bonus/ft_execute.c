/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:34:50 by armarake          #+#    #+#             */
/*   Updated: 2025/04/02 21:38:15 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	execute_script(char **s_cmnd, char **env)
{
	if (access(s_cmnd[0], F_OK) == -1)
		execution_error(s_cmnd, "no such file or directory");
	if (access(s_cmnd[0], X_OK) == -1)
		execution_error(s_cmnd, "permission denied");
	if (execve(s_cmnd[0], s_cmnd, env) == -1)
	{
		ft_free_tab(s_cmnd);
		exit(1);
	}
}

void	execute_command(char *arg, char *env[])
{
	char	**s_cmnd;
	char	*path_to_cmnd;

	empty_command(arg);
	s_cmnd = ft_split(arg, ' ');
	if (!s_cmnd || !*s_cmnd)
	{
		ft_free_tab(s_cmnd);
		exit(1);
	}
	if (ft_strchr(s_cmnd[0], '/'))
		execute_script(s_cmnd, env);
	else
	{
		path_to_cmnd = get_full_path(s_cmnd[0], env);
		if (execve(path_to_cmnd, s_cmnd, env) == -1)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			ft_putendl_fd(s_cmnd[0], 2);
			ft_free_tab(s_cmnd);
			free(path_to_cmnd);
			exit(1);
		}
	}
}

void	child_process(char *arg, int *pipefd, char *env[])
{
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	close(pipefd[1]);
	execute_command(arg, env);
}

void	parent_process(int *pipefd)
{
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	close(pipefd[1]);
}
