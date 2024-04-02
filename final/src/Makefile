OS=MAC
USERNAME := $(shell uname -s)
OPEN_CMD = open

#CC=gcc -Wall -Wextra -Werror
CC=gcc -g # TODO: Remove
FLAGS= -lm -lsubunit -lcheck -lpthread
GCOVFLAGS=-fprofile-arcs -ftest-coverage
GLFLAGS=--coverage

SOURCES=s21_decimal.c utils.c
OBJECTS=s21_decimal.o utils.o
EXECUTABLE=s21_decimal.a
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

all: s21_decimal.a

install:
	if [ $(OS) = "LINUX" ]; then \
		sudo apt-get install -y lcov; \
		sudo apt-get install -y check; \
	else \
		brew install lcov; \
	fi

s21_decimal.a:
	$(CC) $(FLAGS) -c $(SOURCES)
	ar rcs $(EXECUTABLE) $(OBJECTS)
	rm -rf *.o

s21_decimal.a_coverage:
	$(CC) $(FLAGS) $(GCOVFLAGS) -c $(SOURCES)
	ar rcs $(EXECUTABLE) $(OBJECTS)
	rm -rf *.o

test: clean s21_decimal.a_coverage
	$(CC) $(TEST_SOURCES) -L. $(EXECUTABLE) -o $(TEST_EXECUTABLE) $(CHECKFLAGS) -lgcov $(ADD_LIB)
	./test

gcov_report: clean s21_decimal.a_coverage test
	lcov -o tests.info -c -d .
	genhtml -o report tests.info
	$(OPEN_CMD) report/index.html

clean:
	rm -rf $(EXECUTABLE) $(TEST_EXECUTABLE) report *.o *.a *.gcda *.gcno *.gcov *.html *.css *.info

cppcheck:
	$@ --enable=all --suppress=missingIncludeSystem .

valgrind: $(TEST_EXECUTABLE)
	CK_FORK=no $@ --tool=memcheck --leak-check=yes $<

leaks: $(TEST_EXECUTABLE)
	CK_FORK=no $@ -atExit -- $<

format:
	cp ../materials/linters/.clang-format .
	find . -type f \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} \; -exec clang-format -n {} \;

checks: format cppcheck
	if [ $(OS) = "LINUX" ]; then \
		make valgrind;  \
	else \
		make leaks; \
	fi

rebuild: clean all

.PHONY: all test gcov_report clean checks rebuild s21_decimal.a s21_decimal.a_coverage

