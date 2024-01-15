NAME		= 	so_long.out
LIBFT		= 	libft.a
LIBFT_DIR	=	./libft

CC			= 	cc
FLAGS 		= 	-Wall -Wextra -Werror
INCLUDE 	= 	-lmlx -lXext -lX11

NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

SRCS_GAME	= 	./srcs/game.c

SRCS_GNL	= 	./get_next_line/get_next_line.c \
		  		./get_next_line/get_next_line_utils.c \

OBJ 		= 	*.o

SRC 		= 	$(SRCS_GAME) $(SRCS_GNL)

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(CURSIVE) $(GRAY) "Removing $(NAME)..." $(NONE)
	@make -C $(LIBFT_DIR)
	@echo $(CURSIVE) $(GRAY) "Removing $(NAME)..." $(NONE)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT_DIR)/$(LIBFT) $(INCLUDE) -o $(NAME)

$(OBJ): $(SRC)
	@echo $(CURSIVE) $(GRAY) "Removing $(NAME)..." $(NONE)
	@$(CC) $(FLAGS) -c $(SRC) 

clean:
	@echo $(CURSIVE) $(GRAY) "Removing $(NAME)..." $(NONE) 
	@rm -rf $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean:
	@echo $(CURSIVE) $(GRAY) "Removing $(NAME)..." $(NONE)
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all