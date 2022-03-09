/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** my_utils
*/

#include "my_nm.h"

int cmp_end(const char *s1, const char *s2)
{
    char *sub = strstr(s1, s2);
    int len_s1 = strlen(s1);
    int len_s2 = strlen(s2);
    int ret = 1;

    if (!IS_NULL(sub) && len_s1 >= len_s2)
        ret = strcmp(sub, &s1[len_s1 - len_s2]);
    return ret;
}

char *capitalize(char *str)
{
    for (int i = 0; str[i]; i++)
        str[i] -= (str[i] >= 'a' && str[i] <= 'z') ? 32 : 0;
    return str;
}

void delete_sub(const char *sub, char *trimmed)
{
    char *str = trimmed;
    int j = 0;

    for (size_t i = 0; i < strlen(trimmed); ++i)
        while (!strchr(sub, str[i]) && (trimmed[j++] = str[i++]));
    trimmed[j] = '\0';
}

int cmp_sym(const void *a, const void *b)
{
    char *s1_ptr = strdup(((t_sym)a)->name);
    char *s2_ptr = strdup(((t_sym)b)->name);
    char *s1 = capitalize(s1_ptr);
    char *s2 = capitalize(s2_ptr);
    int ret = 0;

    if (!IS_NULL(s1) && !IS_NULL(s2)) {
        delete_sub("_@.", s1);
        delete_sub("_@.", s2);
        ret = strcmp(s1, s2);
        if (ret == 0)
            ret = strcmp(((t_sym)a)->name, ((t_sym)b)->name);
        DESTROY(s1_ptr);
        DESTROY(s2_ptr);
    }
    return ret;
}

char *get_name(t_nm nm, char *name)
{
    int i = 0;
    int len = 0;

    if (name[i] == '/') {
        len = atoi(&name[i + 1]);
        if (len < nm->size) {
            DESTROY(name);
            name = strdup(&nm->names[len]);
        }
    }
    while (name[i] != '\0' && name[i] != '/')
        i++;
    name[i] = '\0';
    return name;
}
