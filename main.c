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

_Bool posibleHexa (FILE *archivoEntrada) {
  char actual = fgetc(archivoEntrada);
  if (esDecimalUOctal(actual, '7')) {
    actual = fgetc(archivoEntrada);
    if (actual == 'x' || actual == 'X') {
      actual = fgetc(archivoEntrada);
      if (esDecimalUOctal(actual, '9') || esHexa(actual)) return true;
    }
  }
  return true;
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

  return 0;
}
