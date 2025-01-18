.PHONY = all, clean, test, s21_string.a, gcov_report
CC = gcc
CFLAGS = -Werror -Wall -Wextra -std=c11
TESTFLAGS = -lcheck -lsubunit -lm
SRC_DIR =./
SOURCES = s21_string.c test_s21_string.c
OBJS = $(SOURCES:.c=.o)
TARGET = ./


#TODO: Оформи решение как статическую библиотеку с названием s21_string.a (с заголовочным файлом s21_string.h).
#TODO: Предусмотри Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_string.a, gcov_report).
#TODO: В цели gcov_report должен формироваться отчёт gcov в виде html страницы. Для этого unit-тесты должны запускаться с флагами gcov.

all: s21_string.a

build: style cppcheck all

s21_string.a: s21_string.o
	ar rcs $(TARGET)$@ $^

test: s21_string.a test_s21_string.c test_s21_sscanf.c
	$(CC) $(CFLAGS) -o test_s21_string.exe test_s21_string.c test_s21_sscanf.c -L. -l:s21_string.a $(TESTFLAGS)
	./test_s21_string.exe

gcov_report: 
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -c s21_string.c -o s21_string.o
	ar rcs $(TARGET)s21_string.a s21_string.o
	$(CC) $(CFLAGS)  -fprofile-arcs -ftest-coverage  -o test_s21_string.exe test_s21_string.c -L. -l:s21_string.a $(TESTFLAGS)
	./test_s21_string.exe
	gcov s21_string.c
	lcov --capture --directory ./ --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@



rebuild: clean build

clean:
	rm -f $(OBJS) $(TARGET)/*.a $(TARGET)/*.gcov $(TARGET)/*.gcda $(TARGET)/*.gcno $(TARGET)/*.exe coverage.info
	rm -r ./gcov_report/

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
		for src in $(SOURCES)  ; do \
			FLS="$$FLS $(SRC_DIR)$$src" ; \
		done ;\
		echo "### Test cppcheck for files: $$FLS..."; \
		cppcheck --enable=all --suppress=missingIncludeSystem $$FLS ; \
		echo "cppcheck control passed."



