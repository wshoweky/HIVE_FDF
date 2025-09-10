NAME		=fdf
URL_MLX		=https://github.com/codam-coding-college/MLX42.git
LIBFT		=libft/libft.a
MLX42		=MLX42/build/libmlx42.a

CC			=cc
CFLAGS		=-Wall -Wextra -Werror -O0 -g3
LDFLAGS		=-ldl -lglfw -pthread -lm


DIR_LIBFT	=libft/
DIR_MLX		=MLX42/
DIR_INC		=./
DIR_SRC		=src/
DIR_OBJ		=obj/


HEADERS		=$(addprefix -I , \
				$(DIR_INC) $(DIR_LIBFT) $(DIR_MLX)include/MLX42/)

# Source files organized by functionality
SRCS_MAIN	=$(addprefix $(DIR_SRC)main/, \
				fdf.c fdf_init.c events.c utils.c)
SRCS_MAP	=$(addprefix $(DIR_SRC)map/, \
				map.c map_parse.c map_vertex.c)
SRCS_RENDER	=$(addprefix $(DIR_SRC)render/, \
				render_init.c render_draw.c camera.c colors.c)

SRCS		=$(SRCS_MAIN) $(SRCS_MAP) $(SRCS_RENDER)  
OBJS		=$(patsubst $(DIR_SRC)%.c, $(DIR_OBJ)%.o, $(SRCS))
DEPS		=$(patsubst $(DIR_SRC)%.c, $(DIR_OBJ)%.d, $(SRCS))

.PHONY: all clean fclean re relibft mlx42

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	@echo "Building $(NAME)..."
	@$(CC) $(OBJS) $(LIBFT) $(MLX42) $(LDFLAGS) -o $(NAME)
	@echo "Build complete!"

-include $(DEPS)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c | $(MLX42)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -MMD -MP -MF $(patsubst %.o, %.d, $@) -c $< -o $@

$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -j4 -C $(DIR_LIBFT)

$(MLX42):
	@echo "Setting up MLX42..."
	@if [ ! -d "$(DIR_MLX)" ]; then \
		echo "Cloning MLX42 from $(URL_MLX)..."; \
		git clone $(URL_MLX) $(DIR_MLX); \
	fi
	@if [ ! -f "$(MLX42)" ]; then \
		echo "Building MLX42..."; \
		cd $(DIR_MLX) && cmake -B build && cmake --build build -j4; \
	fi
	@echo "MLX42 is ready!"

mlx42: $(MLX42)

clean:
	@echo "Cleaning object files and dependencies..."
	@rm -rf $(DIR_OBJ) 
	@$(MAKE) -C $(DIR_LIBFT) clean

fclean: clean
	@echo "Full cleaning..."
	@rm -f $(NAME)
	@$(MAKE) -C $(DIR_LIBFT) fclean
	@rm -rf $(DIR_MLX)

re: fclean all

relibft:
	@echo "Rebuilding libft..."
	@$(MAKE) -C $(DIR_LIBFT) re

