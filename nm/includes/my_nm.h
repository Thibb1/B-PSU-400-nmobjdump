/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** my_nm
*/

#ifndef MY_NM_H_
    #define MY_NM_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <elf.h>
    #include <ar.h>
    #include <string.h>
    #include <sys/stat.h>

    #define FORMAT "file format not recognized"

    #define IS_NULL(x) ((x) == NULL)

    #define PRINT_ERROR(error) \
{ \
    printf("./my_nm: '%s': %s\n", nm->name, error); \
    destroy_nm(nm); \
    exit (84); \
}
    #define CHECK_FD \
if (IS_NULL(nm->fd)) { \
    PRINT_ERROR("No such file"); \
}

    #define ASSERT(assert, error) \
if (!(assert)) { \
    PRINT_ERROR(error); \
}

    #define ASSERT_VAL(assert, result) \
if (assert) { \
    t = (result); \
}

    #define DESTROY(ptr) \
{ \
    if (!IS_NULL(ptr)) \
        free(ptr); \
}
    #define EHDR (nm->ehdr)
    #define SHDR (nm->shdr)
    #define SBL (nm->symbols)
    #define EHDR_32 ((Elf32_Ehdr *)EHDR)
    #define SHDR_32 ((Elf32_Shdr *)SHDR)
    #define SBL_32 ((Elf32_Shdr *)SBL)

    #define SYM (nm->sym)
    #define ARCH (nm->arch)

    #define SYMBOL_PTR_32 ((char *)EHDR + SHDR_32[SBL_32->sh_link].sh_offset)
    #define SYMBOL_PTR \
    (ARCH == 32 ? SYMBOL_PTR_32 : (char *)EHDR + SHDR[SBL->sh_link].sh_offset)
    #define SECTION_PTR ((char *)EHDR + SHDR[EHDR->e_shstrndx].sh_offset)
    #define SECTION_PTR_32 \
    ((char *)EHDR + SHDR_32[EHDR_32->e_shstrndx].sh_offset)

    #define S_PTR ((Elf64_Sym *)ptr)
    #define S_PTR_32 ((Elf32_Sym *)ptr)

    #define S_PRINT (ARCH == 32 ? "%10c %s\n" : "%18c %s\n")
    #define S_PRINT_V (ARCH == 32 ? "%08lx %c %s\n" : "%016lx %c %s\n")
    #define S_IDX (ARCH == 32 ? S_PTR_32->st_shndx : S_PTR->st_shndx)
    #define S_FLAG \
    (ARCH == 32 ? SHDR_32[S_IDX].sh_flags : SHDR[S_IDX].sh_flags)
    #define S_TYPE (ARCH == 32 ? SHDR_32[S_IDX].sh_type : SHDR[S_IDX].sh_type)
    #define S_INF (ARCH == 32 ? S_PTR_32->st_info : S_PTR->st_info)
    #define S_OFFSET (ARCH == 32 ? SBL_32->sh_offset : SBL->sh_offset)
    #define S_ENTSIZE (ARCH == 32 ? SBL_32->sh_entsize : SBL->sh_entsize)
    #define S_SIZE (ARCH == 32 ? SBL_32->sh_size : SBL->sh_size)
    #define S_VAL (ARCH == 32 ? S_PTR_32->st_value : S_PTR->st_value)
    #define S_NAME (ARCH == 32 ? S_PTR_32->st_name : S_PTR->st_name)
    #define S_TAB ((void *)EHDR + S_OFFSET)
    #define ST_BIND (ARCH == 32 ? ELF32_ST_BIND(S_INF) : ELF64_ST_BIND(S_INF))
    #define ST_TYPE (ARCH == 32 ? ELF32_ST_TYPE(S_INF) : ELF64_ST_TYPE(S_INF))
    #define SYMBOL_NAME (&SYMBOL_PTR[S_NAME])
    #define SECTION_NAME (ARCH == 32 ? \
    &SECTION_PTR_32[SHDR_32[S_IDX].sh_name] : \
    &SECTION_PTR[SHDR[S_IDX].sh_name])


    #define SYMBOL_CMP(str) (!strcmp((str), SYMBOL_NAME))

    #define IN_FILE(ptr) ((void *)(ptr) > (void *)((void *)EHDR + nm->size))
    #define IN_SHDR (!IN_FILE(SHDR + 1) && !IN_FILE(&SHDR[EHDR->e_shnum]))
    #define IN_SHDR_32 \
    (!IN_FILE(EHDR_32 + 1) && !IN_FILE(&EHDR_32[EHDR_32->e_shnum]))

typedef struct s_nm *t_nm;

typedef struct s_sym *t_sym;

struct s_sym
{
    Elf64_Addr value;
    char *name;
    char type;
};

struct s_nm
{
    char *name;
    FILE *fd;
    int is_relocatable;
    int i;
    int arch;
    off_t size;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
    Elf64_Shdr *symbols;
    t_sym sym;
};

// symbols
void get_symbol_table(t_nm);
void get_symbol(t_nm, void *);
void get_symbols(t_nm);
char get_local_type(t_nm, void *, char);
char get_type(t_nm, void *);

// nm
void destroy_nm(t_nm);
t_nm init_nm(const char *);
void print_nm(t_nm);
int my_nm(const char *, const int);

// utils
int cmp_end(const char *, const char *);
char *capitalize(char *);
int cmp_sym(const void *, const void *);

// efl
off_t get_size(t_nm);
void get_ehdr(t_nm);
void get_shdr(t_nm);
void relocatable_file(t_nm);

#endif /* !MY_NM_H_ */
