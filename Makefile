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

nm:
	make -C nm
	cp nm/my_nm my_nm

objdump:
	make -C objdump
	cp objdump/my_objdump my_objdump

all: nm objdump

clean:
	make -C nm clean
	make -C objdump clean

fclean: clean
	make -C nm fclean
	make -C objdump fclean
	$(RM) my_nm my_objdump

re: fclean all

.PHONY: all clean fclean re nm objdump
