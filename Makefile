# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/02 19:54:31 by glictevo          #+#    #+#              #
#    Updated: 2018/05/03 21:13:01 by upopee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB =		libft
LIBF =		libft/libft.a
ASM =		assembleur
ASMF =		asm
VM =		vm
VMF =		corewar
TESTS =		tests

MAKE =		make -C

all: $(LIBF) $(VMF) $(ASMF)

$(LIBF):
	@$(MAKE) $(LIB)

$(ASMF):
	@$(MAKE) $(ASM)

$(VMF):
	@$(MAKE) $(VM)

$(TESTS):
	@$(MAKE) $(TESTS)

clean:
	@$(MAKE) $(LIB) clean
	@$(MAKE) $(VM) clean
	@$(MAKE) $(ASM) clean
	@$(MAKE) $(TESTS) clean

fclean: clean
	@$(MAKE) $(LIB) fclean
	@$(MAKE) $(VM) fclean
	@$(MAKE) $(ASM) fclean

re: fclean all

.PHONY: all clean fclean re $(LIB) $(ASM) $(VM) $(TESTS)
