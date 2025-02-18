NAME    = cub3d
CFLAGS  = -Werror -Wall -Wextra -Wunreachable-code -g #-fsanitize=address #-Ofast

#MLX STUFF
LIBMLX	= ./MLX42
HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# Source directories
SRC_MAP = src/map_parsing/check_map_basic.c \
			src/map_parsing/check_map_lines.c \
			src/map_parsing/check_map_space.c \
			src/map_parsing/parse_colors.c \
			src/map_parsing/parse_file_map.c \
			src/map_parsing/parse_img_paths.c

SRC_UTIL = src/utilities/errors.c \
			src/utilities/free_structs.c \
			src/utilities/ft_split.c \
			src/utilities/get_next_line_utils.c \
			src/utilities/get_next_line.c \
			src/utilities/utils_files.c \
			src/utilities/utils_memory.c \
			src/utilities/utils_strings.c \
			src/utilities/utils_strings_2.c

SRC_ROOT = src/game_loop.c \
			src/helpers.c \
			src/key_callback.c \
			src/main.c \
			src/render_wall_texture.c

SRCS    = $(SRC_MAP) \
			$(SRC_UTIL) \
			$(SRC_ROOT)

OBJS    = $(SRCS:src/%.c=$(OBJDIR)/%.o)
OBJDIR  = obj

# Colors for prettier output
GREEN=\033[1;32m
BLUE=\033[1;36m
YELLOW=\033[1;33m
RED=\033[1;31m
NC=\033[0m # No Color

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "$(GREEN)Compiled $< successfully!$(NC)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $@
	@echo "$(BLUE)$(NAME) created successfully!$(NC)"

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBMLX)/build
	@echo "$(YELLOW)$(NAME) -> Object files removed!$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) executable removed!$(NC)"

re: fclean all

.PHONY: all clean fclean re libmlx