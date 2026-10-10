#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "macro_handler.h"

char macro_names[50][50];
char macro_params[50][20];
char macro_values[50][100];
int macro_is_func[50];
int macro_count = 0;

void handle_define(char *line)
{
    char name[50], rest[100];
    if (sscanf(line, "#define %s %[^\n]", name, rest) != 2)
        return;

    char *paren = strchr(name, '(');
    if (paren)
    {
        *paren = '\0';
        strcpy(macro_names[macro_count], name);
        strcpy(macro_params[macro_count], paren + 1);
        char *close = strchr(macro_params[macro_count], ')');
        if (close)
            *close = '\0';
        strcpy(macro_values[macro_count], rest);
        macro_is_func[macro_count] = 1;
    }
    else
    {
        strcpy(macro_names[macro_count], name);
        macro_params[macro_count][0] = '\0';
        strcpy(macro_values[macro_count], rest);
        macro_is_func[macro_count] = 0;
    }
    macro_count++;
}