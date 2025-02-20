/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:21:41 by armarake          #+#    #+#             */
/*   Updated: 2025/01/23 20:01:42 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *str, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	while (*str)
	{
		in_word = 0;
		while (*str && *str == c)
			++str;
		while (*str && *str != c)
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
			++str;
		}
	}
	return (count);
}

static void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	const char	*new_s;
	char		**arr;
	int			words_count;
	int			i;

	if (!s)
		return (NULL);
	words_count = count_words(s, c);
	arr = (char **)malloc((words_count + 1) * (sizeof(char *)));
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < words_count)
	{
		while (*s == c)
			s++;
		new_s = s;
		while (*s && *s != c)
			s++;
		arr[i] = ft_substr(new_s, 0, s - new_s);
		if (!arr[i])
			return (free_array(arr));
	}
	arr[i] = NULL;
	return (arr);
}
