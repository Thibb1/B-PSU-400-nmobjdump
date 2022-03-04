/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** my_symbol
*/

#include "my_nm.h"

void get_symbol_table(t_nm nm)
{
    SYMBOLS = NULL;
    if (IN_FILE(SHDR + 1) || IN_FILE(&SHDR[EHDR->e_shnum]))
        PRINT_ERROR(FORMAT);
    for (int i = 0; i < EHDR->e_shnum; i++) {
        if (SHDR[i].sh_type == SHT_SYMTAB)
            SYMBOLS = &SHDR[i];
    }
    ASSERT(!IS_NULL(SYMBOLS), "no symbols");
}

void get_symbol(t_nm nm, Elf64_Sym *s)
{
    if (s->st_info == STT_SECTION && s->st_shndx <= EHDR->e_shnum
        && s->st_name == 0)
        SYM[nm->i].name = SECTION_NAME;
    else
        SYM[nm->i].name = SYMBOL_NAME;
    SYM[nm->i].value = s->st_value;
    SYM[nm->i].type = get_type(nm, s);
    nm->i++;
}

void get_symbols(t_nm nm)
{
    Elf64_Sym *s = ((void *)EHDR + SYMBOLS->sh_offset);

    SYM = calloc(sizeof(struct s_sym), SYMBOLS->sh_size);
    ASSERT(!IS_NULL(SYM), "calloc failed");
    while ((void *)s < (void *)EHDR + SYMBOLS->sh_offset + SYMBOLS->sh_size) {
        if (s->st_name > 0 && s->st_info != STT_FILE)
            get_symbol(nm, s);
        s++;
    }
}

char get_local_type(t_nm nm, Elf64_Sym *s)
{
    char t = '?';
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

char get_type(t_nm nm, Elf64_Sym *s)
{
    char t = '?';
    Elf64_Section idx = s->st_shndx;

    ASSERT_VAL(ST_BIND == STB_GNU_UNIQUE, 'u');
    ASSERT_VAL(idx == SHN_UNDEF, 'U');
    ASSERT_VAL(idx == SHN_ABS, 'A');
    ASSERT_VAL(idx == SHN_COMMON, 'C');
    ASSERT_VAL(S_TYPE == SHT_NOBITS && S_FLAG == (SHF_ALLOC | SHF_WRITE), 'B');
    if (S_TYPE == SHT_PROGBITS) {
        ASSERT_VAL(S_FLAG == SHF_ALLOC, 'R');
        ASSERT_VAL(S_FLAG == (SHF_ALLOC | SHF_WRITE), 'D');
        ASSERT_VAL(S_FLAG == (SHF_ALLOC | SHF_EXECINSTR), 'T');
    }
    ASSERT_VAL(S_TYPE == SHT_DYNAMIC || S_TYPE == SHT_DYNSYM, 'D');
    ASSERT_VAL(ST_BIND == STB_WEAK, t == 'U' ? 'w' : 'W');
    ASSERT_VAL((t == 'w' || t == 'W') && ST_TYPE == STT_OBJECT, t - 1);
    ASSERT_VAL(t == '?', get_local_type(nm, s));
    ASSERT_VAL(t != '?' && ST_BIND == STB_LOCAL, t + 32);
    return t;
}
