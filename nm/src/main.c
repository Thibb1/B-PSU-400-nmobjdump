/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** main
*/

#include "my_nm.h"

int main(int ac, char **av)
{
    if (ac == 1)
        return my_nm("a.out", 1);
    for (int i = 1; i < ac; i++)
        my_nm(av[i], ac == 2);
    return 0;
}
