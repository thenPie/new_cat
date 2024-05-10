#ifndef CAT_FUNC_H
#define CAT_FUNC_H

#include <stdio.h>
#include <getopt.h>

// fancy colourful text
#define CLR_RED "\x1b[31m"
#define CLR_GREEN "\x1b[32m"
#define CLR_YELLOW "\x1b[33m"
#define CLR_BLUE "\x1b[34m"
#define CLR_MAGENTA "\x1b[35m"
#define CLR_CYAN "\x1b[36m"
#define CLR_WHITE "\x1b[37m"

#define CLR_RED_BRIGHT "\x1b[31m"
#define CLR_GREEN_BRIGHT "\x1b[32m"
#define CLR_YELLOW_BRIGHT "\x1b[33m"
#define CLR_BLUE_BRIGHT "\x1b[34m"
#define CLR_MAGENTA_BRIGHT "\x1b[35m"
#define CLR_CYAN_BRIGHT "\x1b[36m"
#define CLR_WHITE_BRIGHT "\x1b[37m"

#define CLR_RESET "\x1b[0m"

// fancy bckgrnd for text
#define BCKGRND_BLACK "\x1b[40m"
#define BCKGRND_RED "\x1b[41m"
#define BCKGRND_GREEN "\x1b[42m"
#define BCKGRND_YELLOW "\x1b[43m"
#define BCKGRND_BLUE "\x1b[44m"
#define BCKGRND_MAGENTA "\x1b[45m"
#define BCKGRND_CYAN "\x1b[46m"
#define BCKGRND_WHITE "\x1b[47m"

#define BCKGRND_RESET "\x1b[49m"

// functional code
void run_cat(int argc, char** argv);
void main_cat(int argc, char** argv);
void check_if_file_functional(int argc, char** argv);
int count_rdbl_files(int argc, char** argv);
void printer(char** argv, FILE* file, int b, int e, int n, int s, int t);

// debug code
void print_all_argv_except_app_name(int argc, char** argv);
void check_if_file(int argc, char** argv);
void what_opt(int opt);

#endif