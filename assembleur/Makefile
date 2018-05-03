# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/06 17:13:11 by glictevo          #+#    #+#              #
#    Updated: 2018/05/03 22:53:28 by upopee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -- PROJECT VARIABLES & COMMANDS --

NAME =			asm
CC =			gcc
CFLAGS =		-Wall -Werror -Wextra
CPPFLAGS =		-I $(INC_DIR) -I $(LIBFT_DIR) -I$(HOME)/.brew/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE
DEPFLAGS =		-MMD

SHELL =			/bin/bash
MKDIR =			mkdir -p
RMDIR =			rm -rf
RM =			rm -f
NORM =			norminette

# -- LIBRARIES --

LDLIBS =		-lft -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wl,-framework,Cocoa
LDFLAGS =		-L$(LIBFT_DIR) -L$(HOME)/.brew/lib

LIBFT_DIR =		../libft
LIBFT_DEP =		$(LIBFT_DIR)/libft.a

# -- PATHS NAMES --

INC_DIR =		includes
LEX_DIR =		lexer
PAR_DIR =		parser
OBJ_DIR =		.objects

FILES =			$(LEX_DIR)/lexer \
				$(LEX_DIR)/is_something \
				$(LEX_DIR)/is_something2 \
				$(LEX_DIR)/is_something3 \
				$(PAR_DIR)/errors \
				$(PAR_DIR)/errors2 \
				$(PAR_DIR)/main \
				$(PAR_DIR)/free_functions \
				$(PAR_DIR)/parser \
				$(PAR_DIR)/utilities \
				$(PAR_DIR)/parse_parameters \
				$(PAR_DIR)/parse_name_comment \
				$(PAR_DIR)/write_in_file \
				$(PAR_DIR)/write_in_file2 \

OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(FILES:=.o))

# -- IMPLICIT RULES  / LINKING --

$(OBJ_DIR)/%.o: %.c Makefile

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
	@$(MKDIR) $(OBJ_DIR)/$(LEX_DIR)
	@$(MKDIR) $(OBJ_DIR)/$(PAR_DIR)

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
	@$(NORM) $(LEX_DIR)
	@$(NORM) $(PAR_DIR)
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
