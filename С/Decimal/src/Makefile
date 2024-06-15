OS=MAC
USERNAME := $(shell uname -s)
OPEN_CMD = open

CC=gcc -Werror -Wall -Wextra -std=c11
GCOVFLAGS= -fprofile-arcs -ftest-coverage
CHECKFLAGS= -lcheck
GLFLAGS=

SOURCES=s21_decimal.c utils.c
OBJECTS=s21_decimal.o utils.o
EXECUTABLE=s21_decimal.a
TEST_SOURCES=tests/*.c
TEST_EXECUTABLE=test
COVERAGE_FOLDER=coverage_html

ifeq ($(USERNAME),Linux)
	CHECKFLAGS += -lm -lsubunit
	OS = LINUX
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

test: clean
	$(CC) $(FLAGS) $(GCOVFLAGS) $(TEST_SOURCES) $(SOURCES) -o $(TEST_EXECUTABLE) $(CHECKFLAGS)
	./$(TEST_EXECUTABLE)
	make clean

gcov_report: clean
	$(CC) $(FLAGS) $(TEST_SOURCES) $(SOURCES) -o $(TEST_EXECUTABLE) $(CHECKFLAGS) $(GCOVFLAGS)
	./$(TEST_EXECUTABLE)
	lcov --capture --directory . -o coverage.info
	lcov --remove coverage.info '/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/*' --output-file coverage.info.cleaned
	genhtml coverage.info.cleaned -o $(COVERAGE_FOLDER)
	$(OPEN_CMD) $(COVERAGE_FOLDER)/index.html

clean:
	rm -rf $(EXECUTABLE) $(TEST_EXECUTABLE) $(COVERAGE_FOLDER) report *.o *.a *.gcda *.gcno *.gcov *.html *.css *.info *.cleaned

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
