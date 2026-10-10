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
    char name[50];
    char rest[100];
    int i = 0;
    int j = 0;
    int k = 0;

    /* Step 1: skip the word "#define" and any spaces after it */
    while (line[i] != '\0' && line[i] != ' ')
        i = i + 1;
    while (line[i] == ' ')
        i = i + 1;

    /* Step 2: read the macro name.
       A name ends at a space or at an opening parenthesis '(' */
    j = 0;
    while (line[i] != '\0' && line[i] != ' ' && line[i] != '(' && j < 49)
    {
        name[j] = line[i];
        j = j + 1;
        i = i + 1;
    }
    name[j] = '\0';

    /* If nothing was read, the line is not a valid #define */
    if (j == 0)
        return;

    /* Step 3: decide simple vs function-like macro */
    if (line[i] == '(')
    {
        /* Function-like macro: read parameters until ')' */
        i = i + 1;
        k = 0;
        while (line[i] != '\0' && line[i] != ')' && k < 19)
        {
            macro_params[macro_count][k] = line[i];
            k = k + 1;
            i = i + 1;
        }
        macro_params[macro_count][k] = '\0';
        if (line[i] == ')')
            i = i + 1;
        macro_is_func[macro_count] = 1;
    }
    else
    {
        /* Simple macro: no parameters */
        macro_params[macro_count][0] = '\0';
        macro_is_func[macro_count] = 0;
    }

    /* Step 4: skip spaces before the value */
    while (line[i] == ' ')
        i = i + 1;

    /* Step 5: read the replacement value (up to end of line) */
    k = 0;
    while (line[i] != '\0' && line[i] != '\n' && k < 99)
    {
        rest[k] = line[i];
        k = k + 1;
        i = i + 1;
    }
    rest[k] = '\0';

    /* Step 6: save everything into the global macro arrays */
    strcpy(macro_names[macro_count], name);
    strcpy(macro_values[macro_count], rest);

    macro_count = macro_count + 1;
}
