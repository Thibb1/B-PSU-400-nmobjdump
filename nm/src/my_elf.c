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
    ARCH = EHDR->e_ident[EI_CLASS] == ELFCLASS32 ? 32 : 64;
}

void get_shdr(t_nm nm)
{
    SHDR = (Elf64_Shdr *)((void *)EHDR + EHDR->e_shoff);
}

void relocatable_file(t_nm nm)
{
    char tmp[SARMAG];

    ASSERT(fread(tmp, SARMAG, 1, nm->fd) == 1, "fread failed");
    ASSERT(strncmp(tmp, ARMAG, SARMAG) != 0, "File is not an object file");
    nm->is_relocatable = 1;
    nm->size = get_size(nm);
    get_ehdr(nm);
    get_shdr(nm);
    get_symbol_table(nm);
    get_symbols(nm);
}
