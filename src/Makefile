FLAG       = -Wall -Wextra -Werror -std=c11
FLAG_LIB   = -lcheck -lsubunit -lm
FLAG_GCOV = -fprofile-arcs -ftest-coverage

SRC_STRING = s21_string.c s21_sprintf.c s21_sscanf.c
OBJ_STRING = s21_string.o s21_sprintf.o s21_sscanf.o
SRC_TEST   = test_s21_string.c 

all: clean s21_string.a

s21_string.a: $(SRC_STRING)
	gcc -c $(FLAG) $(SRC_STRING)
	ar rcs s21_string.a $(OBJ_STRING)

test: clean s21_string.a
	gcc $(FLAG) $(SRC_TEST) s21_string.a -o unit_test $(FLAG_LIB)
	./unit_test
		
leaks: clean s21_string.a
	gcc $(FLAG) -ggdb3 $(SRC_TEST) s21_string.a -o unit_test $(FLAG_LIB)
	valgrind --tool=memcheck --leak-check=yes ./unit_test

leaks-quiet: clean s21_string.a
	gcc $(FLAG) -ggdb3 $(SRC_TEST) s21_string.a -o unit_test $(FLAG_LIB)
	valgrind --tool=memcheck --leak-check=yes --quiet ./unit_test

leaks-log: clean s21_string.a
	gcc $(FLAG) -ggdb3 $(SRC_TEST) s21_string.a -o unit_test $(FLAG_LIB)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file="leaks_log.txt" ./unit_test

gcov_s21_string.a: $(SRC_STRING)
	gcc -c $(FLAG_GCOV) $(FLAG) $(SRC_STRING)
	ar rcs s21_string.a $(OBJ_STRING)

gcov_report: clean gcov_s21_string.a
	gcc $(FLAG) $(FLAG_GCOV) $(SRC_TEST) s21_string.a -o gcov_unit_test $(FLAG_LIB)
	./gcov_unit_test
	gcov $(OBJ_STRING)
	lcov -t "gcov_report" -o s21_string_coverage.info -c -d .
	genhtml -o report s21_string_coverage.info

clean:
	rm -f s21_string.a
	rm -f *.o
	rm -f *.h.gch
	rm -f unit_test gcov_unit_test
	rm -f *.gcda *.gcno *.gcov
	rm -rf report
	rm -f *.info

rebuild: clean all

.PHONY: all test clean gcov_report rebuild
