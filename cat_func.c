#include "cat_func.h"
#include <bits/getopt_ext.h>

// functional code
void run_cat(int argc, char** argv) {
    // check if any arguments were used except application start
    if (argc > 1) {
        print_all_argv_except_app_name(argc, argv);
        printf("\n");
        check_if_file(argc, argv);
        printf("\n");
        main_cat(argc, argv);
    }
}

void main_cat(int argc, char** argv) {
    printf("!!!MAIN CAT STARTS!!!\n\n");
    check_if_file_functional(argc, argv);
    printf("<----------------------!!!MAIN CAT STOPPED!!!\n");
}

void check_if_file_functional(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if (file != NULL) {
            // print out the file here
            printer(file, argc, argv);
            fclose(file);
        }
        if (i < argc - 1) {
            printf("\n");
        }
    }
}

void printer(FILE* file, int argc, char** argv) {

    // b - нумерует только непустые строки
    // e - \n отображает как $
    // n - нумерует все строки
    // s - сжимает смежные пустые строки
    // t - отображает табы как ^I

    // initialize variables for the flags
    int number_non_empty_lines_bb = -1; // number-nonblank
    int show_dollar_ends_ee = -1;
    int number_all_lines_nn = -1;       // number
    int suppress_empty_lines_ss = -1;   // squeeze-blank
    int show_tabs_tt = -1;

    struct option long_opt[] = {
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank", 0, 0, 's'}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, ":benstET", long_opt, NULL)) != -1) {
        switch (opt) {
            case 'b':
                number_non_empty_lines_bb = 0;
                break;
            case 'e':
                show_dollar_ends_ee = 0;
                break;
            case 'n':
                number_all_lines_nn = 0;
                break;
            case 's':
                suppress_empty_lines_ss = 0;
                break;
            case 't':
                show_tabs_tt = 0;
                break;
            case 'E':
                show_dollar_ends_ee = 0;
                break;
            case 'T':
                show_tabs_tt = 0;
                break;
            case '?':
                break;
            default:
                break;
        }
    }

    char c;
    while ((c = fgetc(file)) != EOF) {
        printf("%c", c);
    }
}

// debug code
void print_all_argv_except_app_name(int argc, char** argv) {
    printf(CLR_MAGENTA_BRIGHT
           "--------------------------------------------\n!!!EXECUTING CODE TO PRINT OUT ALL THE INPUTTED "
           "ARGVs!!!\n\n");
    for (int i = 1; i < argc; i++) {
        printf("argv[%d] - %s\n", i, argv[i]);
    }
    printf("\n!!!PRINTED OUT ALL ARGVs!!!\n--------------------------------------------" CLR_RESET "\n");
}

void check_if_file(int argc, char** argv) {
    printf(
        CLR_BLUE_BRIGHT
        "--------------------------------------------\n!!!EXECUTING CODE TO CHECK IF ARGVs ARE FILES!!!\n\n");
    for (int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if (file != NULL) {
            printf("Yes, argv[%d] is a file and can be read\n", i);
            fclose(file);
        } else {
            printf(CLR_RED_BRIGHT "No, argv[%d] is NOT a file and can't be read\n" CLR_BLUE_BRIGHT, i);
        }
    }
    printf("\n!!!CHECKED ALL FILES!!!\n--------------------------------------------" CLR_RESET "\n");
}