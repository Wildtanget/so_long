/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notahtah <notahtah@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:07:36 by notahtah          #+#    #+#             */
/*   Updated: 2024/01/14 23:45:18 by notahtah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

// int main(void)
// {
//     int length1 = ft_printf(" %p %p d\n", 0, 0);
//     int length2 = printf(" %p %p d\n", 0, 0);
//    	printf("Ft_printf = %d and printf = %d\n", length1, length2);
//     return (0);
// }

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	position;
	int		count;

	va_start(args, format);
	position = -1;
	count = 0;
	while (format[++position])
	{
		if (format[position] == '%')
			count += ft_print_specifier(format[++position], args);
		else
			count += write(1, &format[position], 1);
	}
	va_end(args);
	return (count);
}

int	ft_print_specifier(int specifier, va_list args)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count = ft_print_char(va_arg(args, int));
	else if (specifier == 's')
		count = ft_print_string(va_arg(args, char *));
	else if (specifier == 'p')
		count = ft_print_pointer(va_arg(args, unsigned long int));
	else if (specifier == 'd' || specifier == 'i')
		count = ft_print_integer(va_arg(args, int));
	else if (specifier == 'u')
		count = ft_print_unsigned(va_arg(args, unsigned long int));
	else if (specifier == 'x' || specifier == 'X')
		count = ft_print_hex(va_arg(args, int), specifier);
	else if (specifier == '%')
		count = ft_print_percent();
	return (count);
}
