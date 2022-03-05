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

    #define R_ASSERT_V(assert, val)  \
if (!(assert)) { \
    return (val); \
}

    #define R_ASSERT(assert) \
if (!(assert)) { \
    return; \
}

    #define DESTROY(ptr) \
{ \
    if (!IS_NULL(ptr)) {\
        free(ptr); \
        ptr = NULL; \
    } \
}
    #define EHDR (nm->ehdr)
    #define SHDR (nm->shdr)
    #define SBL (nm->symbols)
    #define HDR (nm->hdr)
    #define EHDR_32 ((Elf32_Ehdr *)EHDR)
    #define SHDR_32 ((Elf32_Shdr *)SHDR)
    #define SBL_32 ((Elf32_Shdr *)SBL)

    #define ST_AR_SIZE (sizeof(struct ar_hdr))

    #define SYM (nm->sym)
    #define ARCH (nm->arch)

    #define IS_32 (ARCH == 32)

    #define SYMBOL_PTR_32 ((char *)EHDR + SHDR_32[SBL_32->sh_link].sh_offset)
    #define SYMBOL_PTR \
    (IS_32 ? SYMBOL_PTR_32 : (char *)EHDR + SHDR[SBL->sh_link].sh_offset)

    #define SH_ENT (IS_32 ? EHDR_32->e_shentsize : EHDR->e_shentsize)
    #define SH_NUM (IS_32 ? EHDR_32->e_shnum : EHDR->e_shnum)
    #define SH_STR (IS_32 ? EHDR_32->e_shstrndx : EHDR->e_shstrndx)

    #define SECTION_PTR_32 ((char *)EHDR + SHDR_32[SH_STR].sh_offset)
    #define SECTION_PTR \
    (IS_32 ? SECTION_PTR_32 : (char *)EHDR + SHDR[SH_STR].sh_offset)

    #define S_PTR ((Elf64_Sym *)ptr)
    #define S_PTR_32 ((Elf32_Sym *)ptr)

    #define SHDR_SIZE (IS_32 ? sizeof(Elf32_Shdr) : sizeof(Elf64_Shdr))

    #define S_PRINT (IS_32 ? "%10c %s\n" : "%18c %s\n")
    #define S_PRINT_V (IS_32 ? "%08lx %c %s\n" : "%016lx %c %s\n")

    #define S_IDX (IS_32 ? S_PTR_32->st_shndx : S_PTR->st_shndx)
    #define S_FLAG (IS_32 ? SHDR_32[S_IDX].sh_flags : SHDR[S_IDX].sh_flags)
    #define S_TYPE (IS_32 ? SHDR_32[S_IDX].sh_type : SHDR[S_IDX].sh_type)
    #define S_INF (IS_32 ? S_PTR_32->st_info : S_PTR->st_info)
    #define S_OFFSET (IS_32 ? SBL_32->sh_offset : SBL->sh_offset)
    #define S_ENTSIZE (IS_32 ? SBL_32->sh_entsize : SBL->sh_entsize)
    #define S_SIZE (IS_32 ? SBL_32->sh_size : SBL->sh_size)
    #define S_VAL (IS_32 ? S_PTR_32->st_value : S_PTR->st_value)
    #define S_VAL_S (IS_32 ? S_PTR_32->st_size : S_PTR->st_size)
    #define S_NAME (IS_32 ? S_PTR_32->st_name : S_PTR->st_name)
    #define S_TAB ((void *)EHDR + S_OFFSET)
    #define ST_BIND (IS_32 ? ELF32_ST_BIND(S_INF) : ELF64_ST_BIND(S_INF))
    #define ST_TYPE (IS_32 ? ELF32_ST_TYPE(S_INF) : ELF64_ST_TYPE(S_INF))
    #define SYMBOL_NAME (&SYMBOL_PTR[S_NAME])
    #define SECTION_NAME (&SECTION_PTR[SHDR[S_IDX].sh_name])


    #define SYMBOL_CMP(str) (!strcmp((str), SYMBOL_NAME))
    #define SYMBOL_WEAK(c) (strchr("Uwv?", c) != NULL)

    #define IN_FILE(ptr) ((void *)(ptr) > (void *)((void *)EHDR + nm->size))
    #define IN_SHDR (!IN_FILE(SHDR + 1) && !IN_FILE(&SHDR[SH_NUM]))
    #define IN_SHDR_32 (!IN_FILE(SHDR_32 + 1) && !IN_FILE(&SHDR_32[SH_NUM]))

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
    int is_ar;
    struct ar_hdr *hdr;
    char *names;
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
void clean_nm(t_nm nm);
void destroy_nm(t_nm);
t_nm init_nm(const char *);
void print_nm(t_nm);
int my_nm(const char *, const int);

// utils
int cmp_end(const char *, const char *);
char *capitalize(char *);
void delete_sub(const char *, char *);
int cmp_sym(const void *, const void *);
char *get_name(t_nm, char *);

// efl
off_t get_size(t_nm);
void get_ehdr(t_nm);
void get_shdr(t_nm);
int get_ar(t_nm, int);
void ar_file(t_nm);
#endif /* !MY_NM_H_ */
