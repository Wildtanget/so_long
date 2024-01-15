/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notahtah <notahtah@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:18:57 by notahtah          #+#    #+#             */
/*   Updated: 2024/01/14 23:44:58 by notahtah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_print_char(int character)
{
	return (write(1, &character, 1));
}

int	ft_print_string(char *string)
{
	size_t	position;

	position = -1;
	if (!string)
		return (ft_print_string("(null)"));
	while (string[++position])
		ft_print_char(string[position]);
	return (position);
}

int	ft_print_percent(void)
{
	return (ft_print_char('%'));
}
