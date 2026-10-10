#include <stdio.h>
#include <string.h>
#include "file_inclusion.h"

void handle_include(char *line, FILE *out) {
    char filename[100];
    if (sscanf(line, "#include <%[^>]>", filename) == 1) {
        FILE *inc = fopen(filename, "r");
        if (inc) {
            char buf[1024];
            while (fgets(buf, sizeof(buf), inc)) {
                fputs(buf, out);
            }
            fclose(inc);
        } else {
            fprintf(out, "/* Could not include %s */\n", filename);
        }
    }
}