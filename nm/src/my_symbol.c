/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** my_symbol
*/

#include "my_nm.h"

void get_symbol_table(t_nm nm)
{
    void *ptr = ((void *)SHDR);
    void *ptr_end = ((void *)SHDR + SH_NUM * SH_ENT);

    SBL = NULL;
    ASSERT(IS_32 || IN_SHDR, FORMAT);
    ASSERT(!IS_32 || IN_SHDR_32, FORMAT);
    while (ptr < ptr_end) {
        if ((IS_32 && ((Elf32_Shdr *)ptr)->sh_type == SHT_SYMTAB)
            || (!IS_32 && ((Elf64_Shdr *)ptr)->sh_type == SHT_SYMTAB))
            SBL = (Elf64_Shdr *)ptr;
        ptr += SHDR_SIZE;
    }
    ASSERT(!IS_NULL(SBL), "no symbols");
}

void get_symbol(t_nm nm, void *ptr)
{
    if (S_INF == STT_SECTION && S_IDX <= EHDR->e_shnum && S_NAME == 0)
        SYM[nm->i].name = SECTION_NAME;
    else
        SYM[nm->i].name = SYMBOL_NAME;
    SYM[nm->i].type = get_type(nm, ptr);
    SYM[nm->i].value = (Elf64_Addr)S_VAL;
    SYM[nm->i].value += SYM[nm->i].value ? 0 : (Elf64_Addr)S_VAL_S;
    nm->i++;
}

void get_symbols(t_nm nm)
{
    void *ptr = S_TAB;
    void *ptr_2 = S_TAB + S_SIZE;

    SYM = calloc(sizeof(struct s_sym), S_SIZE);
    ASSERT(!IS_NULL(SYM), "calloc failed");
    while (ptr < ptr_2) {
        if (S_NAME > 0 && S_INF != STT_FILE)
            get_symbol(nm, ptr);
        ptr += S_ENTSIZE;
    }
}

char get_local_type(t_nm nm, void *ptr, char t)
{
    ASSERT_VAL(SYMBOL_CMP(".bss"), 'B');
    ASSERT_VAL(SYMBOL_CMP(".debug"), 'N');
    ASSERT_VAL(SYMBOL_CMP("__abi_tag") || SYMBOL_CMP(".rodata")
        || SYMBOL_CMP(".eh_frame"), 'R');
    ASSERT_VAL(!cmp_end(SYMBOL_NAME, "_array_entry") || SYMBOL_CMP(".jcr")
        || SYMBOL_CMP(".dynamic") || SYMBOL_CMP(".data")
        || SYMBOL_CMP(".got.plt"), 'D');
    ASSERT_VAL(SYMBOL_CMP(".init_array") || SYMBOL_CMP(".fini_array") ||
        SYMBOL_CMP(".plt") || SYMBOL_CMP(".fini") || SYMBOL_CMP(".init") ||
        SYMBOL_CMP(".text") || SYMBOL_CMP(".init"), 'T');
    return t;
}

char get_type(t_nm nm, void *ptr)
{
    char t = '?';

    ASSERT_VAL(ST_BIND == STB_GNU_UNIQUE, 'u');
    ASSERT_VAL(S_IDX == SHN_UNDEF, 'U');
    ASSERT_VAL(S_IDX == SHN_ABS, 'A');
    ASSERT_VAL(S_IDX == SHN_COMMON, 'C');
    ASSERT_VAL(S_TYPE == SHT_NOBITS && S_FLAG == (SHF_ALLOC | SHF_WRITE), 'B');
    if (S_TYPE == SHT_PROGBITS) {
        ASSERT_VAL(S_FLAG == SHF_ALLOC, 'R');
        ASSERT_VAL(S_FLAG == (SHF_ALLOC | SHF_WRITE), 'D');
        ASSERT_VAL(S_FLAG == (SHF_ALLOC | SHF_EXECINSTR), 'T');
    }
    ASSERT_VAL(S_TYPE == SHT_DYNAMIC || S_TYPE == SHT_DYNSYM, 'D');
    ASSERT_VAL(ST_BIND == STB_WEAK, t == 'U' ? 'w' : 'W');
    ASSERT_VAL((t == 'w' || t == 'W') && ST_TYPE == STT_OBJECT, t - 1);
    ASSERT_VAL(t == '?', get_local_type(nm, ptr, t));
    ASSERT_VAL(t != '?' && ST_BIND == STB_LOCAL, t + 32);
    return t;
}
