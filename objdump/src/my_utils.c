/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** my_utils
*/

#include "my_objdump.h"

char *get_name(t_objdump objdump, char *name)
{
    int i = 0;
    int len = 0;

    if (name[i] == '/') {
        len = atoi(&name[i + 1]);
        if (len < objdump->size) {
            DESTROY(name);
            name = strdup(&objdump->names[len]);
        }
    }
    while (name[i] != '\0' && name[i] != '/')
        i++;
    name[i] = '\0';
    return name;
}

const char *get_machine(t_objdump objdump)
{
    if (MACHINE == EM_386)
        return "i386";
    else if (MACHINE == EM_X86_64)
        return "x86-64";
    return ENDIAN == ELFDATA2LSB ? "little" : "big";
}

const char *get_arch(t_objdump objdump)
{
    if (MACHINE == EM_386)
        return "i386";
    else if (MACHINE == EM_X86_64)
        return "i386:x86-64";
    return "UNKNOWN!";
}
