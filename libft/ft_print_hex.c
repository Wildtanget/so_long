/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notahtah <notahtah@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:36:21 by notahtah          #+#    #+#             */
/*   Updated: 2024/01/14 23:45:03 by notahtah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"


int	ft_print_hex(unsigned int number, int specifier)
{
	char	*string;
	int		count;

	if (specifier == 'x')
		string = ft_htoa(number, 0);
	else
		string = ft_htoa(number, 1);
	count = ft_print_string(string);
	free(string);
	return (count);
}

char	*ft_htoa(unsigned int number, int c)
{
	int		length;
	char	*string;
	int		position;
	char	*hex_base[2];
	int		last_digit;

	length = ft_hex_length(number);
	string = malloc(sizeof(char) * (length + 1));
	if (!string)
		return (NULL);
	position = 0;
	hex_base[0] = "0123456789abcdef";
	hex_base[1] = "0123456789ABCDEF";
	while (++position <= length)
	{
		last_digit = number % 16;
		string[length - position] = hex_base[c][last_digit];
		number /= 16;
	}
	string[length] = '\0';
	return (string);
}

int	ft_hex_length(unsigned int number)
{
	int	length;

	if (number == 0)
		return (1);
	length = 0;
	while (number != 0)
	{
		number /= 16;
		length++;
	}
	return (length);
}
