/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** main
*/

#include "my_nm.h"

void check_file(const char *filename)
{
    t_nm nm = NULL;
    FILE *fd = fopen(filename, "r");
    struct stat st;

    if (IS_NULL(fd)) {
        fprintf(stderr, "./my_nm: '%s': No such file\n", filename);
        exit(84);
    }
    ASSERT(stat(filename, &st) != -1, FORMAT);
    if (S_ISDIR(st.st_mode)) {
        printf("./my_nm: Warning: '%s' is a directory\n", filename);
        exit(84);
    }
    fclose(fd);
}

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
