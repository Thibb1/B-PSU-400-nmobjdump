/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** my_print
*/

#include "my_objdump.h"

void print_flags(t_objdump objdump)
{
    int i = printf(HAS_RELOC ? "HAS_RELOC" : "");
    i += printf(F_EXEC_P, EXEC_P ? "EXEC_P" : "");
    i += printf(F_HAS_LINENO, HAS_LINENO ? "HAS_LINENO" : "");
    i += printf(F_HAS_DEBUG, HAS_DEBUG ? "HAS_DEBUG" : "");
    i += printf(F_HAS_SYMS, HAS_SYMS ? "HAS_SYMS" : "");
    i += printf(F_HAS_LOCALS, HAS_LOCALS ? "HAS_LOCALS" : "");
    i += printf(F_DYNAMIC, DYNAMIC ? "DYNAMIC" : "");
    i += printf(F_WP_TEXT, WP_TEXT ? "WP_TEXT" : "");
    i += printf(F_D_PAGED, D_PAGED ? "D_PAGED" : "");
    i += printf(F_BFD_IS_RELAX, BFD_IS_RELAX ? "BFD_IS_RELAXABLE" : "");
    printf(F_HAS_LOAD_PAGE, HAS_LOAD_PAGE ? "HAS_LOAD_PAGE" : "");
    printf("\n");
}

void print_section(t_objdump objdump, int i)
{
    for (unsigned int j = S_OFFSET; j < S_OFFSET + S_SIZE; j += 16) {
        printf(" %04x ", (int)(S_ADDR + j - S_OFFSET));
        for (int k = 0; k < 16; k++) {
            printf(HEX_FORMAT, SH_HEX[j + k]);
            printf((k + 1) % 4 ? "" : " ");
        }
        printf(" ");
        for (int k = 0; k < 16; k++)
            printf(W_FORMAT(SH_HEX[j + k]), SH_HEX[j + k]);
        printf("\n");
    }
}

void print_objdump(t_objdump objdump)
{
    printf("\n%s:     file format %s-%s\n", NAME, EFORMAT,
        get_machine(objdump));
    printf("architecture: %s, flags 0x%08x:\n", get_arch(objdump), FLAGS);
    print_flags(objdump);
    printf("start address 0x%0*lx\n\n", IS_32 ? 8 : 16, SH_ENTRY);
    for (int i = 0; i < SH_NUM; i++) {
        if (!is_section(objdump, i))
            continue;
        printf("Contents of section %s:\n", SECTION_NAME);
        print_section(objdump, i);
    }
}
