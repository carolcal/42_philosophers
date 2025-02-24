# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 15:32:34 by cayamash          #+#    #+#              #
#    Updated: 2025/02/24 12:36:55 by cayamash         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Name of the program
NAME = philosophers

#Compilers and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g3

#Directories
SRC_DIR = src/
OBJ_DIR = obj/
INCLUDES = -I include/ -I src/ -I .

#Source files and object file
SRC = $(addprefix $(SRC_DIR), utils.c init.c start.c routine.c monitor.c main.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#Valgrind
VALGRIND = 	valgrind --leak-check=fill --track-origind=yes --show-leak-kinds=all

#Style
NO_PRINT = --no-print-directory
GREEN = \033[1;32m
END = \033[0m

#Rules
all: $(NAME)

val: $(VALGRIND) ./$(NAME) > valgrind.log 2>&1

norm:
	@echo "\n$(MAGENTA)======= SRC =======$(END)"
	@norminette src | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/Error/\x1b[1;31m&\x1b[0m/g'
	@echo "\n$(BLUE)======= INCLUDES =======$(END)"
	@norminette include | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/Error/\x1b[1;31m&\x1b[0m/g'

#Compile Object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

#Executable
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)Compiled!$(END)"

#Clean Object
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Cleaned$(END)"

#Clean all generated file
fclean: clean
	@rm -rf $(NAME)
	@rm -f valgrind.log
	@echo "$(GREEN)All!$(END)"

#Recompile everything
re: fclean all

PHONY: all clean fclean re val norm
