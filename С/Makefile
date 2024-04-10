OS=MAC
USERNAME := $(shell uname -s)
OPEN_CMD = open

#CC=gcc -Wall -Wextra -Werror -D_GNU_SOURCE
CC=gcc -D_GNU_SOURCE
FLAGS= -lcheck -lm -lpthread
GCOVFLAGS := -lcheck -coverage -lpthread -pthread -lm
ADD_LIB=

SOURCES=s21_decimal.c utils.c
OBJECTS=s21_decimal.o utils.o
EXECUTABLE=s21_decimal.a
TEST_SOURCES=./tests/*.c
TEST_EXECUTABLE=test

ifeq ($(USERNAME),Linux)
	OS = LINUX
	ADD_LIB = -lm -lpthread -lrt -lsubunit
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
	ranlib $(EXECUTABLE)
	@rm -rf *.o

s21_decimal.a_coverage:
	$(CC) $(FLAGS) $(GCOVFLAGS) -c $(SOURCES)
	ar rcs $(EXECUTABLE) $(OBJECTS)
	ranlib $(EXECUTABLE)
	@rm -rf *.o

test: clean s21_decimal.a_coverage
	$(CC) $(TEST_SOURCES) $(GCOVFLAGS) $(EXECUTABLE) -L. -o $(TEST_EXECUTABLE) $(ADD_LIB)
	./test

gcov_report: clean s21_decimal.a_coverage test
	$(CC) --coverage $(TEST_SOURCES) $(SOURCES) $(EXECUTABLE) -L. $(EXECUTABLE) $(FLAGS) -o ./test.out
	./test.out
	gcov s21_*.gcno > report.html
	make clean

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

.PHONY: all test gocv_report clean checks rebuild s21_decimal.a s21_decimal.a_coverage

