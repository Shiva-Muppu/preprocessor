#include <stdio.h>
#include <string.h>
#include "comment_removal.h"
#include "macro_handler.h"
#include "macro_replace.h"
#include "file_inclusion.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s inputfile.c\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    char output[256];
    strcpy(output, input);
    char *dot = strrchr(output, '.');
    if (dot)
        strcpy(dot, ".i");
    else
        strcat(output, ".i");

    FILE *in = fopen(input, "r");
    FILE *out = fopen(output, "w");
    if (!in || !out)
    {
        printf("Error opening files.\n");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), in))
    {
        remove_comments(line);
        if (strlen(line) == 0)
            continue;

        if (strstr(line, "#include"))
        {
            handle_include(line, out);
        }
        else if (strstr(line, "#define"))
        {
            handle_define(line);
        }
        else
        {
            replace_macros(line);
            fputs(line, out);
        }
    }

    fclose(in);
    fclose(out);
    printf("Preprocessing complete: %s\n", output);
    return 0;
}
