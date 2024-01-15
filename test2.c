#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

char **copy_map(int lines);

char **load_map()

{
    int fd;
    int i;
    char *line;
    int lines;

    fd = open("minimal_horizontal.ber", O_RDONLY);
    if (fd == -1)
        exit(1);
    i = 0;

    line = get_next_line(fd);
    while (line[0] != '\0')
    {
        line = get_next_line(fd);
        i++;
    }
    // printf("i = %d\n", i);
    lines = i;
    close(fd);
    return(copy_map(lines));
}

char **copy_map(int lines)
{
    int fd;
    int i;
    char **test;
    test = (char **)malloc(sizeof(char *) * (lines + 1));
    fd = open("minimal_horizontal.ber", O_RDONLY);
    i = 0;
    test[i] = get_next_line(fd);
    while (i < lines - 1)
    {
        // printf("%s", map[i]);
        i++;
        test[i] = get_next_line(fd);
    }
    close(fd);
    return (test);
}

int main(void)
{
    char **map;
    char *line;
    map = load_map();
    int i, j;
    i = 0;
    while (i < 3)
    {
        j = 0;
        line = map[i];
        while (j < 5)
        {
            printf("%c", map[i][j]);
            j++;
        }
        i++;
    }
    return (0);
}
char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*buffer;
	int				res;

	if (fd < 0)
		return (NULL);
	if (list && (has_newline(list) == 1))
		return (return_line(&list));
	res = 1;
	while (res)
	{
		if ((has_newline(list) == 1))
			return (return_line(&list));
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		// printf("Malloc'd1 %p\n", buffer);
		if (!buffer)
			return (NULL);
		res = read_buffer(fd, buffer);
		if (add_node(&list, buffer) == NULL || res == -1)
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

	if (!buffer || !fd)
		return (0);
	res = read(fd, buffer, BUFFER_SIZE);
	if (res == -1)
		return (-1);
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

int count_elves(char *buffer)
{
    int i = 0;
    int count = 0;
    while (buffer[i])
    {
        if (buffer[i-1] == '\n' && buffer[i] == '\n')
            count++;
        i++;
    }
    return (count + 1);
}

int is_symbol(char c)
{
	if (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*' ||
		c == '/' || c == '?' || c == '-' || c == '+' || c == '=')
		return (1);
	return (0);
}