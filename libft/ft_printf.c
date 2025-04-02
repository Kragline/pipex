/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:59:57 by armarake          #+#    #+#             */
/*   Updated: 2025/01/27 13:45:13 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_parse_formatter(const char *str, va_list args)
{
	size_t	bytes;

	bytes = 0;
	if (*str == '%')
		bytes += byte_putchar('%');
	else if (*str == 'c')
		bytes += byte_putchar(va_arg(args, int));
	else if (*str == 's')
		bytes += byte_putstr(va_arg(args, char *));
	else if (*str == 'p')
		bytes += byte_putpointer(va_arg(args, unsigned long long));
	else if (*str == 'i' || *str == 'd')
		bytes += byte_putnbr(va_arg(args, int));
	else if (*str == 'u')
		bytes += byte_putunsigned(va_arg(args, unsigned int));
	else if (*str == 'x')
		bytes += byte_puthex(va_arg(args, unsigned int), 0);
	else if (*str == 'X')
		bytes += byte_puthex(va_arg(args, unsigned int), 1);
	return (bytes);
}

int	ft_printf(const char *str, ...)
{
	size_t	bytes;
	va_list	args;

	bytes = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			bytes += ft_parse_formatter(str++, args);
		}
		else
		{
			bytes += byte_putchar(*str);
			str++;
		}
	}
	va_end(args);
	return (bytes);
}
