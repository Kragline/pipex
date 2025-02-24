/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:04:27 by armarake          #+#    #+#             */
/*   Updated: 2025/02/24 18:43:33 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	execute_command(char *arg, char *env[])
{
	char	**s_cmnd;
	char	*path_to_cmnd;

	s_cmnd = ft_split(arg, ' ');
	path_to_cmnd = get_full_path(s_cmnd[0], env);
	if (execve(path_to_cmnd, s_cmnd, env) == -1)
	{
		free(path_to_cmnd);
		ft_free_tab(s_cmnd);
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmnd[0], 2);
		exit(1);
	}
}

void	execve_child(char *argv[], int *pipefd, char *env[])
{
	int	infile;

	infile = open_infile(argv[1]);
	if (infile == -1)
		exit(1);
	dup2(infile, 0);
	dup2(pipefd[1], 1);
	close(infile);
	close(pipefd[0]);
	close(pipefd[1]);
	execute_command(argv[2], env);
}

void	execve_parent(char *argv[], int *pipefd, char *env[])
{
	int	outfile;

	outfile = open_outfile(argv[4]);
	if (outfile == -1)
		exit(1);
	dup2(outfile, 1);
	dup2(pipefd[0], 0);
	close(outfile);
	close(pipefd[0]);
	close(pipefd[1]);
	execute_command(argv[3], env);
}

int	main(int argc, char *argv[], char *env[])
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putendl_fd("Wrong number of arguments", 2);
		exit(1);
	}
	if (pipe(pipefd) == -1)
	{
		ft_putendl_fd("Pipe failed", 2);
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("Fork failed", 2);
		exit(1);
	}
	if (pid == 0)
		execve_child(argv, pipefd, env);
	waitpid(pid, NULL, 0);
	execve_parent(argv, pipefd, env);
}
