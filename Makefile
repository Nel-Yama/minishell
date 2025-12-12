# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 21:03:05 by nel-yama          #+#    #+#              #
#    Updated: 2025/12/10 16:36:51 by nel-yama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable name & Compiler and flags
NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./lib/libft -I./includes \
	-I/opt/homebrew/opt/readline/include #-Werror

# Libraries
LIBFT_DIR = lib/libft

LIBFT = $(LIBFT_DIR)/libft.a

# Linker Driver Flags (ld) - Linker search paths
LDFLAGS = -L$(LIBFT_DIR) \
	-L/opt/homebrew/opt/readline/lib -lreadline

# Header file (optional, not strictly needed unless for dependencies)
HEADER = includes/main.h

# Source files for main program
MAIN = src/main.c

# Source files from source directories
SRC = src/lexing/ft_check_quotes.c src/lexing/lexing.c \
	src/parsing/parsing.c src/parsing/parsing_helper.c \
	src/parsing/parsing_helper_2.c \
	src/pipes/create_pipes.c src/get_env/ft_get_env.c \
	src/here_doc/here_doc.c src/execution/handle_fds.c \
	src/execution/run_cmd.c src/execution/run_child.c \
	src/prog_exit/exit_prog.c src/prog_exit/exit_error.c \
	src/main_utils/main_utils.c src/main_utils/main_utils_2.c \
	src/env_utils/env_utils.c \
	src/builtins/builtin.c \
	src/builtins/ft_echo.c \
	src/builtins/ft_pwd.c \
	src/builtins/ft_env.c \
	src/builtins/ft_exit.c \
	src/builtins/ft_unset.c \
	src/builtins/ft_export.c \
	src/builtins/export_print.c \
	src/builtins/export_append.c \
	src/builtins/ft_cd.c \
	src/expansion/ft_expand_utils.c \
	src/expansion/ft_expand_dollar.c \
	src/expansion/ft_expand_var.c \
	src/expansion/ft_expand.c

# All source files
SRCS = $(MAIN) $(SRC)

# Object files
OBJ_DIR = build
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/$(MAIN:.c=.o)

# Rules
.PHONY: all clean fclean re

# Default rule: build the executable
all: $(NAME)

# Link object files into executable
# Normal executable
$(NAME): $(OBJ) $(LIBFT)
	@echo "Linking $(NAME)..."
	@$(CC) $(OBJ) $(LDFLAGS) $(LIBFT) -o $(NAME)

# Creating the build Directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile source files into object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Remove object files
clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJ) $(BONUS_OBJ)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Remove object files and the executable
fclean: clean
	@echo "Cleaning the library..."
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all
