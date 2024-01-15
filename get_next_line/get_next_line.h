#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 140
# endif
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h> 
# include <string.h>

typedef struct s_list {
	char			*data;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	*add_node(t_list **head, char *data);
char	*save_remainder(t_list *list);
int		has_newline(t_list *node);
char	*create_line(t_list *head);
int		count_length(t_list *head);
int		read_buffer(int fd, char *buffer);
void	clear_list(t_list **list);
char	*return_line(t_list **list);
#endif

