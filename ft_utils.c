/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:35:36 by armarake          #+#    #+#             */
/*   Updated: 2025/02/20 16:37:58 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	exit_handler(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

int	open_infile(char *filename)
{
	if (access(filename, F_OK) != 0)
	{
		perror("pipex");
		return (0);
	}
	if (access(filename, R_OK) != 0)
	{
		perror("pipex");
		return (0);
	}
	return(open(filename, O_RDONLY));
}

int	open_outfile(char *filename)
{
	if (access(filename, F_OK) != 0)
		return (open(filename, O_CREAT, 0777));
	if (access(filename, W_OK) != 0)
	{
		perror("pipex");
		return (0);
	}
	return (open(filename, O_WRONLY));
}

char	*get_path(char *cmnd, char *env[])
{
	
}
