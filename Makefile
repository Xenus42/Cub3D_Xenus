NAME := cub3d

override SRCDIR := srcs/

override BUILDDIR := .build/$(MODE)/$(DEFINE)/

override FLAGFILE := .build/.compile_flags

override OBJDIR := $(addprefix $(BUILDDIR), objs/)

override DEPDIR := $(addprefix $(BUILDDIR), deps/)

MAIN := main

BASENAME := $(MAIN) \
			$(addprefix game/, init_data_game_key) \
			$(addprefix keyboard/, handle_key handle_key_utils) \
			$(addprefix minimap/, draw_minimap_bonus) \
			$(addprefix parsing/, parse_line parse_map_line parse_file check_map free_parsing parse_color) \
			$(addprefix player/, init_player update_player update_player_utils wall_collision_bonus) \
			$(addprefix raycasting/, raycasting raycasting_utils_calculate_wall_distance raycasting_utils_dda_algo raycasting_utils_dda_algo_utils_calculate_step raycasting_utils_draw_vertical_line raycasting_utils_draw_vertical_line_utils_render_wall_pixel_column raycasting_utils_draw_vertical_line_utils_wall_texture_fill raycasting_utils_init_ray raycasting_utlils_draw_vertical_line_utils_texture_mapping) \
			$(addprefix render_3d/, draw_floor_and_ceilling render) \
			$(addprefix textures/, charge_textures free_textures texture_loader texture_ptrs) \
			$(addprefix window/, open_window window_events)

DIR := $(addprefix $(DEPDIR), $(sort $(filter-out ./, $(dir $(BASENAME)))))    \
       $(addprefix $(OBJDIR), $(sort $(filter-out ./, $(dir $(BASENAME)))))

override SRCS := $(addprefix $(SRCDIR), $(addsuffix .c, $(BASENAME)))

override OBJS := $(addprefix $(OBJDIR), $(addsuffix .o, $(BASENAME)))

override DEPS := $(addprefix $(DEPDIR), $(addsuffix .d, $(BASENAME)))

override LIBFT := libft/libft.a

override MLX := minilibx-linux/libmlx.a

override LDFLAGS := -lmlx -lXext -lX11 -lft -lm

override LDLIBS := -L libft/ -L minilibx-linux/

override FILTERED_SRCS := $(strip $(foreach f,$(SRCS),$(if $(or $(findstring test,$(f)),$(findstring tmp,$(f))),,$(f)))) $(strip $(foreach f,$(addprefix includes/, $(shell ls includes/)),$(if $(or $(findstring test,$(f)),$(findstring tmp,$(f))),,$(f))))

CC := cc

CFLAGS := -Wall -Wextra -Werror -Wunreachable-code

ifeq (debug, $(MODE))
CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -g3
endif

ifeq (opti, $(MODE))
CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -O3 -march=native -flto -funroll-loops -finline-functions -fomit-frame-pointer -fno-math-errno -funsafe-math-optimizations -fno-signed-zeros -DNDEBUG -pipe
endif

ifeq (gprof, $(MODE))
CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -pg
endif

ifeq (asan, $(MODE))
CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -fsanitize=address -g3 -O1
endif

ifeq (msan, $(MODE))
CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -fsanitize=memory -g3 -O1
#-Wstrict-prototypes
endif

ifeq (lsan, $(MODE))
CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -fsanitize=leak -g3 -O1
endif

CPPFLAGS := -Iincludes -Ilibft/includes -Iminilibx-linux/

DEPSFLAGS := -MD -MP -MF

MAKEFLAGS += --no-print-directory

.DEFAULT_GOAL = all

-include $(DEPS)

CURRENT_FLAGS := $(MODE)$(DEFINE)$(CC)$(CFLAGS)$(CPPFLAGS)$(LDFLAGS)$(LDLIBS)$(TEST)

ifneq ($(MODE),)
ifneq ($(shell cat $(FLAGFILE) 2>/dev/null), $(CURRENT_FLAGS))
$(shell mkdir -p $(BUILDDIR) && echo '$(CURRENT_FLAGS)' > $(FLAGFILE))
endif
endif

.PHONY: json
json:
	@compiledb $(MAKE) MODE="$(MODE)"

.PHONY: all
all:
	@$(MAKE) MODE="default" TEST="$(TEST)" $(NAME) DEFINE="MANDATORY"

.PHONY: bonus
bonus:
	@$(MAKE) MODE="opti" TEST="$(TEST)" $(NAME) DEFINE="BONUS"

#-j$(nproc) 
.PHONY: debug
debug:
	@$(MAKE) -j$(nproc) MODE="debug" TEST="$(TEST)" $(NAME)

.PHONY: asan
asan:
	@$(MAKE) -j$(nproc) MODE="asan" TEST="$(TEST)" $(NAME)

.PHONY: lsan
lsan:
	@$(MAKE) -j$(nproc) MODE="lsan" TEST="$(TEST)" $(NAME)

.PHONY: msan
msan:
	@$(MAKE) -j$(nproc) MODE="msan" TEST="$(TEST)" $(NAME)

.PHONY: gprof
gprof:
	@$(MAKE) -j$(nproc) MODE="gprof" TEST="$(TEST)" $(NAME)

.PHONY: opti
opti:
	@$(MAKE) -j$(nproc) MODE="opti" TEST="$(TEST)" $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX) $(FLAGFILE)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LDLIBS) $(LDFLAGS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c | $(DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPSFLAGS) $(DEPDIR)$*.d -c $< -o $@

$(LIBFT): force
	@$(MAKE) -j$(nproc) MODE="$(MODE)" -C libft/

$(MLX): force
	@$(MAKE) -C minilibx-linux/

$(FLAGFILE): | $(BUILDDIR)
	@echo '$(CURRENT_FLAGS)' > $@

.PHONY: force
force:

$(DIR):
	mkdir -p $@

.PHONY: clean
clean:
	@$(MAKE) -j$(nproc) clean -C minilibx-linux/
	@$(MAKE) -j$(nproc) MODE="$(MODE)" clean -C libft/
	rm -rf $(BUILDDIR)

.PHONY: fclean
fclean: clean
	@$(MAKE) -j$(nproc) MODE="$(MODE)" fclean -C libft/
	rm -f $(NAME)

.PHONY: re
re: fclean all

.PHONY: norm
norm:
	@$(MAKE) $@ -C $(dir $(LIBFT))
	@norminette $(FILTERED_SRCS)
