OS=MAC
USERNAME := $(shell uname -s)
СС = gcc
FLAGS = -Wall -Wextra -Werror
ALL_C_FILES = s21_*.c
ALL_O_FILES = s21_*.o
TEST_FLAGS = -lm -lsubunit -lcheck -lpthread
LIBRARY = s21_matrix.a
TEST_LIBRARY = test
GCOVFLAGS=-fprofile-arcs -ftest-coverage
TEST_SOURCES=./tests/*.c
TEST_EXECUTABLE=test

ifeq ($(USERNAME),Linux)
	CHECKFLAGS= -lcheck
	ADD_LIB = -lm -lpthread -lrt -lsubunit
	OS = LINUX
endif

ifeq ($(USERNAME),Darwin)
	CHECKFLAGS= $(shell pkg-config --cflags --libs check)
endif

all: s21_matrix.a

s21_matrix.a:
	$(CC) $(FLAGS) -c $(ALL_C_FILES)
	ar rcs $(LIBRARY) $(ALL_O_FILES)
	rm -rf *.o

s21_matrix.a_coverage:
	$(CC) $(FLAGS) $(GCOVFLAGS) -c $(ALL_C_FILES)
	ar rcs $(LIBRARY) $(ALL_O_FILES)
	rm -rf *.o
test: clean s21_matrix.a_coverage
	$(CC) $(TEST_SOURCES) -L. $(LIBRARY) -o $(TEST_EXECUTABLE) $(CHECKFLAGS) -B /usr/bin/gcov -fprofile-arcs -ftest-coverage $(ADD_LIB)
	./test

gcov_report: clean s21_matrix.a_coverage test
	lcov -o tests.info -c -d .
	genhtml -o report tests.info
	xdg-open report/index.html

format:
	cp ../materials/linters/.clang-format .
	find . -type f \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} \; -exec clang-format -n {} \;

clean: 
	rm -rf $(LIBRARY) $(TEST_LIBRARY) report *.o *.a *.gcda *.gcno *.gcov *.html *.css *.info *.profraw

rebuild: clean all
