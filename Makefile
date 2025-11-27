V = false

ifeq ($(V),true)
	ECHO =
else
	ECHO = @
endif

# Nom du programme
NAME = cub3D
NAME_BONUS = cub3d_bonus

# Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

# Génération automatique des dépendances pour les headers
CFLAGS += -MMD -MP

OS = $(shell uname | tr '[:upper:]' '[:lower:]')

MAKE = make -sC
MKDIR = mkdir -p
RM = rm -rf

# Lib perso
LIB_DIR = lib
LIB = $(LIB_DIR)/lib.a
LINKER = $(LIB)

# Info système
#$(info 🖥️  OS détecté : $(OS))

# MiniLibX - Platform-dependent compilation
MLX_BASE ?= minilibx
ifeq ($(OS),linux)
	MLX_DIR         := $(MLX_BASE)/minilibx-linux
	MLX             := $(MLX_DIR)/libmlx.a
	INCLUDES_FLAG   += -I$(MLX_DIR)
	LINKER          += -L$(MLX_DIR) -lmlx -lm -lz -lXext -lX11
else
	# macOS — détection du support Metal (FR/EN) + présence du dossier Metal
	METAL_SUPPORTED := $(shell system_profiler SPDisplaysDataType 2>/dev/null | grep -Eiq 'Metal.*(Pris en charge|Supported)' && echo yes || echo no)
	HAS_METAL_DIR   := $(shell test -d $(MLX_BASE)/minilibx_macos_metal && echo yes)

ifneq ($(and $(METAL_SUPPORTED),$(HAS_METAL_DIR)),)
	# → Metal OK
	MLX_DIR         := $(MLX_BASE)/minilibx_macos_metal
	MLX             := $(MLX_DIR)/libmlx.a
	INCLUDES_FLAG   += -I$(MLX_DIR)
	LINKER          += -L$(MLX_DIR) -lmlx -framework Metal -framework MetalKit -framework AppKit
else
	# → fallback OpenGL
	MLX_DIR         := $(MLX_BASE)/minilibx_macos_opengl
	MLX             := $(MLX_DIR)/libmlx.a
	INCLUDES_FLAG   += -I$(MLX_DIR)
	LINKER          += -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif
endif

# Includes
INCLUDE_DIR = include
LIB_SUBDIR = lib/ft_fprintf lib/ft_printf lib/gnl lib/libft

INCLUDE_FLAG = -I$(INCLUDE_DIR) \
			   $(foreach dir, $(LIB_SUBDIR), -I$(dir))

INCLUDE_FLAG += $(INCLUDES_FLAG)

INCLUDE = $(INCLUDE_DIR)/color.h \
		$(INCLUDE_DIR)/cub3d.h \
		$(INCLUDE_DIR)/keys.h \
		$(LIB_DIR)/ft_fprintf/ft_fprintf.h \
		$(LIB_DIR)/ft_printf/ft_printf.h \
		$(LIB_DIR)/gnl/get_next_line_bonus.h \
		$(LIB_DIR)/libft/libft.h

# Dossiers sources
SRC_DIR = src/

# Fichiers sources (relatifs à SRC_DIR)
SRC_MAIN = \
	main.c

SRC_DEBUG = \
	debug/print_data.c \
	debug/ray_debug.c

SRC_PARSING = \
	parsing/check_map.c \
	parsing/get_map.c \
	parsing/get_rgb.c \
	parsing/parse_element.c \
	parsing/parse_floor_ceiling.c \
	parsing/parse_game_info.c \
	parsing/parse_wall.c \
	parsing/parsing_utils.c

SRC_PLAYER = \
	player/events.c \
	player/events_mouse.c \
	player/player_move.c \
	player/movement.c

SRC_INIT = \
	init/init_data.c \
	init/init_mlx.c \
	init/init_player.c

SRC_UTILS = \
	utils/cleanup.c \
	utils/print_error.c \
	utils/utils.c

SRC_GFX = \
	gfx/draw.c \
	gfx/extra.c \
	gfx/texture.c \
	gfx/render.c \
	gfx/dda.c \

