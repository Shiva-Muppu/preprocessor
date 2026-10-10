#ifndef MACRO_HANDLER_H
#define MACRO_HANDLER_H

void handle_define(char *line);
void replace_macros(char *line);

extern char macro_names[50][50];
extern char macro_params[50][20];
extern char macro_values[50][100];
extern int macro_is_func[50];
extern int macro_count;

#endif