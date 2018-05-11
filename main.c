#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void noEsConstanteEntera (char constante[]) {
  printf("%s no es constante entera", constante);
}

int esDecimalUOctal (char constante, char tope) {
  return constante >= '0' && constante <= tope;
}

int esHexa (char constante) {
  return (constante >= 'a' && constante <= 'f') || (constante >= 'A' && constante <= 'F');
}

int constanteDecimal (char constante[]) {
  int i = 1;
  int condicion = esDecimalUOctal(constante[i], '9');
  while (constante[i] != '\0' && condicion) {
    condicion = esDecimalUOctal(constante[i], '9');
    if (condicion) i++;
  }

  return constante[i] == '\0';
}

int constanteHexa (char constante[]) {
  int i = 2;
  int condicion = esDecimalUOctal(constante[i], '9') || esHexa(constante[i]);
  while (constante[i] != '\0' && condicion) {
    condicion = esDecimalUOctal(constante[i], '9') || esHexa(constante[i]);
    if (condicion) i++;
  }

  return constante[i] == '\0';
}

int constanteOctal (char constante[]) {
  int i = 1;
  int condicion = esDecimalUOctal(constante[i], '7');
  while (constante[i] != '\0' && condicion) {
    condicion = esDecimalUOctal(constante[i], '7');
    if (condicion) i++;
  }

  return constante[i] == '\0';
}

void manipularArchivos () {
  FILE *archivoEntrada, *archivoSalida;
  archivoEntrada = fopen("constantes.txt", "r");
  archivoSalida = fopen("clasificacion.txt", "w");

  if (archivoEntrada == NULL || archivoSalida == NULL) {
    printf("Ha ocurrido un error leyendo alguno de los archivos.\n");
    return;
  }

  fclose(archivoEntrada);
  fclose(archivoSalida);
  return;
}

int main () {
  manipularArchivos();
  char octal[9] = "01234567";
  char octalFalso[9] = "01234597";
  char decimal[9] = "12345690";
  char decimalFalso[9] = "9a234567";
  char hexa[9] = "0x1aF";
  char hexaFalso[9] = "0x1Ag";

  printf("Octal es %i\n",  constanteOctal(octal));
  printf("Octal falso es %i\n",  constanteOctal(octalFalso));
  printf("Decimal es %i\n",  constanteDecimal(decimal));
  printf("Decimal falso es %i\n",  constanteDecimal(decimalFalso));
  printf("Hexa es %i\n",  constanteHexa(hexa));
  printf("Hexa falso es %i\n",  constanteHexa(hexaFalso));

  return 0;
}
