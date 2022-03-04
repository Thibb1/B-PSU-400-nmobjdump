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
    return (str);
}

int cmp_sym(const void *a, const void *b)
{
    char *s1 = strdup(((t_sym)a)->name);
    char *s2 = strdup(((t_sym)b)->name);
    int ret = 0;
    char *s1_ptr = s1;
    char *s2_ptr = s2;

    if (!IS_NULL(s1) && !IS_NULL(s2)) {
        while (strchr("_@.", *s1) && *++s1);
        while (strchr("_@.", *s2) && *++s2);
        ret = strcmp(capitalize(s1), capitalize(s2));
        if (ret == 0)
            ret = strcmp(s2_ptr, s1_ptr);
    }
    DESTROY(s1_ptr);
    DESTROY(s2_ptr);
    return ret;
}
