#include <stdio.h>
#include <string.h>
char *s21_strpbrk(const char *str1, const char *str2) {
  for (size_t i = 0; str1[i] != '\0'; i++) {
    for (size_t j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        return (char *)&str1[i];
      }
    }
  }
  return NULL;
}
int main() {
  const char *str1 = "232432";
  const char *str2 = "";

  char *result1 = strpbrk(str1, str2);
  char *result2 = strpbrk(str1, str2);

  if (result1) // Проверяем, что указатель не NULL
    printf("First trim: %c\n", *result1);
  else if (result1 == NULL) {
    printf("No matching character found.\n");
  }

  if (result2) // Проверяем, что указатель не NULL
    printf("First trim: %c\n", *result2);
  else if (result2 == NULL) {
    printf("No matching character found.\n");
  }

  return 0;
}
