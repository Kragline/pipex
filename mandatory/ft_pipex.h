/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:04:23 by armarake          #+#    #+#             */
/*   Updated: 2025/04/02 21:33:52 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

void	ft_free_tab(char **tab);
int		open_infile(char *filename);
int		open_outfile(char *filename);
char	*path_from_env(char *env[]);
char	*get_full_path(char *cmnd, char *env[]);
void	empty_command(char *command);
void	execution_error(char **s_cmnd, char *message);

#endif