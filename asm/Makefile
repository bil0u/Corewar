# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/06 17:13:11 by glictevo          #+#    #+#              #
#    Updated: 2018/05/03 15:43:36 by upopee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB =	../libft
NAME =	asm
CC =	gcc
FLAG =	-Wall -Werror -Wextra
OBJ =	lexer/lexer.o \
		lexer/is_something.o \
		lexer/is_something2.o \
		lexer/is_something3.o \
		parser/errors.o \
		parser/errors2.o \
		parser/main.o \
		parser/free_functions.o \
		parser/parser.o \
		parser/utilities.o \
		parser/parse_parameters.o \
		parser/parse_name_comment.o \
		parser/write_in_file.o \
		parser/write_in_file2.o

all: $(LIB) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAG) $(OBJ) -L ../libft/ -lft -o $(NAME)
	@printf "\r$(ERASELN)$(GREEN_B)✓$(EOC) $(YELLOW)$(NAME)$(EOC) : Binary created\n"

%.o: %.c
	@$(CC) $(FLAG) -c $^ -o $@

clean:
	@rm -f $(OBJ)
	@printf "$(RED_B)✗$(EOC) $(YELLOW)$(NAME)$(EOC) : Objects deleted\n";

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED_B)✗$(EOC) $(YELLOW)$(NAME)$(EOC) : Binary deleted\n";

norm:
	@norminette lexer parser includes

re: fclean all

.PHONY: all clean fclean re

# -- DISPLAY --

YELLOW =	\e[31;33m
GREEN_B =	\e[32;1m
RED_B =		\e[31;1m
EOC =		\e[0m
