/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:35:36 by armarake          #+#    #+#             */
/*   Updated: 2025/04/02 21:36:11 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	if (!*tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	open_infile(char *filename)
{
	if (access(filename, F_OK) != 0)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putendl_fd(filename, 2);
		return (-1);
	}
	if (access(filename, R_OK) != 0)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putendl_fd(filename, 2);
		return (-1);
	}
	return (open(filename, O_RDONLY));
}

int	open_outfile(char *filename)
{
	if (access(filename, F_OK) != 0)
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777));
	if (access(filename, W_OK) != 0)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putendl_fd(filename, 2);
		return (-1);
	}
	return (open(filename, O_WRONLY | O_TRUNC));
}

void	empty_command(char *command)
{
	if (!command || !*command)
	{
		ft_putendl_fd("pipex: empty command", 2);
		exit (1);
	}
}

void	execution_error(char **s_cmnd, char *message)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(s_cmnd[0], 2);
	ft_free_tab(s_cmnd);
	exit(1);
}
