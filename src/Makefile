CC = gcc
EFLAGS = -Wall -Wextra -Werror -std=c11
TEST_FLAGS = -lcheck -lm -lpthread
CFLAGS = $(EFLAGS) -c
OFLAGS = $(EFLAGS) -o
S21_MATRIX_O = s21_*.o

ifeq ($(shell uname -s),Linux)
	TEST_FLAGS += -lrt -lsubunit
endif


all: clean test

s21_matrix.a:
	$(CC) $(CFLAGS) s21_helps.c s21_matrix.c
	ar r s21_matrix.a s21_helps.o s21_matrix.o
	rm -rf *.o
	ranlib s21_matrix.a

test: s21_matrix.a
	$(CC) $(CFLAGS) tests.c
	$(CC) $(OFLAGS) test tests.o s21_matrix.a $(TEST_FLAGS)
	./test
	rm -rf *.o *.a

valgrind: s21_matrix.a
	$(CC) $(CFLAGS) tests.c
	$(CC) $(OFLAGS) test tests.o s21_matrix.a $(TEST_FLAGS)
	rm -rf *.o
	# valgrind --leak-check=full -s ./test
	valgrind --leak-check=full -s ./test

gcov_report:
	$(CC) --coverage $(CFLAGS) s21_helps.c s21_matrix.c
	ar r s21_matrix.a s21_helps.o s21_matrix.o
	ranlib s21_matrix.a
	$(CC) $(CFLAGS) tests.c
	$(CC) --coverage $(OFLAGS) test tests.o s21_matrix.a $(TEST_FLAGS)
	rm -rf *.o *.a
	./test
	# gcov s21*.gcda
	gcovr -r . --html --html-details -o report.html
	open report.html

style_check:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	rm .clang-format

style_fix:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h
	rm .clang-format

clean:
	rm -rf *.o *.a test tgtests *.gcda *.gcno *.gcov *.html *.css *.out

rebuild: all