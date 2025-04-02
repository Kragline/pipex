/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:04:27 by armarake          #+#    #+#             */
/*   Updated: 2025/04/02 17:11:35 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	check_command(char *path, char **s_cmnd, char **env)
{
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putendl_fd(path, 2);
		ft_free_tab(s_cmnd);
		exit(1);
	}
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putendl_fd(path, 2);
		ft_free_tab(s_cmnd);
		exit(1);
	}
	if (execve(path, s_cmnd, env) == -1)
	{
		ft_putstr_fd("pipex: execution failed: ", 2);
		ft_free_tab(s_cmnd);
		free(path);
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
		path_to_cmnd = s_cmnd[0];
	else
	{
		path_to_cmnd = get_full_path(s_cmnd[0], env);
		if (!path_to_cmnd)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			ft_putendl_fd(s_cmnd[0], 2);
			ft_free_tab(s_cmnd);
			exit(1);
		}
	}
	check_command(path_to_cmnd, s_cmnd, env);
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
	pid_t	proc_id;
	pid_t	proc_id2;

	if (argc != 5)
		return (ft_putendl_fd("Wrong number of arguments", 2), 1);
	if (pipe(pipefd) == -1)
		return (ft_putendl_fd("Pipe failed", 2), 1);
	proc_id = fork();
	if (proc_id == -1)
		return (ft_putendl_fd("Fork failed", 2), 1);
	if (proc_id == 0)
		execve_child(argv, pipefd, env);
	proc_id2 = fork();
	if (proc_id2 == -1)
		return (ft_putendl_fd("Fork failed", 2), 1);
	if (proc_id2 == 0)
		execve_parent(argv, pipefd, env);
	return (0);
}
