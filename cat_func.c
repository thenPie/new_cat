#include "cat_func.h"
#include <getopt.h>
#include <stdio.h>

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
    printf("!!!MAIN CAT STARTS!!!\n\n--------------------------------------------\n");
    check_if_file_functional(argc, argv);
    printf("<----------------------!!!MAIN CAT STOPPED!!!\n");
}

void check_if_file_functional(int argc, char** argv) {

    //amount of readable files
    int readable_files = count_rdbl_files(argc, argv);

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
    // TODO: ignores wrong options for now, need to ask around!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    while ((opt = getopt_long(argc, argv, ":benstET", long_opt, NULL)) != -1) {
        switch (opt) {
            case 'b':
                what_opt(opt);
                number_non_empty_lines_bb = 0;
                break;
            case 'e':
                what_opt(opt);
                show_dollar_ends_ee = 0;
                break;
            case 'n':
                what_opt(opt);
                number_all_lines_nn = 0;
                break;
            case 's':
                what_opt(opt);
                suppress_empty_lines_ss = 0;
                break;
            case 't':
                what_opt(opt);
                show_tabs_tt = 0;
                break;
            case 'E':
                what_opt(opt);
                show_dollar_ends_ee = 0;
                break;
            case 'T':
                what_opt(opt);
                show_tabs_tt = 0;
                break;
            case '?':
                break;
            default:
                break;
        }
    }

    int amount_of_opened = 0;
    for (int i = 1; i < argc; i++) {
        int no_file = 0;
        FILE* file = fopen(argv[i], "r");
        if (file != NULL) {
            // print out the file here
            printer(argv, file, number_non_empty_lines_bb, show_dollar_ends_ee, number_all_lines_nn, suppress_empty_lines_ss, show_tabs_tt);
            fclose(file);
            no_file = -1;
            amount_of_opened++;
        }
        if (no_file == -1 && amount_of_opened < readable_files) {
            printf("\n");
        }
    }
}

int count_rdbl_files(int argc, char** argv) {
    int rdbl_files = 0;
    for (int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if (file != NULL) {
            rdbl_files++;
            fclose(file);
        }
    }
    return rdbl_files;
}

void printer(char** argv, FILE* file, int b, int e, int n, int s, int t) {

    // b - нумерует только непустые строки
    // e - \n отображает как $
    // n - нумерует все строки
    // s - сжимает смежные пустые строки
    // t - отображает табы как ^I

    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == EOF && e == 0) {
            printf("$");
        }

        if (e == 0 && c == '\n') {
            c = '$';
        }

        if (t == 0 && c == '	') {
            c = '^';
        }

        if (c == '$') {
            printf("%c\n", c);
        } else if (c == '^') {
            printf("%cI", c);
        } else {
            printf("%c", c);
        }
    }
    if (e == 0 && c == EOF) {
        printf("$");
    }
}

// debug code
void print_all_argv_except_app_name(int argc, char** argv) {
    printf(CLR_GREEN_BRIGHT
           "--------------------------------------------\n!!!EXECUTING CODE TO PRINT OUT ALL THE INPUTTED "
           "ARGVs!!!\n\n");
    for (int i = 1; i < argc; i++) {
        printf("argv[%d] - %s\n", i, argv[i]);
    }
    printf("\n!!!PRINTED OUT ALL ARGVs!!!\n--------------------------------------------" CLR_RESET "\n");
}

void check_if_file(int argc, char** argv) {
    printf(
        CLR_GREEN_BRIGHT
        "--------------------------------------------\n!!!EXECUTING CODE TO CHECK IF ARGVs ARE FILES!!!\n\n");
    for (int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if (file != NULL) {
            printf("Yes, argv[%d] is a file and can be read\n", i);
            fclose(file);
        } else {
            printf(CLR_RED_BRIGHT "No, argv[%d] is NOT a file and can't be read\n" CLR_GREEN_BRIGHT, i);
        }
    }
    printf("\n!!!CHECKED ALL FILES!!!\n--------------------------------------------" CLR_RESET "\n");
}

void what_opt(int opt) {
    printf("%c - is opt\n", (char)opt);
}