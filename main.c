#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define OCTAL " es una Constante Octal\n"
#define DECIMAL " es una Constante Decimal\n"
#define HEXADECIMAL " es una Constante Hexadecimal\n"
#define ERROR " no es una Constante Entera\n"


_Bool Decimal(char num, bool correcto) {
  correcto = (num >= '0' || num <= '9');
  return correcto;
}

_Bool Octal(char num, bool correcto) {
  correcto = (num >= '0' || num <= '7');
  return correcto;
}

_Bool Hexa(char num, bool correcto) {
  correcto = ((num >= '0' || num <= '9') && (num >= 'a' || num <= 'f') && (num >= 'A' || num <= 'F'));
  return correcto;
}

void FinPalabra(bool *correcto, int validez, bool *primeraSaltear, bool *hexaDistinto0X, FILE *archivoEscritura) {

    switch (validez) {
      case 1:
        EscribirEsConstanteEntera(archivoEscritura, OCTAL);
        break;
      case 2:
        EscribirEsConstanteEntera(archivoEscritura, DECIMAL);
        break;
      case 3:
        EscribirEsConstanteEntera(archivoEscritura, HEXADECIMAL);
        break;
      case 0:
        EscribirEsConstanteEntera(archivoEscritura, ERROR);
        break;
    }


  *correcto=true;
  validez=0;
  *primeraSaltear=false;
  *hexaDistinto0X=false;
  return;
}

void EscribirEsConstanteEntera(FILE *archivo, char texto[]) {
  fprintf(archivo, texto);
  return;
}

void CargarArchivo() {
  FILE *archivoLectura;
  FILE *archivoEscritura;

	char caracter;
  bool correcto = true;//se asegura de que la palabra sea correcta
  int validez;
  bool primeraSaltear = false;//se asegura que no revise si la X de hexadecimal es valida ni los espacios que separan los numeros
	bool hexaDistinto0X = false;//se asegura que el hexadecimal sea distinto a 0x o 0X

	archivoLectura = fopen("prueba.txt", "r");
	archivoEscritura = fopen("pruebaEscritura.txt", "w");

	if (archivoLectura == NULL) {
    printf("\nError de apertura del archivo. \n\n");
  } else {
    while((caracter = fgetc(archivoLectura)) != EOF) {
      validez = 0;
      printf("%c", fputc(caracter, archivoEscritura));
      if (caracter == '0' || validez == 1 || validez == 3) {
        if (caracter == 'x' || caracter == 'X' || validez == 3) {
          validez = 3;
          if (caracter == ' ') {
            FinPalabra(&correcto, validez, &primeraSaltear, &hexaDistinto0X, archivoEscritura);
          } else {
            if (primeraSaltear == false) {
              primeraSaltear = true;
              correcto = false;
            } else {
              if (hexaDistinto0X == false) {
                hexaDistinto0X = true;
                correcto = true;
              }
              correcto = Hexa(caracter, correcto);
            }
          }
        } else {
          validez = 1;
          if (caracter == ' ') {
            FinPalabra(&correcto, validez, &primeraSaltear, &hexaDistinto0X, archivoEscritura);
          } else {
            correcto = Octal(caracter, correcto);
          }
        }
      }
      else if ((caracter >= '1' && caracter <= '9') || validez == 2) {
        validez = 2;
        if (caracter == ' ') {
          FinPalabra(&correcto, validez, &primeraSaltear, &hexaDistinto0X, archivoEscritura);
        } else {
          correcto = Decimal(caracter, correcto);
        }
      } else {
        validez = 0;
        if (primeraSaltear == false) {
          primeraSaltear = true;
        }
        else if (caracter == ' ') {
          correcto = false;
          FinPalabra(&correcto, validez, &primeraSaltear, &hexaDistinto0X, archivoEscritura);
        }
      }
    }
    FinPalabra(&correcto, validez, &primeraSaltear, &hexaDistinto0X, archivoEscritura);
  }
  fclose(archivoLectura);
  fclose(archivoEscritura);
  return;
}

int main() {
  CargarArchivo();
  return 0;
}
