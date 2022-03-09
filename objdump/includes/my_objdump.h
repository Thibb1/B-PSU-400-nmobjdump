/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** my_objdump
*/

#ifndef MY_OBJDUMP_H_
    #define MY_OBJDUMP_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <elf.h>
    #include <ar.h>
    #include <string.h>
    #include <sys/stat.h>

    #define FORMAT "file format not recognized"

    #define IS_NULL(x) ((x) == NULL)

    #define PRINT_ERROR(error) { \
        printf("./my_objdump: '%s': %s\n", objdump->name, error); \
        destroy_objdump(objdump); \
        exit(84); \
    }

    #define CHECK_FD \
    if (IS_NULL(objdump->fd)) { \
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
        return val; \
    }

    #define R_ASSERT(assert) \
    if (!(assert)) { \
        return; \
    }

    #define DESTROY(ptr) \
    if (!IS_NULL(ptr)) {\
        free(ptr); \
        ptr = NULL; \
    }

    #define NAME (objdump->name)
    #define EHDR (objdump->ehdr)
    #define SHDR (objdump->shdr)
    #define HDR (objdump->hdr)
    #define EHDR_32 ((Elf32_Ehdr *)EHDR)
    #define SHDR_32 ((Elf32_Shdr *)SHDR)

    #define ST_AR_SIZE (sizeof(struct ar_hdr))

    #define ARCH (objdump->arch)

    #define IS_32 (ARCH == 32)
    #define EFORMAT (IS_32 ? "elf32" : "elf64")

    #define MACHINE (IS_32 ? EHDR_32->e_machine : EHDR->e_machine)
    #define ENDIAN (IS_32 ? EHDR_32->e_ident[EI_DATA] : EHDR->e_ident[EI_DATA])
    #define SH_FLAG (IS_32 ? EHDR_32->e_flags : EHDR->e_flags)
    #define SH_TYPE (IS_32 ? EHDR_32->e_type : EHDR->e_type)
    #define SH_ENT (IS_32 ? EHDR_32->e_shentsize : EHDR->e_shentsize)
    #define SH_NUM (IS_32 ? EHDR_32->e_shnum : EHDR->e_shnum)
    #define SH_STR (IS_32 ? EHDR_32->e_shstrndx : EHDR->e_shstrndx)
    #define SH_ENTRY (IS_32 ? EHDR_32->e_entry : EHDR->e_entry)
    #define SH_HEX (IS_32 ? (unsigned char *)EHDR_32 : (unsigned char *)EHDR)


    #define FLAGS (SH_TYPE == ET_EXEC ? 274 : \
    SH_TYPE == ET_DYN ? 336 : \
    SH_TYPE == ET_REL ? 17 : SH_FLAG)

    #define HAS_RELOC (FLAGS & 0x01)
    #define EXEC_P (FLAGS & 0x02)
    #define HAS_LINENO (FLAGS & 0x04)
    #define HAS_DEBUG (FLAGS & 0x08)
    #define HAS_SYMS (FLAGS & 0x10)
    #define HAS_LOCALS (FLAGS & 0x20)
    #define DYNAMIC (FLAGS & 0x40)
    #define WP_TEXT (FLAGS & 0x80)
    #define D_PAGED (FLAGS & 0x100)
    #define BFD_IS_RELAX (FLAGS & 0x200)
    #define HAS_LOAD_PAGE (FLAGS & 0x1000)

    #define F_EXEC_P (i && EXEC_P ? ", EXEC_P" : "%s")
    #define F_HAS_LINENO (i && HAS_LINENO ? ", HAS_LINENO" : "%s")
    #define F_HAS_DEBUG (i && HAS_DEBUG ? ", HAS_DEBUG" : "%s")
    #define F_HAS_SYMS (i && HAS_SYMS ? ", HAS_SYMS" : "%s")
    #define F_HAS_LOCALS (i && HAS_LOCALS ? ", HAS_LOCALS" : "%s")
    #define F_DYNAMIC (i && DYNAMIC ? ", DYNAMIC" : "%s")
    #define F_WP_TEXT (i && WP_TEXT ? ", WP_TEXT" : "%s")
    #define F_D_PAGED (i && D_PAGED ? ", D_PAGED" : "%s")
    #define F_BFD_IS_RELAX (i && BFD_IS_RELAX ? ", BFD_IS_RELAXABLE" : "%s")
    #define F_HAS_LOAD_PAGE (i && HAS_LOAD_PAGE ? ", HAS_LOAD_PAGE" : "%s")

    #define SECTION_PTR_32 ((char *)EHDR + SHDR_32[SH_STR].sh_offset)
    #define SECTION_PTR \
    (IS_32 ? SECTION_PTR_32 : (char *)EHDR + SHDR[SH_STR].sh_offset)


    #define SHDR_SIZE (IS_32 ? sizeof(Elf32_Shdr) : sizeof(Elf64_Shdr))

    #define S_PRINT (IS_32 ? "%10c %s\n" : "%18c %s\n")
    #define S_PRINT_V (IS_32 ? "%08lx %c %s\n" : "%016lx %c %s\n")

    #define S_NAME (IS_32 ? SHDR_32[i].sh_name : SHDR[i].sh_name)
    #define S_SIZE (IS_32 ? SHDR_32[i].sh_size : SHDR[i].sh_size)
    #define S_OFFSET (IS_32 ? SHDR_32[i].sh_offset : SHDR[i].sh_offset)
    #define S_ADDR (IS_32 ? SHDR_32[i].sh_addr : SHDR[i].sh_addr)
    #define IN_SECTION (j + k < S_OFFSET + S_SIZE)
    #define HEX_FORMAT (!IN_SECTION ? "  " : "%02x")
    #define W_FORMAT(c) (!IN_SECTION ? " " : \
    c < 32 || c > 126 ? "." : "%c")


    #define SECTION_NAME (&SECTION_PTR[S_NAME])

    #define SECTION_STR(str) (!strstr(SECTION_NAME, str))

typedef struct s_objdump *t_objdump;

struct s_objdump
{
    char *name;
    FILE *fd;
    int is_ar;
    struct ar_hdr *hdr;
    char *names;
    int arch;
    off_t size;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
};

// print
void print_flags(t_objdump);
void print_section(t_objdump, int);
void print_objdump(t_objdump);

// objdump
void clean_objdump(t_objdump);
void destroy_objdump(t_objdump);
t_objdump init_objdump(const char *);
int is_section(t_objdump, int);
int my_objdump(const char *);

// utils
char *get_name(t_objdump, char *);
const char *get_machine(t_objdump);
const char *get_arch(t_objdump);

// efl
off_t get_size(t_objdump);
void get_ehdr(t_objdump);
void get_shdr(t_objdump);
int get_ar(t_objdump, int);
void ar_file(t_objdump);

#endif /* !MY_OBJDUMP_H_ */
