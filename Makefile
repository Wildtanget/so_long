NAME		= 	so_long.out
LIBFT		= 	libft.a
LIBFT_DIR	=	./libft

CC			= 	cc
FLAGS 		= 	-Wall -Wextra -Werror
INCLUDE 	= 	-lmlx -lXext -lX11

# NONE='\033[0m'
# GREEN='\033[32m'
# GRAY='\033[2;37m'
# CURSIVE='\033[3m'

SRCS_GAME	= 	./srcs/game.c

SRCS_GNL	= 	./get_next_line/get_next_line.c \
		  		./get_next_line/get_next_line_utils.c \

OBJ 		= 	*.o

SRC 		= 	$(SRCS_GNL) $(SRCS_GAME)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT_DIR)/$(LIBFT) $(INCLUDE) -o $(NAME)

$(OBJ): $(SRC)
	@$(CC) $(FLAGS) -c $(SRC) 

clean:
	@rm -rf $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all