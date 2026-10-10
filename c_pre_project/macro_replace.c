#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "macro_replace.h"
#include "macro_handler.h"

/* Try to match a function-like macro at position p.
   Returns the number of characters consumed,
   or 0 if no function-like macro matched. */
static int try_func_macro(char *p, char *out)
{
    int i;
    int len;
    int j;
    int k;
    int o;
    int m;
    int plen;
    char arg[100];

    for (i = 0; i < macro_count; i++)
    {
        if (macro_is_func[i] == 0)
            continue;

        len = strlen(macro_names[i]);

        /* Check if the macro name matches */
        if (strncmp(p, macro_names[i], len) != 0)
            continue;

        /* The next character must be '(' */
        if (p[len] != '(')
            continue;

        /* Read the argument inside the parentheses */
        j = 0;
        k = len + 1;
        while (p[k] != '\0' && p[k] != ')' && j < 99)
        {
            arg[j] = p[k];
            j = j + 1;
            k = k + 1;
        }
        if (p[k] != ')')
            continue;
        arg[j] = '\0';
        k = k + 1;

        /* Copy the macro value into out, replacing the parameter with arg */
        o = strlen(out);
        m = 0;
        while (macro_values[i][m] != '\0')
        {
            plen = strlen(macro_params[i]);

            if (plen > 0 &&
                strncmp(&macro_values[i][m], macro_params[i], plen) == 0 &&
                (m == 0 || (isalnum(macro_values[i][m - 1]) == 0 &&
                            macro_values[i][m - 1] != '_')))
            {
                strcpy(&out[o], arg);
                o = o + strlen(arg);
                m = m + plen - 1;
            }
            else
            {
                out[o] = macro_values[i][m];
                o = o + 1;
            }
            m = m + 1;
        }
        out[o] = '\0';

        return k;
    }

    return 0;
}

void replace_macros(char *line)
{
    char result[1024];
    char *p;
    int used;
    int matched;
    int i;
    int len;

    result[0] = '\0';
    p = line;

    while (*p != '\0')
    {
        /* First try to match a function-like macro */
        used = try_func_macro(p, result);
        if (used > 0)
        {
            p = p + used;
            continue;
        }

        /* Then try to match a simple (object-like) macro */
        matched = 0;
        for (i = 0; i < macro_count; i++)
        {
            if (macro_is_func[i] == 1)
                continue;

            len = strlen(macro_names[i]);

            if (strncmp(p, macro_names[i], len) == 0 &&
                isalnum(p[len]) == 0 && p[len] != '_')
            {
                strcat(result, macro_values[i]);
                p = p + len;
                matched = 1;
                break;
            }
        }

        /* If no macro matched, copy the current character */
        if (matched == 0)
        {
            len = strlen(result);
            result[len] = *p;
            result[len + 1] = '\0';
            p = p + 1;
        }
    }

    strcpy(line, result);
}
