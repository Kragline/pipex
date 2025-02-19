/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:04:27 by armarake          #+#    #+#             */
/*   Updated: 2025/02/19 18:45:01 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int main(int argc, char *argv[], char *env[])
{
	int pipefd[2];
	pid_t pid;
	
	
	char *g_args[] = {"grep", "f", NULL};
	char *wc_args[] = {"wc", NULL};

	pipe(pipefd);

	pid = fork();
	if (pid == 0)
	{
		int infile = open(argv[1], O_RDONLY);
		dup2(infile, 0);
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		
		execve("/usr/bin/grep", g_args, env);
		perror("Error while executing grep");
	}
	else
	{
		int outfile = open(argv[2], O_WRONLY);
		dup2(outfile, 1);
		dup2(pipefd[0], 0);
		close(pipefd[1]);

		execve("/usr/bin/wc", wc_args, env);
		perror("Error while executing wc");	
	}
	
	return (0);
}