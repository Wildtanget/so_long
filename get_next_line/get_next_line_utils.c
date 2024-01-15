/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notahtah <notahtah@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 00:58:57 by notahtah          #+#    #+#             */
/*   Updated: 2024/01/15 00:58:58 by notahtah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save_remainder(t_list *list)
{
	int		i;
	int		j;
	char	*remainder;
	t_list	*current;

	if (!list)
		return (NULL);
	j = 0;
	i = 0;
	current = list;
	while (current->next)
		current = current->next;
	while (current->data[i] != '\n' && current->data[i] != '\0')
		i++;
	remainder = malloc(sizeof(char) * (BUFFER_SIZE - ++i + 1));
	// printf("Malloc'd2 %p\n", remainder);
	if (!remainder)
		return (NULL);
	while (current->data && current->data[i])
	{
		remainder[j++] = current->data[i];
		current->data[i++] = '\0';
	}
	remainder[j] = '\0';
	if (remainder[0] == '\0')
	{
		free(remainder);
		return (NULL);
	}
	return (remainder);
}

char	*create_line(t_list *head)
{
	char	*line;
	t_list	*current;
	int		i;
	int		j;
	int		length;

	if (!head)
		return (NULL);
	length = count_length(head);
	line = malloc(sizeof(char) * length + 1);
	// printf("Malloc'd3 %p\n", line);
	if (!line)
		return (NULL);
	current = head;
	i = 0;
	while (current)
	{
		j = 0;
		while (current->data[j] && i < length)
			line[i++] = current->data[j++];
		current = current->next;
	}
	line[i] = '\0';
	return (line);
}

int	read_buffer(int fd, char *buffer)
{
	int	res;

	buffer[0] = '\0';
	if (!buffer)
		return (0);
	res = read(fd, buffer, BUFFER_SIZE);
	if (res == -1)
		free(buffer);
	else if (res > 0)
		buffer[res] = '\0';
	return (res);
}

void	*add_node(t_list **head, char *data)
{
	t_list	*new;
	t_list	*current;

	if (!head || !data)
		return (NULL);
	new = malloc(sizeof(t_list));
	// printf("Malloc'd4 %p\n", new);
	if (!new)
		return (NULL);
	new->data = data;
	new->next = NULL;
	if (!(*head))
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (new);
}

int	count_length(t_list *head)
{
	t_list	*current;
	int		count;
	int		i;

	if (!head)
		return (0);
	current = head;
	count = 0;
	while (current)
	{
		i = 0;
		while (current->data[i] && current->data[i] != '\0'
			&& current->data[i] != '\n')
		{
			count++;
			i++;
		}
		if (current->data[i] == '\n')
			count++;
		current = current->next;
	}
	return (count);
}
