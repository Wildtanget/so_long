/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_integer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notahtah <notahtah@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:45:18 by notahtah          #+#    #+#             */
/*   Updated: 2024/01/14 23:45:07 by notahtah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"


char	*ft_utoa(unsigned int number);
int		ft_unsigned_length(unsigned int number);

int	ft_print_integer(int number)
{
	char	*string;
	int		count;

	string = ft_itoa(number);
	count = ft_print_string(string);
	free(string);
	return (count);
}

int	ft_print_unsigned(unsigned int number)
{
	char	*string;
	int		count;

	string = ft_utoa(number);
	count = ft_print_string(string);
	free(string);
	return (count);
}

char	*ft_utoa(unsigned int number)
{
	int		length;
	char	*string;
	int		position;
	int		last_digit;

	length = ft_unsigned_length(number);
	string = malloc(sizeof(char) * (length + 1));
	if (!string)
		return (NULL);
	position = 0;
	while (++position <= length)
	{
		last_digit = number % 10;
		string[length - position] = last_digit + '0';
		number /= 10;
	}
	string[length] = '\0';
	return (string);
}

int	ft_unsigned_length(unsigned int number)
{
	int	length;

	if (number == 0)
		return (1);
	length = 0;
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}
