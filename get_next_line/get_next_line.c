/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notahtah <notahtah@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:40:07 by notahtah          #+#    #+#             */
/*   Updated: 2023/11/29 21:04:43 by notahtah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// int	main(void)
// {
// 	int	fd = open("file.txt", O_RDWR);
// 	int	i = 0;
// 	char *line;

// 	while (i < 1)
// 	{
// 		line = get_next_line(0);
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*buffer;
	int				res;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0	)
		return (NULL);
	if (list && (has_newline(list) == 1))
		return (return_line(&list));
	res = 1;
	while (res)
	{
		if ((has_newline(list) == 1))
		{
			line = return_line(&list);
			return (line);
		}
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		// printf("Malloc'd1 %p\n", buffer);
		if (!buffer)
			return (NULL);
		res = read_buffer(fd, buffer);
		if (res == -1 || add_node(&list, buffer) == NULL || list->data[0] == '\0')
		{
			clear_list(&list);
			return (NULL);
		}
	}
	if (res == 0)
		return (return_line(&list));
	return (NULL);
}

int	has_newline(t_list *node)
{
	int		i;
	t_list	*current;

	if (node)
	{
		current = node;
		while (current->next)
			current = current->next;
		i = 0;
		if (current->data)
		{
			while (current->data[i] && current->data[i] != '\0')
			{
				if (current->data[i] == '\n')
					return (1);
				i++;
			}
		}
	}
	return (0);
}

void	clear_list(t_list **list)
{
	t_list	*previous;
	t_list	*current;

	if (!*list)
		return ;
	current = *list;
	if (current->next)
	{
		while (current->next)
		{
			previous = current;
			current = current->next;
			// printf("Free'd2 %p\n", previous->data);
			// printf("Free'd3 %p\n", previous);
			free(previous->data);
			free(previous);
			previous = NULL;
		}
	}
	if (current)
	{
		// printf("Free'd2 %p\n", current->data);
		// printf("Free'd3 %p\n", current);
		free(current->data);
		free(current);
	}
	*list = NULL;
}

char	*return_line(t_list **list)
{
	char			*remainder;
	char			*line;

	if ((has_newline(*list) == 1))
	{
		remainder = save_remainder(*list);
		line = create_line(*list);
		clear_list(list);
		add_node(list, remainder);
	}
	else
	{
		line = create_line(*list);
		clear_list(list);
	}
	return (line);
}
