/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:04:27 by armarake          #+#    #+#             */
/*   Updated: 2025/04/02 17:40:59 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

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
		return (ft_putendl_fd("Wrong number of arguments", 2), 1);
	if (!path_from_env(env))
		return (ft_putendl_fd("Path variable was not found", 2), 1);
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
