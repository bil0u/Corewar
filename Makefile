# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/02 19:54:31 by glictevo          #+#    #+#              #
#    Updated: 2018/05/16 00:28:21 by upopee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_DIR =	libft
LIB =		$(LIB_DIR)/libft.a
ASM_DIR =	assembler
ASM =		asm
VM_DIR =	vm
VM =		corewar
CHAMPS =	champs
TESTS =		tests_resources

MAKE =		make -C
RM =		rm -f
LN =		ln -fs

all: lib asm vm

lib:
	@$(MAKE) $(LIB_DIR)

asm:
	@$(MAKE) $(ASM_DIR)
	@$(LN) $(ASM_DIR)/$(ASM) $(ASM)

vm:
	@$(MAKE) $(VM_DIR)
	@$(LN) $(VM_DIR)/$(VM) $(VM)

champs: $(ASM)
	@$(MAKE) $(CHAMPS)

tests: $(ASM)
	@$(MAKE) $(TESTS)

clean:
	@$(MAKE) $(LIB_DIR) clean
	@$(MAKE) $(VM_DIR) clean
	@$(MAKE) $(ASM_DIR) clean
	@$(MAKE) $(TESTS) clean
	@$(MAKE) $(CHAMPS) clean

fclean: clean
	@$(MAKE) $(LIB_DIR) fclean
	@$(RM) $(VM)
	@$(MAKE) $(VM_DIR) fclean
	@$(RM) $(ASM)
	@$(MAKE) $(ASM_DIR) fclean

norm:
	@$(MAKE) $(LIB_DIR) norm
	@$(MAKE) $(VM_DIR) norm
	@$(MAKE) $(ASM_DIR) norm

re: fclean all

.PHONY: all lib asm vm champs tests clean fclean norm re
