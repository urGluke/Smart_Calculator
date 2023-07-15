CF = -Wall -Werror -Wextra -std=c11 -g
LF = -lm -lcheck -lpthread
HEADERS = s21_smart_calc.h

ifeq ($(shell uname -s), Linux)
	LF += -lsubunit
endif

all: uninstall dvi style test gcov_report dist install

install:
	[-d build] || mkdir -p build
	cd build && qmake ../calculator/calculator.pro
	make -C build/

uninstall: clean
	rm -rf build

dvi:
	open ../README.md

dist: uninstall clean
	cd ..
	tar -cf s21_smart_calc.tar *.c *.h tests calculator Makefile README.md

test:
	gcc $(CF) s21_smart_calc.c tests/test.c -o test $(LF)
	rm -rf *.o *.a
	./test

gcov_report: clean
	gcc tests/test.c s21_smart_calc.c -o gcov_report --coverage $(LF)
	./gcov_report
	rm -f test.gc*
	gcov *.gcno
	lcov -d . -o gcov_report.info -c
	genhtml -o report gcov_report.info
	open report/index.html

clean:
	rm -rf *.o *.out *.a *.gcda *.gcdo gcov* *gcov report *.tar test
style:
	clang-format -style=Google -i tests/test.c
	clang-format -style=Google -n tests/test.c
	clang-format -style=Google -i *.c calculator/*.cpp calculator/*.h
	clang-format -style=Google -n *.c calculator/*.cpp calculator/*.h
