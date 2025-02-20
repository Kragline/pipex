/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:11:11 by armarake          #+#    #+#             */
/*   Updated: 2025/01/13 12:28:38 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_ptr;
	unsigned char	chr;

	s_ptr = (unsigned char *)s;
	chr = (unsigned char)c;
	while (n > 0)
	{
		if (*s_ptr == chr)
			return ((void *)s_ptr);
		s_ptr++;
		n--;
	}
	return (NULL);
}
