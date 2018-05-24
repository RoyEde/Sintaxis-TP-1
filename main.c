#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

_Bool Decimal (char num, bool correcto) {
  if (num<'0'||num>'9') {
    correcto=false;
  }
  return correcto;
}

_Bool Octal (char num, bool correcto) {
  if (num<'0'||num>'7') {
    correcto=false;
  }
  return correcto;
}

_Bool Hexa (char num, bool correcto) {
  if ((num<'0'||num>'9')&&num!='a'&&num!='A'&&num!='b'&&num!='B'&&num!='c'&&num!='C'&&num!='d'&&num!='D'&&num!='e'&&num!='E'&&num!='f'&&num!='F') {
    //printf("\n Char: %c -Correcto: %d \n",num,correcto);
    correcto=false;
  }
  return correcto;
}


void CargarArchivo () {
  FILE *archivoLectura;
  FILE *archivoEscritura;
  char dir1[] = "C:\\Users\\Equipo\\Desktop\\Sintaxis-TP-1-codigo-sebi\\prueba.txt";
  char dir2[] = "C:\\Users\\Equipo\\Desktop\\Sintaxis-TP-1-codigo-sebi\\pruebaEscritura.txt";
  int ContadorDecimal = 0;
  int ContadorOctal = 0;
  int ContadorHexa = 0;
  char caracter;
  int i = 0;                  //revisa que el numero es decimal, octal, hexa o ninguno de ellos
  bool correcto = true;       //revisa que el numero sea valido
  bool primeraSaltear = false;//se asegura que no revise si la X de hexadecimal es valida ni los espacios que separan los numeros
  archivoLectura = fopen (dir1,"r");
  archivoEscritura = fopen (dir2,"a+t");

  if (archivoLectura == NULL) {
    printf("\nError de apertura del archivo. \n\n");
  } else {
    while ((caracter = fgetc(archivoLectura)) != EOF) {
      printf("%c", fputc(caracter, archivoEscritura));
      if (caracter == '0' || i == 1 || i == 2) {
        if (caracter == 'x' || caracter == 'X' || i == 2) {
          i = 2;
          if (caracter == ' ') {
            if (correcto == true) {
              //archivoEscritura,"%s",
              printf("Hexa\n");
              ContadorHexa = ContadorHexa + 1; //contador de hexa
            } else printf("No es valido\n");
            i = 0;
            correcto = true;
            primeraSaltear = false;
          } else {
            if (primeraSaltear == false) {
              primeraSaltear = true;
            } else correcto = Hexa(caracter, correcto);
          }
        } else {
          i = 1;
          if (caracter == ' ') {
            if (correcto == true) {
                printf("Octal\n");
                ContadorOctal = ContadorOctal + 1;
            }else printf("No es valido\n");
            i = 0;
            correcto = true;
          }
          else correcto=Octal(caracter, correcto);
        }
      }
      else if ((caracter >= '1' && caracter <= '9') || i == 3) {
        i = 3;
        if (caracter == ' ') {
          if (correcto == true) {
                printf("Decimal\n");
            ContadorDecimal = ContadorDecimal +1;//contarodr de decimales
          }else printf("No es valido\n");
          i = 0;
          correcto = true;
        } else correcto = Decimal(caracter, correcto);
      } else {
        if (primeraSaltear == false) primeraSaltear = true;
        else {
          printf("No es valido\n");primeraSaltear = false;
        }
        i = 0;
        correcto = true;
      }
    }
  }
  printf("\n\nSe detectaron:\n\n%i numero/s en decimal.\n%i numero/s en octal.\n%i numero/s en Hexadecimal.\n\n",ContadorDecimal,ContadorOctal,ContadorHexa);
  fclose(archivoLectura);
  fclose(archivoEscritura);
}

int main () {
  CargarArchivo();
  return 0;
}
