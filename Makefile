# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 17:31:18 by okraus            #+#    #+#              #
#    Updated: 2025/03/04 19:03:15 by okraus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Program name (output executable)
NAME := so_long

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := rm -rf

# Directories for source and object files
SRC_DIR := src
OBJ_DIR := obj

# List of source files
SRCS := main.c \
        utils/utils.c
# Corresponding object files for compilation
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
# Dependency files for automatic rebuilding
DEPS := $(OBJS:.o=.d)

# Rule to link object files into the final executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile each source file into an object file
# Creates the object directory if needed
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
# Ensure the object file's directory exists before compiling
	mkdir -p $(dir $@)
# Compile source file and generate object file along with dependency file
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Default rule to build the program
all: $(NAME)

# Clean up object files
clean:
	$(RM) $(OBJ_DIR)

# Clean up both object files and the executable
fclean: clean
	$(RM) $(NAME)

# Clean and rebuild the program
re: fclean all

# Mark these targets as not actual files
.PHONY: all clean fclean re

# Include the dependency files if they exist
-include $(DEPS)
