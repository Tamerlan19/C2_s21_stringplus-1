#include <stdio.h>
#include <string.h>

void *s21_memcpy(void *dest, const void *src, int n) {
  unsigned char *src_1 = (unsigned char *)src;
  unsigned char *dest_1 = (unsigned char *)dest;
  for (int i = 0; i < n; i++) {
    dest_1[i] = src_1[i];
  }
  return dest;
}
void test_memcpy() {
  // Тест 1: Копирование строк
  char str1[] = "Hello, world!";
  char dest1[20];
  s21_memcpy(dest1, str1, 13); // Копируем 13 символов
  printf("Test 1 - Expected: 'Hello, world!' | Got: '%s'\n", dest1);

  // Тест 2: Копирование в пустой массив
  char str2[] = "Testing";
  char dest2[10];
  s21_memcpy(dest2, str2, 7); // Копируем 7 символов
  printf("Test 2 - Expected: 'Testing' | Got: '%s'\n", dest2);

  // Тест 3: Копирование меньше чем размер строки
  char str3[] = "Short";
  char dest3[10];
  s21_memcpy(dest3, str3, 3); // Копируем только первые 3 символа
  dest3[3] = '\0'; // Завершаем строку вручную
  printf("Test 3 - Expected: 'Sho' | Got: '%s'\n", dest3);

  // Тест 4: Копирование в пустой массив с нулевой длиной
  char str4[] = "Empty copy test";
  char dest4[20];
  s21_memcpy(dest4, str4, 0); // Ничего не копируем
  printf("Test 4 - Expected: '' | Got: '%s'\n",
         dest4); // Ожидается пустая строка

  // Тест 5: Копирование в массив с размером больше, чем строка
  char str5[] = "Hello";
  char dest5[20];
  s21_memcpy(dest5, str5, 5); // Копируем строку целиком
  dest5[5] = '\0';            // Завершаем строку
  printf("Test 5 - Expected: 'Hello' | Got: '%s'\n", dest5);

  // Тест 6: Копирование массива байтов
  unsigned char arr1[] = {1, 2, 3, 4, 5};
  unsigned char arr2[5];
  s21_memcpy(arr2, arr1, 5); // Копируем массив из 5 байтов
  printf("Test 6 - Expected: '1 2 3 4 5' | Got: '%d %d %d %d %d'\n", arr2[0],
         arr2[1], arr2[2], arr2[3], arr2[4]);

  // Тест 7: Копирование в тот же массив
  char str6[] = "No change";
  s21_memcpy(str6, str6, 9); // Копируем строку в саму себя
  printf("Test 7 - Expected: 'No change' | Got: '%s'\n", str6);
}

int main() {
  test_memcpy(); // Запуск тестов
  return 0;
}