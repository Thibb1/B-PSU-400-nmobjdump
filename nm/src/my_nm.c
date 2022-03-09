/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** my_nm
*/

#include "my_nm.h"

void clean_nm(t_nm nm)
{
    if (IS_NULL(nm))
        return;
    DESTROY(nm->name);
    DESTROY(EHDR);
    DESTROY(SYM);
    DESTROY(HDR);
    nm->i = 0;
}

void destroy_nm(t_nm nm)
{
    if (IS_NULL(nm))
        return;
    if (!IS_NULL(nm->fd))
        fclose(nm->fd);
    clean_nm(nm);
    DESTROY(nm->names);
    DESTROY(nm);
}

t_nm init_nm(const char *filename)
{
    t_nm nm = NULL;

    check_file(filename);
    nm = calloc(1, sizeof(struct s_nm));
    if (IS_NULL(nm)) {
        printf("./my_nm: '%s': %s\n", filename, "Out of memory");
        exit(84);
    }
    nm->fd = fopen(filename, "r");
    nm->name = strdup(filename);
    return nm;
}

void print_nm(t_nm nm)
{
    qsort(SYM, nm->i, sizeof(struct s_sym), cmp_sym);
    for (int i = 0; i < nm->i; i++) {
        if (SYM[i].value == 0 && SYMBOL_WEAK(SYM[i].type))
            printf(S_PRINT, SYM[i].type, SYM[i].name);
        else
            printf(S_PRINT_V, SYM[i].value, SYM[i].type, SYM[i].name);
    }
}

int my_nm(const char *filename, const int is_single)
{
    t_nm nm = init_nm(filename);

    CHECK_FD;
    if (!is_single)
        printf("\n%s:\n", nm->name);
    ar_file(nm);
    R_ASSERT_V(!nm->is_ar, 0);
    nm->size = get_size(nm);
    get_ehdr(nm);
    get_shdr(nm);
    get_symbol_table(nm);
    get_symbols(nm);
    print_nm(nm);
    destroy_nm(nm);
    return 0;
}
