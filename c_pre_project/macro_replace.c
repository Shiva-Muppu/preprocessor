#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "macro_replace.h"
#include "macro_handler.h"

static int try_func_macro(char *p, char *out)
{
    for (int i = 0; i < macro_count; i++)
    {
        if (!macro_is_func[i])
            continue;
        int len = strlen(macro_names[i]);
        if (strncmp(p, macro_names[i], len) != 0)
            continue;
        if (p[len] != '(')
            continue;

        char arg[100];
        int j = 0, k = len + 1;
        while (p[k] && p[k] != ')' && j < 99)
            arg[j++] = p[k++];
        if (p[k] != ')')
            continue;
        arg[j] = '\0';
        k++;

        int o = strlen(out);
        for (int m = 0; macro_values[i][m]; m++)
        {
            int plen = strlen(macro_params[i]);
            if (plen > 0 &&
                strncmp(&macro_values[i][m], macro_params[i], plen) == 0 &&
                (m == 0 || (!isalnum(macro_values[i][m - 1]) && macro_values[i][m - 1] != '_')))
            {
                strcpy(&out[o], arg);
                o += strlen(arg);
                m += plen - 1;
            }
            else
                out[o++] = macro_values[i][m];
        }
        out[o] = '\0';
        return k;
    }
    return 0;
}

void replace_macros(char *line)
{
    char result[1024] = "";
    char *p = line;
    while (*p)
    {
        int used = try_func_macro(p, result);
        if (used > 0)
        {
            p += used;
            continue;
        }
        int matched = 0;
        for (int i = 0; i < macro_count; i++)
        {
            if (macro_is_func[i])
                continue;
            int len = strlen(macro_names[i]);
            if (strncmp(p, macro_names[i], len) == 0 &&
                !isalnum(p[len]) && p[len] != '_')
            {
                strcat(result, macro_values[i]);
                p += len;
                matched = 1;
                break;
            }
        }
        if (!matched)
        {
            int len = strlen(result);
            result[len] = *p++;
            result[len + 1] = '\0';
        }
    }
    strcpy(line, result);
}