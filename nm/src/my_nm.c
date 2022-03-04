/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** my_nm
*/

#include "my_nm.h"

void destroy_nm(t_nm nm)
{
    if (IS_NULL(nm))
        return;
    if (!IS_NULL(nm->fd))
        fclose(nm->fd);
    DESTROY(nm->name);
    DESTROY(EHDR);
    DESTROY(SYM);
    DESTROY(nm);
}

t_nm init_nm(const char *filename)
{
    t_nm nm = malloc(sizeof(struct s_nm));

    if (IS_NULL(nm)) {
        printf("./my_nm: '%s': %s\n", filename, "Out of memory");
        exit (84);
    }
    nm->fd = fopen(filename, "r");
    nm->name = strdup(filename);
    nm->size = 0;
    nm->is_relocatable = 0;
    nm->i = 0;
    nm->arch = 64;
    EHDR = NULL;
    SHDR = NULL;
    SBL = NULL;
    SYM = NULL;
    return nm;
}

void print_nm(t_nm nm)
{
    qsort(SYM, nm->i, sizeof(struct s_sym), cmp_sym);
    for (int i = 0; i < nm->i; i++) {
        if (SYM[i].value == 0)
            printf(S_PRINT, SYM[i].type, SYM[i].name);
        else
            printf(S_PRINT_V, SYM[i].value, SYM[i].type, SYM[i].name);
    }
}

int my_nm(const char *filename, const int is_single)
{
    t_nm nm = init_nm(filename);
    CHECK_FD;
    relocatable_file(nm);
    if (!is_single)
        printf("\n%s:\n", nm->name);
    print_nm(nm);
    destroy_nm(nm);
    return 0;
}

int main(int ac, char **av)
{
    if (ac == 1)
        return my_nm("a.out", 1);
    for (int i = 1; i < ac; i++)
        my_nm(av[i], ac == 2);
    return 0;
}