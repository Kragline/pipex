/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:01:48 by armarake          #+#    #+#             */
/*   Updated: 2025/01/27 13:50:52 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	byte_puthex(unsigned long long nbr, int upper)
{
	size_t	bytes;
	char	*digits;

	if (upper)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	bytes = 0;
	if (nbr >= 16)
		bytes += byte_puthex(nbr / 16, upper);
	bytes += byte_putchar(digits[nbr % 16]);
	return (bytes);
}

size_t	byte_putpointer(unsigned long long nbr)
{
	size_t	bytes;

	bytes = 0;
	if (!nbr)
	{
		bytes += byte_putstr("0x0");
		return (bytes);
	}
	bytes += byte_putstr("0x");
	bytes += byte_puthex(nbr, 0);
	return (bytes);
}
