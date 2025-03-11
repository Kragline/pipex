/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:04:27 by armarake          #+#    #+#             */
/*   Updated: 2025/03/12 01:11:38 by armarake         ###   ########.fr       */
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
		ft_free_tab(s_cmnd);
		free(path_to_cmnd);
		exit(1);
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

void	do_pipe(char *arg, char *env[])
{
	int		pipefd[2];
	pid_t	pid;

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
		child_process(arg, pipefd, env);
	parent_process(pipefd);
}

int	main(int argc, char *argv[], char *env[])
{
	int	i;
	int	infile;
	int	outfile;

	if (argc < 5)
	{
		ft_putendl_fd("Wrong number of arguments", 2);
		exit(1);
	}
	infile = open_infile(argv[1]);
	if (infile == -1)
		exit(1);
	outfile = open_outfile(argv[argc - 1]);
	if (outfile == -1)
		exit(1);
	i = 2;
	dup2(infile, 0);
	while (i < argc - 2)
	{
		do_pipe(argv[i], env);
		i++;
	}
	dup2(outfile, 1);
	execute_command(argv[argc - 2], env);
}
