##
## EPITECH PROJECT, 2022
## nmobjdump
## File description:
## Makefile
##

#####################################################
#
# 					PARAMETERS
#
#####################################################

SOURCE = 	src/main.c \
			src/my_objdump.c \
			src/my_elf.c \
			src/my_print.c \
			src/my_utils.c
OBJS = $(SOURCE:.c=.o)
OBJS_TEST = $(SOURCE_TEST:.c=.o)
NAME = my_objdump
CC = gcc
CFLAGS = -W -Wall -Wshadow -Wextra -I./includes/

#####################################################
#
# 					RULES
#
#####################################################

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) -f $(OBJS) $(OBJS_TEST)
	find . -type f -name '*.gc*' -delete

fclean: clean
	$(RM) -rf $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug
