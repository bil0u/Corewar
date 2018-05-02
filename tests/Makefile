# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upopee <upopee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/02 07:03:08 by upopee            #+#    #+#              #
#    Updated: 2018/05/02 07:04:02 by upopee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM =		./asm_zaz

CHAMPS =	./champs
CHP_SRC =	$(shell find $(CHAMPS) -name '*.s')
CHP_COR =	$(CHP_SRC:.s=.cor)

OPTESTS =	./op_tests
OP_SRC =	$(shell find $(OPTESTS) -name '*.s')
OP_COR =	$(OP_SRC:.s=.cor)

TOURNAMENT =	./tournament
TOURN_SRC =	$(shell find $(TOURNAMENT) -name '*.s')
TOURN_COR =	$(TOURN_SRC:.s=.cor)


%.cor:%.s
	@ $(ASM) $<

all: champs op tournament

champs: $(CHP_COR)

op: $(OP_COR)

tournament: $(TOURN_COR)

clean:
	@rm -f $(CHP_COR) $(OP_COR) $(TOURN_COR)
