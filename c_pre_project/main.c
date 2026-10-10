#include <stdio.h>
#include <string.h>
#include "comment_removal.h"
#include "macro_handler.h"
#include "macro_replace.h"
#include "file_inclusion.h"

int main(int argc, char *argv[])
{
    char *input;
    char output[256];
    char *dot;
    FILE *in;
    FILE *out;
    char line[1024];

    if (argc != 2)
    {
        printf("Usage: %s inputfile.c\n", argv[0]);
        return 1;
    }

    input = argv[1];

    /* Build the output filename: replace the extension with .i */
    strcpy(output, input);
    dot = strrchr(output, '.');
    if (dot != NULL)
        strcpy(dot, ".i");
    else
        strcat(output, ".i");

    in = fopen(input, "r");
    if (in == NULL)
    {
        printf("Error: could not open input file %s\n", input);
        return 1;
    }

    out = fopen(output, "w");
    if (out == NULL)
    {
        printf("Error: could not create output file %s\n", output);
        fclose(in);
        return 1;
    }

    while (fgets(line, sizeof(line), in) != NULL)
    {
        remove_comments(line);

        if (strlen(line) == 0)
            continue;

        if (strstr(line, "#include") != NULL)
        {
            handle_include(line, out);
        }
        else if (strstr(line, "#define") != NULL)
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
