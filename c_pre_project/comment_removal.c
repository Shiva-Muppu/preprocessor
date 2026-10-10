#include <stdio.h>
#include <string.h>
#include "comment_removal.h"

void remove_comments(char *line, int *in_comment)
{
    char result[1024];
    int i = 0, j = 0;

    while (line[i] != '\0')
    {
        if (*in_comment)
        {
            if (line[i] == '*' && line[i + 1] == '/')
            {
                *in_comment = 0;
                i += 2;
            }
            else
            {
                i++;
            }
        }
        else
        {
            if (line[i] == '/' && line[i + 1] == '/')
            {
                break;
            }
            else if (line[i] == '/' && line[i + 1] == '*')
            {
                *in_comment = 1;
                i += 2;
            }
            else
            {
                result[j++] = line[i++];
            }
        }
    }

    result[j] = '\0';
    strcpy(line, result);
}