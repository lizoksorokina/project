CC=gcc -std=c11 -D_GNU_SOURCE
TEST_LIBS=-lcheck -lm -lpthread 
LIB_A=s21_string.a
CC_FLAGS = -Wall -Werror -Wextra -std=c11
TESTFLAGS := -lcheck -coverage -lpthread -pthread 
C_FILES = s21_*.c 
O_FILES = s21_*.o

all: s21_string.a

s21_string.a: $(C_FILES)
	$(CC) -c $(CC_FLAGS) $(C_FILES)
	ar r s21_string.a $(O_FILES)
	ranlib s21_string.a
	@rm $(O_FILES)

test: s21_string.a
	gcc test.c $(GCCFLAGS) $(TESTFLAGS) -L. s21_string.a -o test
	./test

gcov_report: s21_string.a
	$(CC) --coverage test.c $(C_FILES) $(LIB_A) -L. $(LIB_A) $(TEST_LIBS) -o ./test.out
	./test.out
	gcov s21_*.gcno > report.html
	make clean

style: clean
	clang-format -i *.c */*.c */*.h
	clang-format -n *.c */*.c */*.h

check:  ./test
	leaks --atExit -- ./test

rebuild:
	@make clean
	@make test
	
clean:
	rm -rf *.o *.gch *.out *.gcno *.gcda *.info *.gcov *.a test
	rm -rf report/
	rm -rf temp/
	rm -rf atest.c
