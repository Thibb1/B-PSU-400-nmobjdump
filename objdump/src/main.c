/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** main
*/

#include "my_objdump.h"

int main(int ac, char **av)
{
    if (ac == 1)
        return my_objdump("a.out");
    for (int i = 1; i < ac; i++)
        my_objdump(av[i]);
    return 0;
}
