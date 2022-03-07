/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** my_objdump
*/

#include "my_objdump.h"

void clean_objdump(t_objdump objdump)
{
    if (IS_NULL(objdump))
        return;
    DESTROY(NAME);
    DESTROY(EHDR);
    DESTROY(HDR);
}

void destroy_objdump(t_objdump objdump)
{
    if (IS_NULL(objdump))
        return;
    if (!IS_NULL(objdump->fd))
        fclose(objdump->fd);
    clean_objdump(objdump);
    DESTROY(objdump->names);
    DESTROY(objdump);
}

t_objdump init_objdump(const char *filename)
{
    t_objdump objdump = calloc(1, sizeof(struct s_objdump));

    if (IS_NULL(objdump)) {
        printf("./my_objdump: '%s': %s\n", filename, "Out of memory");
        exit (84);
    }
    objdump->fd = fopen(filename, "r");
    NAME = strdup(filename);
    return objdump;
}

int is_section(t_objdump objdump, int i)
{
    R_ASSERT_V(S_SIZE, 0);
    R_ASSERT_V(SECTION_NAME, 0);
    R_ASSERT_V(SECTION_STR(".bss"), 0);
    R_ASSERT_V(SECTION_STR(".shstrtab"), 0);
    R_ASSERT_V(SECTION_STR(".symtab"), 0);
    R_ASSERT_V(SECTION_STR(".strtab"), 0);
    R_ASSERT_V(SECTION_STR(".rela.text"), 0);
    R_ASSERT_V(SECTION_STR(".rela.data"), 0);
    R_ASSERT_V(SECTION_STR(".rela.debug_info"), 0);
    R_ASSERT_V(SECTION_STR(".rela.debug_line"), 0);
    R_ASSERT_V(SECTION_STR(".rela.debug_aranges"), 0);
    R_ASSERT_V(SECTION_STR(".rela.eh_frame"), 0);
    R_ASSERT_V(SECTION_STR(".tbss"), 0);
    R_ASSERT_V(SECTION_STR("__libc_freeres_ptrs"), 0);
    return 1;
}

int my_objdump(const char *filename)
{
    t_objdump objdump = init_objdump(filename);

    CHECK_FD;
    ar_file(objdump);
    R_ASSERT_V(!objdump->is_ar, 0);
    objdump->size = get_size(objdump);
    get_ehdr(objdump);
    get_shdr(objdump);
    print_objdump(objdump);
    destroy_objdump(objdump);
    return 0;
}
