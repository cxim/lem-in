NAME = visual

CC = gcc
#FLAGS = -Wall -Werror -Wextra
LIBRARIES = -lmlx -lft -L$(LIB_DIRECTORY) -L$(MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIB_HEADERS) -I$(MINILIBX_HEADERS)

LIB = $(LIB_DIRECTORY)libft.a
LIB_DIRECTORY = ./includes/libft/
LIB_HEADERS = $(LIB_DIRECTORY)includes/

MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
MINILIBX_DIRECTORY = ./includes/minilibx_macos/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

HEADERS_LIST = visual.h

HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./srcs/
SOURCES_LIST =  main.c              \
				errors.c            \
                get_structure_1.c   \
                get_structure_2.c   \
                get_structure_3.c   \
                map_reading.c       \
                color.c             \
                draw.c              \
                draw2.c              \
                key_settings_1.c    \
                key_settings_2.c    \
                mouse_settings.c    \
                rotate_map.c        \
                menu.c              \
                check_map.c			\
                anima1.c			\
                anima2.c			\

SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

all: $(NAME)

$(NAME): $(LIB) $(MINILIBX) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) -c $(INCLUDES) $< -o $@

$(LIB):
	@$(MAKE) -sC $(LIB_DIRECTORY)

$(MINILIBX):
	@$(MAKE) -sC $(MINILIBX_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIB_DIRECTORY) clean
	@$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)

fclean: clean
	@rm -f $(MINILIBX)
	@rm -f $(LIB)
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re