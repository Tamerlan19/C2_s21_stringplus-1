.PHONY = all, clean, test, s21_string.a, gcov_report
CC = gcc
CFLAGS = -Werror -Wall -Wextra -std=c11 -DDEBUG
TESTFLAGS = -lcheck -lsubunit -lm
SRC_DIR =./
SOURCES = test.c s21_string.c test_s21_string.c test_s21_sscanf.c test_s21_sprintf.c s21_string.h
SRCS = test.c s21_string.c test_s21_string.c test_s21_sscanf.c test_s21_sprintf.c
OBJS = $(SRCS:.c=.o)
TARGET = ./


# [x] Оформи решение как статическую библиотеку с названием s21_string.a (с заголовочным файлом s21_string.h).
# [x] Предусмотри Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_string.a, gcov_report).
# [ ] В цели gcov_report должен формироваться отчёт gcov в виде html страницы. Для этого unit-тесты должны запускаться с флагами gcov.

all: s21_string.a

build: style cppcheck all

s21_string.a: s21_string.o
	ar rcs $(TARGET)$@ $^
<<<<<<< HEAD

test: s21_string.a test_s21_string.c
	$(CC) $(CFLAGS) -o test_s21_string.exe test_s21_string.c -L. -l:s21_string.a $(TESTFLAGS)
	./test_s21_string.exe
=======
	rm $^

test: s21_string.a test_s21_string.c test_s21_sscanf.c test_s21_sprintf.c
	$(CC) $(CFLAGS) -o test.exe test.c test_s21_string.c test_s21_sscanf.c test_s21_sprintf.c -L. -l:s21_string.a $(TESTFLAGS)
	./test.exe
>>>>>>> 84216d2cd5df977021cdda1d6dcf85320fb083da

gcov_report: 
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -c s21_string.c -o s21_string.o
	ar rcs $(TARGET)s21_string.a s21_string.o
<<<<<<< HEAD
	$(CC) $(CFLAGS)  -fprofile-arcs -ftest-coverage  -o test_s21_string.exe test_s21_string.c -L. -l:s21_string.a $(TESTFLAGS)
	./test_s21_string.exe
	gcov s21_string.c
	lcov --capture --directory ./ --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
=======
	$(CC) $(CFLAGS)  -fprofile-arcs -ftest-coverage  -o test.exe test.c test_s21_string.c test_s21_sscanf.c test_s21_sprintf.c -L. -l:s21_string.a $(TESTFLAGS)
	./test.exe
	gcov s21_string.c
	lcov --exclude "test*.c"  --capture --directory ./ --output-file flt-coverage.info
	genhtml flt-coverage.info --output-directory gcov_report
>>>>>>> 84216d2cd5df977021cdda1d6dcf85320fb083da

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@



rebuild: clean build

clean:
<<<<<<< HEAD
	rm -f $(OBJS) $(TARGET)/*.a $(TARGET)/*.gcov $(TARGET)/*.gcda $(TARGET)/*.gcno $(TARGET)/*.exe coverage.info
	rm -r ./gcov_report/
=======
	rm -f $(OBJS) $(TARGET)/*.a $(TARGET)/*.gcov $(TARGET)/*.gcda $(TARGET)/*.gcno $(TARGET)/*.exe *.info
	@if [ -d "./gcov_report/" ]; then \
		rm -r ./gcov_report/; \
	fi
>>>>>>> 84216d2cd5df977021cdda1d6dcf85320fb083da

style:
	@for src in $(SOURCES) ; do \
		echo "###Formatting $$src..." ; \
		clang-format -i "$(SRC_DIR)/$$src" ; \
	done
	@echo "Done"

check-style:
	@for src in $(SOURCES) ; do \
		echo "###Check format for file $$src..." ; \
		clang-format -n "$(SRC_DIR)/$$src" ; \
	done
	@echo "Style check passed."

cppcheck:
		@FLS="" ; \
<<<<<<< HEAD
		for src in $(SOURCES)  ; do \
=======
		for src in $(SOURCES) ; do \
>>>>>>> 84216d2cd5df977021cdda1d6dcf85320fb083da
			FLS="$$FLS $(SRC_DIR)$$src" ; \
		done ;\
		echo "### Test cppcheck for files: $$FLS..."; \
		cppcheck --enable=all --suppress=missingIncludeSystem $$FLS ; \
		echo "cppcheck control passed."



