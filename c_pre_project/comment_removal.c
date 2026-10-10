#include <stdio.h>
#include <string.h>
#include "comment_removal.h"

/* Global flag.
   0 = not inside a comment
   1 = inside a multi-line comment */
int in_comment = 0;

void remove_comments(char *line)
{
    char result[1024];
    int i = 0;
    int j = 0;

    while (line[i] != '\0')
    {
        /* Case 1: we are already inside a multi-line comment */
        if (in_comment == 1)
        {
            /* Look for the closing marker: star followed by slash */
            if (line[i] == '*' && line[i + 1] == '/')
            {
                in_comment = 0;
                i = i + 2;
            }
            else
            {
                i = i + 1;
            }
        }
        /* Case 2: we are not inside any comment */
        else
        {
            /* Step 1: check for single-line comment first */
            if (line[i] == '/' && line[i + 1] == '/')
            {
                break;
            }
            /* Step 2: check for start of multi-line comment */
            else if (line[i] == '/' && line[i + 1] == '*')
            {
                in_comment = 1;
                i = i + 2;
            }
            /* Step 3: normal character, so keep it */
            else
            {
                result[j] = line[i];
                j = j + 1;
                i = i + 1;
            }
        }
    }

    result[j] = '\0';
    strcpy(line, result);
}
