# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upopee <upopee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/31 15:28:26 by upopee            #+#    #+#              #
#    Updated: 2018/04/03 21:01:28 by upopee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		sdl_test
CC =		gcc
CFLAGS =	-I /usr/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE
LFLAGS =	-L /usr/local/lib -lSDLmain -lSDL -lSDL_image -lSDL_mixer -Wl,-framework,Cocoa

CFLAGS42 =	-I /Users/upopee/.brew/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE
LFLAGS42 =	-L /Users/upopee/.brew/lib -lSDLmain -lSDL -lSDL_image -lSDL_mixer -Wl,-framework,Cocoa

FILE =		sdl_test.c

all:
	@$(CC) $(CFLAGS) $(LFLAGS) $(FILE) -o $(NAME)
	@printf "$(GREEN_B)✓$(EOC) $(YELLOW)$(NAME)$(EOC) : Binary created\n"

42:
	@$(CC) $(CFLAGS42) $(LFLAGS42) $(FILE) -o $(NAME)
	@printf "$(GREEN_B)✓$(EOC) $(YELLOW)$(NAME)$(EOC) : Binary created\n"

clean:
	@$(RM) $(NAME)
	@printf "$(RED_B)✗$(EOC) $(YELLOW)$(NAME)$(EOC) : Binary deleted\n"

YELLOW =	\e[31;33m
GREEN_B =	\e[32;1m
RED_B =		\e[31;1m
EOC =		\e[0m
