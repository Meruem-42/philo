CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

NAME = philo

SRC =	src/ft_atoi.c \
		src/free_all.c \
		src/time.c \
		src/print.c \
		src/eat.c \
		src/free_all.c \
		src/manager.c \
		src/philo_behavior.c \
		src/philo.c \
		src/main.c 
		

GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

OBJ_DIR = build/

OBJ = $(SRC:src/%.c=$(OBJ_DIR)%.o)

$(OBJ_DIR)%.o : src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)Compilation successful ! ✅ $(RESET)"

all : $(NAME)

clean :
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)All object files cleaned. 🧹$(RESET)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(YELLOW)Executable cleaned. 🧹$(RESET)"

re : fclean all

.PHONY: clean fclean re


