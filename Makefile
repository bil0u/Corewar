# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upopee <upopee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/15 11:05:28 by upopee            #+#    #+#              #
#    Updated: 2018/05/03 06:55:30 by upopee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -- PROJECT VARIABLES & COMMANDS --

NAME =			corewar
CC =			gcc
CFLAGS =		-Wall -Werror -Wextra -g
CPPFLAGS =		-I $(INC_DIR) -I $(LIBFT_DIR) -I/Users/upopee/.brew/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE
DEPFLAGS =		-MMD

SHELL =			/bin/bash
MKDIR =			mkdir -p
RMDIR =			rm -rf
RM =			rm -f
NORM =			norminette

# -- LIBRARIES --

LDLIBS =		-lft -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wl,-framework,Cocoa
LDFLAGS =		-Llibft -L/Users/upopee/.brew/lib

LIBFT_DIR =		libft
LIBFT_DEP =		$(LIBFT_DIR)/libft.a

# -- PATHS NAMES --

SRC_DIR =		sources
OP_DIR	=		cpu_instructions
SDL_DIR	=		visu
INC_DIR =		includes
OBJ_DIR =		.objects

# -- PROJECT FILES --

FILES =			vm_main \
				vm_init \
				vm_tools \
				debug_gameinfo \
				debug_memory \
				debug_tools \
				verbose_tools \
				load_core \
				load_tools \
				cpu_core \
				cpu_tools \
				$(OP_DIR)/op01_live \
				$(OP_DIR)/op02_ld \
				$(OP_DIR)/op03_st \
				$(OP_DIR)/op04_add \
				$(OP_DIR)/op05_sub \
				$(OP_DIR)/op06_and \
				$(OP_DIR)/op07_or \
				$(OP_DIR)/op08_xor \
				$(OP_DIR)/op09_zjmp \
				$(OP_DIR)/op10_ldi \
				$(OP_DIR)/op11_sti \
				$(OP_DIR)/op12_fork \
				$(OP_DIR)/op13_lld \
				$(OP_DIR)/op14_lldi \
				$(OP_DIR)/op15_lfork \
				$(OP_DIR)/op16_aff \
				$(SDL_DIR)/sdl_init \
				$(SDL_DIR)/sdl_ttfinit \
				$(SDL_DIR)/sdl_clean \
				$(SDL_DIR)/sdl_start \
				$(SDL_DIR)/sdl_title \
				$(SDL_DIR)/sdl_mainscreen \
				$(SDL_DIR)/sdl_colors \

OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(FILES:=.o))

# -- IMPLICIT RULES  / LINKING --

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile

	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB) - 1))))
	@$(eval COLOR=$(shell list=(160 196 202 208 215 221 226 227 190 154 118 82 46); index=$$(($(PERCENT) * $${#list[@]} / 100)); echo "$${list[$$index]}"))
	@printf "\r> $(YELLOW)$(NAME)$(EOC) : Creating binary...  %2d%% $(CNO)[`printf '#%.0s' {0..$(DONE)}`%*s]$(YELLOW)%*.*s$(EOC)$(ERASELN)" $(PERCENT) $(COLOR) $(TO_DO) "" $(DELTA) $(DELTA) "$(shell echo "$@" | sed 's/^.*\///')"
	@$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

# -- RULES --

all: $(LIBFT_DEP)
	@$(MAKE) -j $(NAME)

$(NAME): $(LIBFT_DEP) $(OBJ_DIR) $(OBJECTS)
	@$(CC) $(LDLIBS) $(LDFLAGS) $(OBJECTS) -o $@
	@printf "\r$(ERASELN)$(GREEN_B)✓$(EOC) $(YELLOW)$(NAME)$(EOC) : Binary created\n"

$(LIBFT_DEP):
	@$(MAKE) lib

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)
	@$(MKDIR) $(OBJ_DIR)/$(OP_DIR)
	@$(MKDIR) $(OBJ_DIR)/$(SDL_DIR)

clean: libclean
	@if [ -e $(OBJ_DIR) ]; \
	then \
		$(RMDIR) $(OBJ_DIR); \
		printf "$(RED_B)✗$(EOC) $(YELLOW)$(NAME)$(EOC) : Objects deleted\n"; \
	fi;

fclean: clean libfclean
	@if [ -e $(NAME) ]; \
	then \
		$(RM) $(NAME); \
		printf "$(RED_B)✗$(EOC) $(YELLOW)$(NAME)$(EOC) : Binary deleted\n"; \
	fi;

re: fclean all

norm:
	@$(NORM) $(SRC_DIR)
	@$(NORM) $(INC_DIR)

lib:
	@$(MAKE) -C $(LIBFT_DIR)

libclean:
	@$(MAKE) -C $(LIBFT_DIR) clean

libfclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean

libre: libfclean lib

libnorm:
	@$(NORM) $(LIB_DIR)

.PHONY: all clean libclean fclean libfclean re libre norm libnorm

-include $(OBJECTS:.o=.d)

# -- DISPLAY --

LEN_NAME =	`printf "%s" $(NAME) |wc -c`
DELTA =		$$(echo "$$(tput cols)-51-$(LEN_NAME)"|bc)
NB =		$(words $(FILES))
INDEX=		0

ERASELN =	\033[K
CNO =		\033[38;5;%dm

YELLOW =	\e[31;33m
YELLOW_B =	\e[31;33;1m
GREEN =		\e[32m
GREEN_B =	\e[32;1m
RED =		\e[31m
RED_B =		\e[31;1m
WHITE =		\e[37m
WHITE_B =	\e[37;1m
EOC =		\e[0m
