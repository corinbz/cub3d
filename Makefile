NAME    = cub3d
CFLAGS  = -Wextra -Wall -Wextra -Wunreachable-code -g #-Ofast

#MLX STUFF
LIBMLX	= ./MLX42
HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# Source directories
SRC_DIRS = src src/utilities src/map_parsing

# Find all .c files in the source directories
SRCS    = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# Create object files in obj directory while maintaining directory structure
OBJS    = $(patsubst src/%.c,obj/%.o,$(SRCS))
OBJDIR  = ./obj

# Colors for prettier output
GREEN=\033[1;32m
BLUE=\033[1;36m
YELLOW=\033[1;33m
RED=\033[1;31m
NC=\033[0m # No Color

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# Create object directories and compile
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