/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:04:27 by armarake          #+#    #+#             */
/*   Updated: 2025/02/24 13:57:12 by armarake         ###   ########.fr       */
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
	close(pipefd[0]);
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
	close(pipefd[1]);
	execute_command(argv[3], env);
}

int	main(int argc, char *argv[], char *env[])
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5)
		exit_handler("Wrong number of arguments");
	if (pipe(pipefd) == -1)
		exit_handler("Pipe failed");
	pid = fork();
	if (pid == -1)
		exit_handler("Fork failed");
	if (pid == 0)
		execve_child(argv, pipefd, env);
	else
	{
		waitpid(pid, NULL, WNOHANG);
		execve_parent(argv, pipefd, env);
	}
}
