/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** my_elf
*/

#include "my_objdump.h"

off_t get_size(t_objdump objdump)
{
    struct stat st;

    ASSERT(fstat(fileno(objdump->fd), &st) != -1, "fstat failed");
    ASSERT(st.st_size > (off_t)sizeof(Elf64_Ehdr), "file truncated");
    ASSERT(fseek(objdump->fd, 0, SEEK_SET) == 0, "fseek failed");
    return st.st_size;
}

void get_ehdr(t_objdump objdump)
{
    EHDR = malloc(objdump->size + 1);
    ASSERT(!IS_NULL(EHDR), "malloc failed");
    ASSERT(fread(EHDR, objdump->size, 1, objdump->fd) == 1, "fread failed");
    ((char *)EHDR)[objdump->size] = '\0';
    ASSERT(memcmp(EHDR->e_ident, ELFMAG, SELFMAG) == 0, FORMAT);
    ARCH = EHDR->e_ident[EI_CLASS] == ELFCLASS64 ? 64 : 0;
    ARCH = EHDR->e_ident[EI_CLASS] == ELFCLASS32 ? 32 : ARCH;
    ASSERT(ARCH == 64 || ARCH == 32, FORMAT);
}

void get_shdr(t_objdump objdump)
{
    if (IS_32)
        SHDR = (Elf64_Shdr *)((void *)EHDR_32 + EHDR_32->e_shoff);
    else
        SHDR = (Elf64_Shdr *)((void *)EHDR + EHDR->e_shoff);
}

int get_ar(t_objdump objdump, int skip_sym)
{
    clean_objdump(objdump);
    HDR = calloc(1, ST_AR_SIZE + 1);
    ASSERT(!IS_NULL(HDR), "malloc failed");
    R_ASSERT_V(fread(HDR, ST_AR_SIZE, 1, objdump->fd) == 1, 0);
    ((char *)HDR)[ST_AR_SIZE] = '\0';
    R_ASSERT_V(memcmp(HDR->ar_fmag, ARFMAG, 2) == 0, 0);
    NAME = get_name(objdump, strdup(HDR->ar_name));
    objdump->size = atoi(HDR->ar_size);
    if (skip_sym) {
        DESTROY(objdump->names);
        objdump->names = calloc(1, objdump->size + 1);
        ASSERT(!IS_NULL(objdump->names), "malloc failed");
        ASSERT(fread(objdump->names, objdump->size, 1, objdump->fd) == 1,
            "fread failed");
        ((char *)objdump->names)[objdump->size] = '\0';
    }
    return 1;
}

void ar_file(t_objdump objdump)
{
    char tmp[SARMAG];

    ASSERT(fread(tmp, SARMAG, 1, objdump->fd) == 1, "fread failed");
    objdump->is_ar = strncmp(tmp, ARMAG, SARMAG) == 0;
    R_ASSERT(objdump->is_ar);
    printf("In archive %s:\n", NAME);
    ASSERT(get_ar(objdump, 1), "Couldn't read ar header");
    ASSERT(get_ar(objdump, 1), "Couldn't read ar header");
    while (get_ar(objdump, 0)) {
        get_ehdr(objdump);
        get_shdr(objdump);
        print_objdump(objdump);
    }
    destroy_objdump(objdump);
}
