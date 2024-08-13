
#--- COLORS ---#

RESET = \\x1b[0m

F_BOLD = \\x1b[1m
F_UNDERLINE = \\x1b[4m
F_ITALIC = \\x1b[3m
F_STRIKE = \\x1b[9m

C_GREEN = \\x1b[32m
C_CYAN = \\x1b[36m
C_RED = \\x1b[31m
C_YELLOW = \\x1b[33m

#--- DEFAULT VALUES ---#

NAME = cub3d

SRC = src/main.c src/map.c src/minimap.c src/movement.c src/parse_headers.c src/parse_map.c src/parsing.c src/raycaster.c src/render_minimap.c src/draw.c src/wall.c src/handler.c

OBJS = $(patsubst src/%.c, obj/%.o, $(SRC))

CC = gcc

ARCH := $(shell uname -m)

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -I './includes'

LIBFTPATH = libs/libftms/

LIBFT = libft.a

MLX = build/libmlx42.a

MLXPATH = libs/MLX42/

LIBMMSPATH = libs/libmms/

LIBMMS = libmms.a

PATHGLFW_M1 = /opt/homebrew/Cellar/glfw/3.4/lib

PATHGLFW_42 = /Users/$(USER)/homebrew/opt/glfw/lib/

ifeq ($(ARCH), arm64)
	PATHGLFW = $(PATHGLFW_M1)
else
	PATHGLFW = $(PATHGLFW_42)
endif

#---   RULES   ---#
# Macos compilation settings
# @$(CC) $(CFLAGS) $(OBJS) $(LIBFTPATH)$(LIBFT) $(LIBMMSPATH)$(LIBMMS) $(MLXPATH)$(MLX) -Iinclude -lglfw -L"$(PATHGLFW)" -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)
# Windows WSL compilation settings
# @$(CC) $(CFLAGS) $(OBJS) $(LIBFTPATH)$(LIBFT) $(LIBMMSPATH)$(LIBMMS) $(MLXPATH)$(MLX) -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)


all: $(NAME) logo

$(NAME): submodule $(OBJS) $(LIBFTPATH)$(LIBFT) $(MLXPATH)$(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFTPATH)$(LIBFT) $(LIBMMSPATH)$(LIBMMS) $(MLXPATH)$(MLX) -Iinclude -lglfw -L"$(PATHGLFW)" -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)
	@echo $(F_BOLD)$(F_ITALIC)$(C_CYAN)$(NAME) COMPILED SUCCESSFULLY...$(RESET)

submodule:
	@git submodule update --init

obj/%.o: src/%.c
	@mkdir -p obj/
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo $(F_BOLD)$(F_ITALIC)$(C_CYAN)$(NAME)\'S $@ OBJECT CREATED SUCCESSFULLY...$(RESET)

$(MLXPATH)$(MLX):
	@cmake $(MLXPATH) -B $(MLXPATH)/build
	@$(MAKE) -C $(MLXPATH)/build -j4

$(LIBFTPATH)$(LIBFT): $(LIBMMSPATH)$(LIBMMS)
	@$(MAKE) -C $(LIBFTPATH)
	@$(MAKE) -C $(LIBFTPATH) bonus

$(LIBMMSPATH)$(LIBMMS):
	@$(MAKE) -C $(LIBMMSPATH)

clean:
	@rm -rf obj/
	@echo $(F_BOLD)$(F_ITALIC)$(C_YELLOW)$(NAME) CLEANED SUCCESSFULLY...$(RESET)
	@$(MAKE) -C $(LIBFTPATH) clean
	@$(MAKE) -C $(LIBMMSPATH) clean

fclean: clean
	@rm -rf $(NAME) $(MLXPATH)/build $(MLXPATH)$(MLX)
	@echo $(F_BOLD)$(F_ITALIC)$(C_RED)FULL CLEAN COMPLETED...$(RESET)
	@$(MAKE) -C $(LIBFTPATH) fclean
	@$(MAKE) -C $(LIBMMSPATH) fclean

bonus: all

re: fclean all

logo:
	@echo "$(F_BOLD)$(C_CYAN)--- BUILD COMPLETE ---"
	@echo "███▄ ▄███▓ ███▄ ▄███▓ ▄▄▄       ██▀███   ▄████▄   ▒█████  ▄▄▄█████▓▄▄▄█████▓"
	@echo "▓██▒▀█▀ ██▒▓██▒▀█▀ ██▒▒████▄    ▓██ ▒ ██▒▒██▀ ▀█  ▒██▒  ██▒▓  ██▒ ▓▒▓  ██▒ ▓▒"
	@echo "▓██    ▓██░▓██    ▓██░▒██  ▀█▄  ▓██ ░▄█ ▒▒▓█    ▄ ▒██░  ██▒▒ ▓██░ ▒░▒ ▓██░ ▒░"
	@echo "▒██    ▒██ ▒██    ▒██ ░██▄▄▄▄██ ▒██▀▀█▄  ▒▓▓▄ ▄██▒▒██   ██░░ ▓██▓ ░ ░ ▓██▓ ░ "
	@echo "▒██▒   ░██▒▒██▒   ░██▒ ▓█   ▓██▒░██▓ ▒██▒▒ ▓███▀ ░░ ████▓▒░  ▒██▒ ░   ▒██▒ ░ "
	@echo "░ ▒░   ░  ░░ ▒░   ░  ░ ▒▒   ▓▒█░░ ▒▓ ░▒▓░░ ░▒ ▒  ░░ ▒░▒░▒░   ▒ ░░     ▒ ░░   "
	@echo "░  ░      ░░  ░      ░  ▒   ▒▒ ░  ░▒ ░ ▒░  ░  ▒     ░ ▒ ▒░     ░        ░    "
	@echo "░      ░   ░      ░     ░   ▒     ░░   ░ ░        ░ ░ ░ ▒    ░        ░      "
	@echo "       ░          ░         ░  ░   ░     ░ ░          ░ ░                    "
	@echo "                                         ░                                   $(RESET)"
