#include "cat_func.h"

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
            printer(file);
            fclose(file);
        }
        if (i < argc - 1) {
            printf("\n");
        }
    }
}

void printer(FILE* file) {
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