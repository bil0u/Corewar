# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/02 19:54:31 by glictevo          #+#    #+#              #
#    Updated: 2018/05/03 14:30:51 by upopee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB =		libft
ASM =		asm
VM =		vm
TESTS =		tests

MAKE =		make -C

all: $(LIB) $(ASM) $(VM) $(TESTS)

$(LIB):
	@$(MAKE) $(LIB)

$(ASM):
	@$(MAKE) $(ASM)

$(VM):
	@$(MAKE) $(VM)

$(TESTS):
	@$(MAKE) $(TESTS)

clean:
	@$(MAKE) $(LIB) clean
	@$(MAKE) $(ASM) clean
	@$(MAKE) $(VM) clean
	@$(MAKE) $(TESTS) clean

fclean: clean
	@$(MAKE) $(LIB) fclean
	@$(MAKE) $(ASM) fclean
	@$(MAKE) $(VM) fclean

re: fclean all

.PHONY: all clean fclean re $(LIB) $(ASM) $(VM) $(TESTS)
