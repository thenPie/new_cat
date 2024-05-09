CC = gcc
CC_FLAGS_STD = $(CC) -Wall -Werror -Wextra -std=c11
NAME_IS = -o
CAT_SRC_CODE = cat.c cat_func.c

all: s21_cat

s21_cat: $(CAT_SRC_CODE)
	$(CC_FLAGS_STD) $(NAME_IS) s21_cat $(CAT_SRC_CODE)

clang_check:
	clang-format -n *.c

clang_fix:
	clang-format -i *.c

clean:
	rm s21_cat

rebuild: clean all