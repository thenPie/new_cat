#include "cat_func.h"
#include <getopt.h>
#include <stdio.h>

// functional code
void run_cat(int argc, char** argv) {
    if (argc > 1) {
        // main_cat(argc, argv);
        check_if_file_functional(argc, argv);
    }
}

// it was used for debugging, no need for it now
void main_cat(int argc, char** argv) {
    check_if_file_functional(argc, argv);
}

void check_if_file_functional(int argc, char** argv) {

    int readable_files = count_rdbl_files(argc, argv);

    int number_non_empty_lines_bb = -1;
    int show_dollar_ends_ee = -1;
    int number_all_lines_nn = -1;
    int suppress_empty_lines_ss = -1;
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

    int is_on_new_line = 0;
    int line_count = 1;
    int empty_line_count = 0;
    int amount_of_opened = 0;

    for (int i = 1; i < argc; i++) {
        int no_file = 0;
        FILE* file = fopen(argv[i], "r");
        if (file != NULL) {
            // print out the file here
            printer(file, number_non_empty_lines_bb, show_dollar_ends_ee, number_all_lines_nn, suppress_empty_lines_ss, show_tabs_tt, &is_on_new_line, &line_count, &empty_line_count);
            // printf("\n%d EMPTY_LINE_COUNT", empty_line_count);
            fclose(file);
            no_file = -1;
            amount_of_opened++;
        }
        if (no_file == -1 && amount_of_opened < readable_files) {
            if (!(suppress_empty_lines_ss == 0 && empty_line_count > 1)) {
                printf("\n");
                is_on_new_line = 0;
            }
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

void printer(FILE* file, int b, int e, int n, int s, int t, int* is_on_new_line, int* line_count, int* empty_line_count) {
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (s == 0) {
            if (*is_on_new_line == 0) {
                if (c == '\n') {
                    *empty_line_count += 1;
                } else {
                    *empty_line_count = 0;
                }
            }
        }

        if (*is_on_new_line == 0) {
            if (b == 0) {
                if (c != '\n') {
                    line_counter_printer(line_count, is_on_new_line);
                }
            } else if (n == 0) {
                if (!(s == 0 && *empty_line_count > 1)) {
                    line_counter_printer(line_count, is_on_new_line);
                }
            }

            *is_on_new_line = -1;
        }

        if (c == '\n') {
            *is_on_new_line = 0;
        }

        if (e == 0 && c == '\n') {
            c = '$';
        }

        if (t == 0 && c == '	') {
            c = '^';
        }

        if (s == 0 && *empty_line_count > 1) {
            c = '!';
        }

        switch (c) {
            case '$':
                printf("%c\n", c);
                break;
            case '^':
                printf("%cI", c);
                break;
            case '!':
                break;
            default:
                printf("%c", c);
                break;
        }
    }

    // if (n == 0 && c == EOF  && *is_on_new_line == 0) {
    //     if (!(s == 0 && *empty_line_count > 1)) {
    //         line_counter_printer(line_count, is_on_new_line);
    //     }
    // }
    // if (e == 0 && c == EOF) {
    //     if (!(s == 0 && *empty_line_count > 1)) {
    //         printf("$");
    //     }
    // }
}

void line_counter_printer(int* line_count, int* is_on_new_line) {
    int is_overflow = -1;
    int amount_of_spaces = 5;
    if (*line_count < 10) {
        lcp_empty(amount_of_spaces);
    } else if (*line_count < 100) {
        amount_of_spaces = 4;
        lcp_empty(amount_of_spaces);
    } else if (*line_count < 1000) {
        amount_of_spaces = 3;
        lcp_empty(amount_of_spaces);
    } else if (*line_count < 10000) {
        amount_of_spaces = 2;
        lcp_empty(amount_of_spaces);
    } else if (*line_count < 100000) {
        amount_of_spaces = 1;
        lcp_empty(amount_of_spaces);
    } else if (*line_count < 1000000) {
        is_overflow = 0;
    }
    if (is_overflow != 0) {
        printf("%d  ", *line_count);
    } else {
        printf("+999999");
    }
    *line_count = *line_count + 1;
    *is_on_new_line = -1;
}

void lcp_empty(int aos) {
    for (int i = 0; i < aos; i++) {
        printf(" ");
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