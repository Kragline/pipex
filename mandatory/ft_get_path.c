/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:30:11 by armarake          #+#    #+#             */
/*   Updated: 2025/04/02 21:09:36 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

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
	int		i;
	char	*temp;
	char	*final_path;
	char	**s_paths;

	i = 0;
	s_paths = ft_split(path_from_env(env), ':');
	while (s_paths[i])
	{
		temp = ft_strjoin(s_paths[i], "/");
		final_path = ft_strjoin(temp, cmnd);
		free(temp);
		if (access(final_path, F_OK | X_OK) == 0)
			return (ft_free_tab(s_paths), final_path);
		free(final_path);
		i++;
	}
	ft_free_tab(s_paths);
	return (NULL);
}
