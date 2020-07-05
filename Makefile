NAME = lem-in

CC = gcc
FLAGS = -Wall -Werror -Wextra
LIBRARIES = -lftprintf -L$(LIB_DIRECTORY)
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIB_HEADERS)

LIB = $(LIB_DIRECTORY)libftprintf.a
VIS = $(VIS_DIR)visual

LIB_DIRECTORY = ./ft_printf/
LIB_HEADERS = $(LIB_DIRECTORY)includes/
VIS_DIR = ./visualizer
HEADERS_LIST = lemin.h

HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

CREAT = \033[0;32m
IMPORTANT =\033[1;36m
DELETE = \033[0;31m
EOC = \033[0m

SOURCES_DIRECTORY = ./srcs/
SOURCES_LIST =  main.c              \
                parsing.c	        \
                errors.c 			\
                errors2.c           \
                alloc_malloc.c		\
                free_func.c			\
                print_some.c		\
                filling.c			\
                find_some.c			\
                diekctra.c			\
                diekctra2.c			\
                road.c				\

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

all: $(NAME)

$(NAME): $(LIB) $(VIS) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "$(IMPORTANT)<----- $(NAME) sucсessfully created ---->$(EOC)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(CREAT)<----- Object directory was created ----->$(EOC)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(CREAT)<----- $@ was created ------ ------>$(EOC)"

$(LIB):
	@$(MAKE) -sC $(LIB_DIRECTORY)
	@echo "$(CREAT)<----- Libft_Printf was created ------ --->$(EOC)"

$(VIS):
	@$(MAKE) -sC $(VIS_DIR)
	@echo "$(CREAT)<----- Visual was created ------ --->$(EOC)"

clean:
	@$(MAKE) -sC $(LIB_DIRECTORY) clean
	@$(MAKE) -sC $(VIS_DIR) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(DELETE)<----- All objects were deleted ------ -->$(EOC)"

fclean: clean
	@rm -f $(VIS)
	@rm -f $(LIB)
	@rm -f $(NAME)
	@echo "$(DELETE)<----- All files were deleted ------ ---->$(EOC)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "$(IMPORTANT)<----- All files were rebuilding ----->$(EOC)"

.PHONY: all clean fclean re