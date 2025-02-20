/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:02:41 by armarake          #+#    #+#             */
/*   Updated: 2025/01/23 20:04:38 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n_size;
	size_t	h_size;

	n_size = ft_strlen(needle);
	if (n_size == 0)
		return ((char *) haystack);
	if (len == 0)
		return (NULL);
	h_size = ft_strlen(haystack);
	i = 0;
	while ((i + n_size) <= len && i < h_size)
	{
		if (ft_strncmp(haystack + i, needle, n_size) == 0)
			return ((char *) haystack + i);
		i++;
	}
	return (NULL);
}
