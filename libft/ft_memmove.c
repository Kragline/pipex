/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:22:56 by armarake          #+#    #+#             */
/*   Updated: 2024/12/02 23:22:56 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d_ptr;
	unsigned char	*s_ptr;

	if (!dest && !src)
		return (NULL);
	d_ptr = (unsigned char *)dest;
	s_ptr = (unsigned char *)src;
	if (dest > src)
		while (n-- > 0)
			d_ptr[n] = s_ptr[n];
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
