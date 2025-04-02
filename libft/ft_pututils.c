/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pututils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:46:30 by armarake          #+#    #+#             */
/*   Updated: 2025/01/26 14:14:22 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	byte_putchar(char chr)
{
	return (write(1, &chr, 1));
}

size_t	byte_putstr(char *str)
{
	size_t	bytes;

	if (str == NULL)
		return (byte_putstr("(null)"));
	bytes = 0;
	while (*str)
		bytes += byte_putchar(*str++);
	return (bytes);
}

size_t	byte_putnbr(int nbr)
{
	size_t	bytes;

	bytes = 0;
	if (nbr == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nbr < 0)
	{
		bytes += byte_putchar('-');
		nbr = -nbr;
	}
	if (nbr > 9)
		bytes += byte_putnbr(nbr / 10);
	bytes += byte_putchar((nbr % 10) + '0');
	return (bytes);
}

size_t	byte_putunsigned(unsigned int nbr)
{
	size_t	bytes;

	bytes = 0;
	if (nbr > 9)
		bytes += byte_putunsigned(nbr / 10);
	bytes += byte_putchar(nbr % 10 + '0');
	return (bytes);
}
