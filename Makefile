SRC := main.c check_connections.c check_rooms.c error_mngr.c valid_input.c \
find_ways.c check_ways_num.c send_ants.c check_duplicate_room.c
SRC := $(addprefix src/, $(SRC))
OBJ := $(SRC:.c=.o)
INC_DIR = includes/
LIB_DIR = libft/
LIB_INC_DIR = $(LIB_DIR)$(INC_DIR)
CC = gcc
FLAGS = -Wall -Werror -Wextra
INC_LIB = -L$(LIB_DIR) -lft
NAME = lem-in

all: create_libft $(SRC) $(NAME)

create_libft:
	@make -C $(LIB_DIR)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -o $@ $^ $(INC_LIB)
	@echo "Create $(NAME)"

%.o: %.c
	@$(CC) $(FLAGS) -c -o $@ $< -I$(LIB_INC_DIR) -I$(INC_DIR)

clean:
	@/bin/rm -f $(OBJ)
	@make clean -C $(LIB_DIR)

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C $(LIB_DIR)

re: fclean all