SRC_MINIMAP = \
	minimap/minimap.c \
	minimap/draw_utils.c \
	minimap/minimap_focus.c \
	minimap/accessorize_fov.c \
	minimap/param_cam_minimap.c \
	minimap/param_cam_minimap_focus.c \

SRC_FILES = $(SRC_MAIN) $(SRC_DEBUG) $(SRC_PARSING) $(SRC_PLAYER) $(SRC_INIT) $(SRC_UTILS) $(SRC_GFX) $(SRC_MINIMAP)

# Chemins complets des sources et objets
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS_DIR = objs/
OBJS_BONUS_DIR = objs_bonus/
#OBJS = $(addprefix $(OBJS_DIR), $(*.=.o))
OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))
OBJS_BONUS = $(patsubst $(SRC_DIR)%.c,$(OBJS_BONUS_DIR)%.o,$(SRCS))

# fichiers de dépendances .d générés automatiquement
DEPS = $(OBJS:.o=.d) $(OBJS_BONUS:.o=.d)

# inclure les fichiers de dépendances (ne pas échouer s'ils n'existent pas)
-include $(DEPS)

# Couleurs ANSI
GREEN = \033[32m
RED = \033[31m
RESET = \033[0m
YELLOW = \033[33m
CLEAR_LINE = \033[2K\r
PINK  = \033[95m
WHITE = \033[97m

# Logo cool
logo ?=on   # on => affiche le logo, off => masque

PRINT_LOGO = \
    if [ "$(logo)" != "off" ]; then \
    $(TERM_RESET); \
    echo ""; \
    printf "$(PINK)"; \
    printf "\n"; \
    printf "  ░██████             ░██            ░██████  ░███████   \n"; \
    printf " ░██   ░██            ░██           ░██   ░██ ░██   ░██  \n"; \
    printf "░██        ░██    ░██ ░████████           ░██ ░██    ░██ \n"; \
    printf "░██        ░██    ░██ ░██    ░██      ░█████  ░██    ░██ \n"; \
    printf "░██        ░██    ░██ ░██    ░██          ░██ ░██    ░██ \n"; \
    printf " ░██   ░██ ░██   ░███ ░███   ░██    ░██   ░██ ░██   ░██  \n"; \
    printf "  ░██████   ░█████░██ ░██░█████      ░██████  ░███████   \n"; \
    printf "\n"; \
    printf "$(RESET)\n"; \
    echo "	  ┌─────────────────────────────┐"; \
    echo "	  │                             │"; \
    echo "	  │  FPS = Frames Per Segfault  │"; \
    echo "	  │                             │"; \
    echo "	  └─────────────────────────────┘"; \
    echo "	                                           "; \
    echo "	        eieong 🤝 aumartin"; \
    printf "\n"; \
    fi

PRINT_CLEAN_LOGO = \
    @$(TERM_RESET); \
    printf "$(GREEN)\n"; \
    printf "░██████████  ░██████   ░██     ░██ ░██████████    ░█████████  ░█████████    ░██████   ░█████████  ░█████████  ░██████████ \n"; \
    printf "    ░██     ░██   ░██  ░██     ░██     ░██        ░██     ░██ ░██     ░██  ░██   ░██  ░██     ░██ ░██     ░██ ░██         \n"; \
    printf "    ░██    ░██     ░██ ░██     ░██     ░██        ░██     ░██ ░██     ░██ ░██     ░██ ░██     ░██ ░██     ░██ ░██         \n"; \
    printf "    ░██    ░██     ░██ ░██     ░██     ░██        ░█████████  ░█████████  ░██     ░██ ░█████████  ░█████████  ░█████████  \n"; \
    printf "    ░██    ░██     ░██ ░██     ░██     ░██        ░██         ░██   ░██   ░██     ░██ ░██         ░██   ░██   ░██         \n"; \
    printf "    ░██     ░██   ░██   ░██   ░██      ░██        ░██         ░██    ░██   ░██   ░██  ░██         ░██    ░██  ░██         \n"; \
    printf "    ░██      ░██████     ░██████       ░██        ░██         ░██     ░██   ░██████   ░██         ░██     ░██ ░██████████ \n"; \
    printf "$(RESET)\n";

# pour le clear
TERM_RESET = printf "\033[2J\033[H"

# Compilation principale
all: $(LIB) $(MLX) $(NAME)

# Compilation lib
$(LIB):
	@echo "$(YELLOW) Compilation de la lib...$(RESET)\r"
	@$(MAKE) $(LIB_DIR) > /dev/null 2>&1 \
	&& echo -e "$(CLEAR_LINE) Compilation lib réussie (✔)" \
	|| { echo -e "$(CLEAR_LINE)❌ Erreur : Compilation de la lib échouée (✘)"; exit 1; }

$(MLX):
	@echo "$(YELLOW) Vérification / clonage MiniLibX...$(RESET)\r"
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "➡️ $(YELLOW) Clonage de la MiniLibX depuis GitHub...$(RESET)"; \
		git clone --depth=1 https://github.com/42paris/minilibx-linux.git $(MLX_DIR) >/dev/null 2>&1 \
		&& echo " MiniLibX clonée avec succès (✔)"; \
	else \
		echo " MiniLibX déjà présente, pas de clonage nécessaire (✔)"; \
	fi
	@echo "$(YELLOW) Compilation de MiniLibX...$(RESET)\r"
	@$(MAKE) $(MLX_DIR) > /dev/null 2>&1 \
	&& echo -e "$(CLEAR_LINE) Compilation mlx réussie (✔)" \
	|| { echo -e "$(CLEAR_LINE)❌ Erreur : Compilation de MiniLibX échouée (✘)"; exit 1; }

# Règle pour objets
$(OBJS_DIR):
	@$(MKDIR) $(OBJS_DIR)

$(OBJS_BONUS_DIR):
	@$(MKDIR) $(OBJS_BONUS_DIR)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE_FLAG) -c $< -o $@

$(OBJS_BONUS_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE) | $(OBJS_BONUS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE_FLAG) -c $< -o $@

# $(OBJS_DIR)main.o: main.c $(INCLUDE) | $(OBJS_DIR)
# 	@$(CC) $(CFLAGS) $(INCLUDE_FLAG) -c $< -o $(OBJS_DIR)main.o

# Compilation du binaire
$(NAME): $(OBJS) $(LIB) $(MLX)
	@echo "$(YELLOW) 🚀 Compilation de $(NAME)...$(RESET)\r"
	@$(CC) $(CFLAGS) $(OBJS) $(LINKER) -o $(NAME) && echo "$(CLEAR_LINE) $(NAME) a été créé avec succès (✔)" && echo "$(GREEN)     eieong 🤝 aumartin" \
	&& $(PRINT_LOGO)

$(NAME_BONUS): $(OBJS_BONUS) $(LIB) $(MLX)
	@echo "$(YELLOW) 🚀 Compilation de $(NAME_BONUS)...$(RESET)\r"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LINKER) -o $(NAME_BONUS) && echo "$(CLEAR_LINE) $(NAME_BONUS) a été créé avec succès (✔)" \
	&& $(PRINT_LOGO)

# Nettoyage
clean:
	@echo "$(YELLOW)🧹 Nettoyage clean en cours...$(RESET)\r"
	@$(RM) $(OBJS_DIR)
	@$(RM) $(OBJS_BONUS_DIR)
	@echo -e "$(CLEAR_LINE) Nettoyage clean réussi (✔)"

fclean: clean
	@echo "$(YELLOW)🧼 Nettoyage complet fclean en cours...$(RESET)\r"
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@$(MAKE) $(LIB_DIR) fclean
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) $(MLX_DIR) clean > /dev/null 2>&1; fi
	@if [ -d "$(MLX_BASE)" ]; then $(RM) $(MLX_BASE); fi
	@echo -e "$(CLEAR_LINE) Nettoyage complet fclean réussi (✔)"
	$(PRINT_CLEAN_LOGO)

bonus: $(LIB) $(MLX) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
