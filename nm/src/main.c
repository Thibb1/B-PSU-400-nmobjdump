/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** main
*/

#include "my_nm.h"

int main(int ac, char **av)
{
    int a = ac;
    if (ac == 1)
        return my_nm("a.out", 1);
    for (int i = 1; i < ac; i++) {
        if (av[i][0] != '-')
            my_nm(av[i], a == 2);
        else
            a--;
    }
    return 0;
}
