/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** my_elf
*/

#include "my_nm.h"

off_t get_size(t_nm nm)
{
    struct stat st;

    ASSERT(fstat(fileno(nm->fd), &st) != -1, "fstat failed");
    ASSERT(st.st_size > (off_t)sizeof(Elf64_Ehdr), "file truncated");
    ASSERT(fseek(nm->fd, 0, SEEK_SET) == 0, "fseek failed");
    return st.st_size;
}

void get_ehdr(t_nm nm)
{
    EHDR = malloc(nm->size + 1);
    ASSERT(!IS_NULL(EHDR), "malloc failed");
    ASSERT(fread(EHDR, nm->size, 1, nm->fd) == 1, "fread failed");
    ((char *)EHDR)[nm->size] = '\0';
    ASSERT(memcmp(EHDR->e_ident, ELFMAG, SELFMAG) == 0, FORMAT);
    ARCH = EHDR->e_ident[EI_CLASS] == ELFCLASS64 ? 64 : 0;
    ARCH = EHDR->e_ident[EI_CLASS] == ELFCLASS32 ? 32 : ARCH;
    ASSERT(ARCH == 64 || ARCH == 32, FORMAT);
}

void get_shdr(t_nm nm)
{
    if (IS_32)
        SHDR = (Elf64_Shdr *)((void *)EHDR_32 + EHDR_32->e_shoff);
    else
        SHDR = (Elf64_Shdr *)((void *)EHDR + EHDR->e_shoff);
}

int get_ar(t_nm nm, int skip_sym)
{
    clean_nm(nm);
    HDR = calloc(1, ST_AR_SIZE + 1);
    ASSERT(!IS_NULL(HDR), "malloc failed");
    R_ASSERT_V(fread(HDR, ST_AR_SIZE, 1, nm->fd) == 1, 0);
    ((char *)HDR)[ST_AR_SIZE] = '\0';
    R_ASSERT_V(memcmp(HDR->ar_fmag, ARFMAG, 2) == 0, 0);
    nm->name = get_name(nm, strdup(HDR->ar_name));
    nm->size = atoi(HDR->ar_size);
    if (skip_sym) {
        DESTROY(nm->names);
        nm->names = calloc(1, nm->size + 1);
        ASSERT(!IS_NULL(nm->names), "malloc failed");
        ASSERT(fread(nm->names, nm->size, 1, nm->fd) == 1, "fread failed");
        ((char *)nm->names)[nm->size] = '\0';
    }
    return 1;
}

void ar_file(t_nm nm)
{
    char tmp[SARMAG];

    ASSERT(fread(tmp, SARMAG, 1, nm->fd) == 1, "fread failed");
    nm->is_ar = strncmp(tmp, ARMAG, SARMAG) == 0;
    R_ASSERT(nm->is_ar);
    ASSERT(get_ar(nm, 1), "Couldn't read ar header");
    ASSERT(get_ar(nm, 1), "Couldn't read ar header");
    while (get_ar(nm, 0)) {
        get_ehdr(nm);
        get_shdr(nm);
        get_symbol_table(nm);
        get_symbols(nm);
        printf("\n%s:\n", nm->name);
        print_nm(nm);
    }
    destroy_nm(nm);
}
