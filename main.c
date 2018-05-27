#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define OCTAL " es una Constante Octal\n"
#define DECIMAL " es una Constante Decimal\n"
#define HEXADECIMAL " es una Constante Hexadecimal\n"
#define ERROR " no es una Constante Entera\n"
//Habia un Bug en que si habia un decimal que tenia un 0 despues del principio, entraba a octal, ya esta arreglado
//Saque varios BOOL y puse 2 INT para que sea un poco mas facil de leer
//Cree palabraCorrecta por las 3 funciones de BOOL Hexa, Octal, Decimal
//Use un switch para mejorar cuando devuelve el tipo de variable
//La funcion finpalabra la corre solo 1 vez en el if para evitar uso innecesario de la compu
//*Aca tiene que ver si el primer caracter es un 0 para que sea hexa u octal, pero en caso que el decimal tenga un 0, iba a entrar igual
//Por lo tanto hice que solo entrara al if ese solo si el 0 es el primer caracter

int PalabraCorrecta (char num, int validez){
  switch (validez) { //Devuelve validez = 0 Si no cumple con la condicion de cada tipo, en caso que cumple, devuelve la misma validez con la que vino
    case 1:
      if(num < '0' || num > '7')
        validez = 0;
      break;
    case 2:
      if (num < '0' || num > '9')
        validez = 0;
      break;
    case 3:
      if ((num < '0' || num > '9')  && (num < 'a' || num > 'f') && (num < 'A' || num > 'F'))
        validez = 0;
      break;
  }
  return validez;
}

void FinPalabra(int validez, FILE *archivoEscritura) {

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
  return;
}

void EscribirEsConstanteEntera(FILE *archivo, char texto[]) {
  fprintf(archivo, texto);
  return;
}

void CargarArchivo() {
  FILE *archivoLectura;
  FILE *archivoEscritura;

  char caracter; // El caracter que agarra del archivo
  int validez; // Valor del entero para saber que tipo es: 0 = No valido, 1 = Octal, 2 = Decimal, 3 = Hexa
  int numeroDeCaracter = 0; // Para saber en que numero de caracter del entero dado estamos

	archivoLectura = fopen("prueba.txt", "r");
	archivoEscritura = fopen("pruebaEscritura.txt", "w");

	if (archivoLectura == NULL) {
    printf("\nError de apertura del archivo. \n\n");
  } else {
    while((caracter = fgetc(archivoLectura)) != EOF) {
      numeroDeCaracter++;
      printf("%c", fputc(caracter, archivoEscritura));
        if (caracter == ' ' ) {
          if (validez == 3 && numeroDeCaracter == 3){ //En el caso de tener 0x o 0X solo, tiene que ser no valido, y yo lo hize aca
            validez = 0;
            FinPalabra(validez, archivoEscritura);
            numeroDeCaracter=0;
          } else { //Si el caracter es vacio, significa que termino el numero y va a FinPalabra a fijarse si que debe poner en el archivo de salida
          FinPalabra(validez, archivoEscritura);
          validez = 0; //Reseteo de variables cuando termina
          numeroDeCaracter=0;
          }
        } else {
        if ((caracter == '0' && numeroDeCaracter == 1) || validez == 1 || validez == 3 ) { //*Explicacion Arriba
          if (caracter == 'x' || caracter == 'X' || validez == 3 ) {
            if ((caracter == 'x' || caracter == 'X' ) && numeroDeCaracter == 2) {
              validez = 3;
            } else { //En caso de tener x algun numero despues del segundo, tiene que ser no valido
              validez = PalabraCorrecta(caracter, validez);
            }
          } else {
            validez = 1;
            validez = PalabraCorrecta(caracter, validez);
          }
        } else if (((caracter >= '1' && caracter <= '9') && numeroDeCaracter == 1 ) || validez == 2) {
          //Solo deberia entrar si el primer caracter es entre 1 y 9 o si ya fue dado como decimal anteriormente
          validez = 2;
          validez = PalabraCorrecta(caracter, validez);
        } else {
          validez = 0;
        }
      }
    }
  }
  fclose(archivoLectura);
  fclose(archivoEscritura);
  return;
}

int main() {
  CargarArchivo();
  return 0;
}
