# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 17:31:18 by okraus            #+#    #+#              #
#    Updated: 2025/03/09 17:27:12 by okraus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name (output executable)
NAME        := so_long

# Compiler and flags
CC          := cc
CFLAGS      := -Wall -Wextra -Werror
RM          := rm -rf

# Directories
SRC_DIR     := src
OBJ_DIR     := obj
MLX_DIR     := minilibx
SDL_DIR     := sdl2
INCLUDE_DIR := include

# Source and object files
SRCS        :=	main.c \
				graphics/game.c \
				parser/parser.c \
				utils/utils.c
OBJS        := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS        := $(OBJS:.o=.d)

# MiniLibX settings (Linux version)
MLX_REPO    := https://github.com/42Paris/minilibx-linux.git
MLX_FLAGS   := -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11
MLX_LIB     := $(MLX_DIR)/libmlx.a

# SDL2 settings
SDL_LIB     := $(SDL_DIR)/build/.libs/libSDL2.a
SDL_FLAGS   := -I$(SDL_DIR)/include -L$(SDL_DIR)/build/.libs -lSDL2 -lm

# Default rule to build the program
all: CFLAGS += -DLIB=0 -I$(MLX_DIR)

all: $(NAME)

# Default rule using MiniLibX
$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ $(MLX_FLAGS) -o $@

# Ensure MiniLibX is downloaded and built before compiling
$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MiniLibX..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@echo "Building MiniLibX..."
	@make -C $(MLX_DIR)

# Ensure SDL2 is downloaded (Assuming a prebuilt SDL2 package)
$(SDL_LIB):
	@if [ ! -d "$(SDL_DIR)" ]; then \
		echo "Downloading SDL2..."; \
		mkdir -p $(SDL_DIR); \
		curl -L https://www.libsdl.org/release/SDL2-2.26.5.tar.gz | tar xz -C $(SDL_DIR) --strip-components=1; \
	fi
	@if [ ! -d "$(SDL_DIR)/build" ]; then \
		echo "Building SDL2..."; \
		cd $(SDL_DIR) && ./configure --disable-shared --enable-static && make; \
	fi

# Rule to build with SDL2
GAME_NAME   := and_thanks_for_all_the_fish
game: CFLAGS += -DLIB=1 -I$(SDL_DIR)/$(INCLUDE_DIR)

game: $(SDL_LIB) $(OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ $(SDL_FLAGS) -o $(GAME_NAME)

# Rule to compile each source file into an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -MMD -MP -c $< -o $@

# Clean up object files
miniclean:
	$(RM) $(OBJ_DIR)

# Clean up object files
clean:
	$(RM) $(OBJ_DIR)
	make -C $(MLX_DIR) clean || true
	make -C $(SDL_DIR) clean || true

# Clean up both object files and the executable
fclean: clean
	$(RM) $(NAME) $(GAME_NAME)
	$(RM) $(MLX_DIR) $(SDL_DIR)

# Clean and rebuild the program
re: fclean all

# Mark these targets as not actual files
.PHONY: all miniclean clean fclean re game
