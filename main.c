#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define OCTAL " es una constante Octal\n"
#define DECIMAL " es una constante Decimal\n"
#define HEXADECIMAL " es una constante Hexadecimal\n"
#define ERROR " no es una constante entera\n"

_Bool esDecimalUOctal (char constante, char tope) {
  return constante >= '0' && constante <= tope;
}

_Bool esHexa (char constante) {
  return (constante >= 'a' && constante <= 'f') || (constante >= 'A' && constante <= 'F');
}

void escribirArchivo (FILE *archivo,  char mensaje[], char constante[]) {
  fprintf(archivo, mensaje, constante);
  return;
}

void manipularArchivos () {
  FILE *archivoEntrada, *archivoSalida;
  archivoEntrada = fopen("constantes.txt", "r");
  archivoSalida = fopen("clasificacion.txt", "w");

  char actual = fgetc(archivoEntrada);
  while (actual !=  EOF) {

      actual = fgetc(archivoEntrada);
  }

  // escribirArchivo(archivoSalida, "%s", "s");
  // escribirArchivo(archivoSalida, "%s no es constante entera", "Hola");

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
