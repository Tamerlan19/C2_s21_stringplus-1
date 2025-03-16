.PHONY = all, clean, test, s21_string.a, gcov_report
CC = gcc
# CFLAGS = -Werror -Wall -Wextra -std=c11 
# CFLAGSDEBUG = -Werror -Wall -Wextra -std=c11 -DDEBUG
ifeq ($(DEBUG),1)
    CFLAGS = -Werror -Wall -Wextra -std=c11 -DDEBUG
else
    CFLAGS = -Werror -Wall -Wextra -std=c11 
endif
TESTFLAGS = -lcheck -lsubunit -lm
SRC_DIR =./
SOURCES =  s21_utils.h  s21_string.h s21_string.c s21_sprintf.c s21_sscanf.c s21_utils.c
SOURCES_TST = test.c test_s21_sscanf_gen.c test/*.c
SRCS = test.c s21_string.c test_s21_string.c test_s21_sscanf.c test_s21_sprintf.c s21_sscanf.c s21_sprintf.c s21_utils.c
OBJS = $(SRCS:.c=.o)
TARGET = ./



# [x] Оформи решение как статическую библиотеку с названием s21_string.a (с заголовочным файлом s21_string.h).
# [x] Предусмотри Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_string.a, gcov_report).
# [ ] В цели gcov_report должен формироваться отчёт gcov в виде html страницы. Для этого unit-тесты должны запускаться с флагами gcov.

all: s21_string.a

build: style cppcheck all

s21_string.a: s21_string.o s21_sprintf.o s21_sscanf.o s21_utils.o
	ar rcs $(TARGET)$@ $^
	rm $^

test: clean s21_string.a test.c
	$(CC) $(CFLAGS) -o test.exe test.c test/*.c -L. -l:s21_string.a $(TESTFLAGS)
	./test.exe

testgen: clean s21_string.a 
	$(CC) $(CFLAGS) -o test_gen_s21_sscanf.exe test/test_s21_sscanf_gen.c
	./test_gen_s21_sscanf.exe

test2: s21_string.a 
	$(CC) $(CFLAGS) -o test_s21_sscanf_gen.exe test/test_gen_s21_sscanf.c -L. -l:s21_string.a $(TESTFLAGS)
	./test_s21_sscanf_gen.exe

gtest: clean s21_string.a testgen test2

gcov_report: clean 
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -c s21_string.c -o s21_string.o
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -c s21_sprintf.c -o s21_sprintf.o
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -c s21_sscanf.c -o s21_sscanf.o
	# $(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -c s21_utils.c -o s21_utils.o
	ar rcs $(TARGET)s21_string.a s21_string.o s21_sprintf.o s21_sscanf.o
	$(CC) $(CFLAGS)  -fprofile-arcs -ftest-coverage  -o test.exe -o test.exe test.c test_s21_string.c test_s21_sprintf.c test/*.c  -L. -l:s21_string.a $(TESTFLAGS)
	./test.exe
	gcov s21_string.c s21_sprintf.c s21_sscanf.c
	lcov --exclude "test*.c"   --capture --directory ./ --output-file flt-coverage.info
	genhtml flt-coverage.info --output-directory gcov_report
#--exclude "s21_utils.c"
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@



rebuild: clean build

clean:
	rm -f $(OBJS) $(TARGET)/*.a $(TARGET)/*.gcov $(TARGET)/*.gcda $(TARGET)/*.gcno $(TARGET)/*.exe *.info test_gen_*
	@if [ -d "./gcov_report/" ]; then \
		rm -r ./gcov_report/; \
	fi

style:
	@for src in $(SOURCES) $(SOURCES_TST); do \
		echo "###Formatting $$src..." ; \
		clang-format -i "$(SRC_DIR)/$$src" ; \
	done
	@echo "Done"

check-style:
	@for src in $(SOURCES) $(SOURCES_TST); do \
		echo "###Check format for file $$src..." ; \
		clang-format -n "$(SRC_DIR)/$$src" ; \
	done
	@echo "Style check passed."

cppcheck:
		@FLS="" ; \
		for src in $(SOURCES) $(SOURCES_TST); do \
			FLS="$$FLS $(SRC_DIR)$$src" ; \
		done ;\
		echo "### Test cppcheck for files: $$FLS..."; \
		cppcheck --enable=all --suppress=missingIncludeSystem $$FLS ; \
		echo "cppcheck control passed."





