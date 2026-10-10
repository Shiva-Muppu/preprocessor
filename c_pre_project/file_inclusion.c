#include <stdio.h>
#include <string.h>
#include "file_inclusion.h"

void handle_include(char *line, FILE *out)
{
    char filename[100];
    int i = 0;
    int j = 0;
    int found_open = 0;
    int found_close = 0;
    FILE *inc;
    char buf[1024];

    /* Step 1: find the '<' character */
    while (line[i] != '\0' && line[i] != '<')
        i = i + 1;

    if (line[i] == '<')
    {
        found_open = 1;
        i = i + 1;

        /* Step 2: read the filename between '<' and '>' */
        while (line[i] != '\0' && line[i] != '>' && j < 99)
        {
            filename[j] = line[i];
            j = j + 1;
            i = i + 1;
        }
        filename[j] = '\0';

        if (line[i] == '>')
            found_close = 1;
    }

    /* Step 3: if the syntax was valid, open and copy the file */
    if (found_open == 1 && found_close == 1)
    {
        inc = fopen(filename, "r");
        if (inc != NULL)
        {
            while (fgets(buf, sizeof(buf), inc) != NULL)
            {
                fputs(buf, out);
            }
            fclose(inc);
        }
        else
        {
            fprintf(out, "/* Could not include %s */\n", filename);
        }
    }
}
