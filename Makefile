##
## EPITECH PROJECT, 2022
## nmobjdump
## File description:
## Makefile
##

#####################################################
#
# 					RULES
#
#####################################################

all:
	make -C nm
	mv nm/my_nm my_nm
	make -C objdump
	mv objdump/my_objdump my_objdump

clean:
	make -C nm clean
	make -C objdump clean

fclean: clean
	make -C nm fclean
	make -C objdump fclean
	$(RM) my_nm my_objdump

re: fclean all

.PHONY: all clean fclean re
