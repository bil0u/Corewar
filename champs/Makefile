# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upopee <upopee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/02 07:03:08 by upopee            #+#    #+#              #
#    Updated: 2018/05/15 20:55:07 by upopee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM =		../asm
ASM_ZAZ =	../tests_ressources/asm_zaz

FILES =		$(shell find . -name '*.s')
BINARIES =	$(FILES:.s=.cor)

RM =		rm -f

%.cor: %.s
	@$(ASM_ZAZ) $<

all: mine

mine:
	@$(ASM) $(FILES)

zaz: $(BINARIES)

clean:
	@$(RM) $(BINARIES)
