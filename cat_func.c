#include "cat_func.h"

#include <getopt.h>
#include <stdio.h>

void run_cat(int argc, char** argv) {
  if (argc > 1) {
    int rdbl_files = count_rdbl_files(argc, argv);
    int number_non_empty_lines_bb = -1;
    int show_dollar_ends_ee = -1;
    int number_all_lines_nn = -1;
    int suppress_empty_lines_ss = -1;
    int show_tabs_tt = -1;
    int is_on_new_line = 0;
    int line_count = 1;
    int empty_line_count = 0;
    int amount_of_opened = 0;
    int opt;
    struct option long_opt[] = {{"number-nonblank", 0, 0, 'b'},
                                {"number", 0, 0, 'n'},
                                {"squeeze-blank", 0, 0, 's'}};
    check_if_file_functional(argc, argv, rdbl_files, &number_non_empty_lines_bb,
                             &show_dollar_ends_ee, &number_all_lines_nn,
                             &suppress_empty_lines_ss, &show_tabs_tt,
                             &is_on_new_line, &line_count, &empty_line_count,
                             &amount_of_opened, long_opt, &opt);
  }
}

void check_if_file_functional(int argc, char** argv, int rdbl_files, int* bb,
                              int* ee, int* nn, int* ss, int* tt,
                              int* is_on_new_line, int* line_count,
                              int* empty_line_count, int* amount_of_opened,
                              struct option long_opt[], int* opt) {
  while ((*opt = getopt_long(argc, argv, ":benstET", long_opt, NULL)) != -1) {
    switch (*opt) {
      case 'b':
        *bb = 0;
        break;
      case 'e':
        *ee = 0;
        break;
      case 'n':
        *nn = 0;
        break;
      case 's':
        *ss = 0;
        break;
      case 't':
        *tt = 0;
        break;
      case 'E':
        *ee = 0;
        break;
      case 'T':
        *tt = 0;
        break;
      default:
        break;
    }
  }
  filer(argc, argv, *bb, *ee, *nn, *ss, *tt, is_on_new_line, line_count,
        empty_line_count, amount_of_opened, rdbl_files);
}

void filer(int argc, char** argv, int bb, int ee, int nn, int ss, int tt,
           int* is_on_new_line, int* line_count, int* empty_line_count,
           int* amount_of_opened, int rdbl_files) {
  for (int i = 1; i < argc; i++) {
    int no_file = 0;
    FILE* file = fopen(argv[i], "r");
    if (file != NULL) {
      printer(file, bb, ee, nn, ss, tt, is_on_new_line, line_count,
              empty_line_count);
      fclose(file);
      no_file = -1;
      *amount_of_opened += 1;
    }
    if (no_file == -1 && *amount_of_opened < rdbl_files) {
      if (!(ss == 0 && *empty_line_count > 1)) {
        printf("\n");
        *is_on_new_line = 0;
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

void printer(FILE* file, int b, int e, int n, int s, int t, int* is_on_new_line,
             int* line_count, int* empty_line_count) {
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
    print_c(c);
  }
  // eof_checker(c, n, s, line_count, is_on_new_line, *empty_line_count);
}

void eof_checker(char c, int nn, int ss, int* line_count, int* is_on_new_line,
                 int empty_line_count) {
  if (nn == 0 && c == EOF && *is_on_new_line == 0) {
    if (!(ss == 0 && empty_line_count > 1)) {
      line_counter_printer(line_count, is_on_new_line);
    }
  }
  // if (ee == 0 && c == EOF) {
  //   if (!(ss == 0 && empty_line_count > 1)) {
  //     printf("$");
  //   }
  // }
}

void print_c(char c) {
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
