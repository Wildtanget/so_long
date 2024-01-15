/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notahtah <notahtah@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:02:39 by notahtah          #+#    #+#             */
/*   Updated: 2024/01/14 23:51:24 by notahtah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_print_pointer(unsigned long int number)
{
	int		count;
	char	*string;

	if (!number)
		return (ft_print_string("(nil)"));
	string = ft_ptoa(number);
	count = ft_print_string("0x") + ft_print_string(string);
	free(string);
	return (count);
}

char	*ft_ptoa(unsigned long int number)
{
	int		length;
	char	*string;
	int		position;
	char	*hex_base;
	int		last_digit;

	length = ft_pointer_length(number);
	string = malloc(sizeof(char) * (length + 1));
	if (!string)
		return (NULL);
	position = 0;
	hex_base = "0123456789abcdef";
	while (++position <= length)
	{
		last_digit = number % 16;
		string[length - position] = hex_base[last_digit];
		number /= 16;
	}
	string[length] = '\0';
	return (string);
}

int	ft_pointer_length(unsigned long int number)
{
	int	length;

	length = 0;
	while (number != 0)
	{
		number /= 16;
		length++;
	}
	return (length);
}
