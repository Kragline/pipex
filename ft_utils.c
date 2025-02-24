/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:35:36 by armarake          #+#    #+#             */
/*   Updated: 2025/02/24 14:48:53 by armarake         ###   ########.fr       */
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

char	*path_from_env(char *env[])
{
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
		{
			j = 0;
			while (env[i][j] && env[i][j] != '=')
				j++;
			return (env[i] + j + 1);
		}
		i++;
	}
	return (NULL);
}

char	*get_full_path(char *cmnd, char *env[])
{
	char	*temp;
	char	*final_path;
	char	**s_paths;

	s_paths = ft_split(path_from_env(env), ':');
	while (*s_paths)
	{
		temp = ft_strjoin(*s_paths, "/");
		final_path = ft_strjoin(temp, cmnd);
		if (access(final_path, F_OK | X_OK) == 0)
			return (final_path);
		s_paths++;
	}
	return (NULL);
}
