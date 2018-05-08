#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void noEsConstanteEntera (char constante[]) {
  printf("%s no es constante entera", constante);
}

_Bool esDecimalUOctal (char constante [], char tope) {
  int i = 1;
  while (constante[i] != '\0' && constante[i] >= '0' && constante[i] <= tope) {
    i++;
  }

  return constante[i] == '\0';
}

int main () {
  char octal[9] = "01234567";
  char octalFalso[9] = "01234597";
  char decimal[9] = "12345690";
  char decimalFalso[9] = "9a234567";

  printf("Octal es %i\n",  esDecimalUOctal(octal, '7'));
  printf("Octal falso es %i\n",  esDecimalUOctal(octalFalso, '7'));
  printf("Decimal es %i\n",  esDecimalUOctal(decimal, '9'));
  printf("Decimal falso es %i\n",  esDecimalUOctal(decimalFalso, '9'));
  char a = '2';
  if (a >= '1' && a <= '9') {

  } else if (a == '0') {

  }

  return 0;
}
