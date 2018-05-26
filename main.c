#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define OCTAL " es una Constante Octal\n"
#define DECIMAL " es una Constante Decimal\n"
#define HEXADECIMAL " es una Constante Hexadecimal\n"
#define ERROR " no es una Constante Entera\n"

_Bool Decimal(char num, bool correcto)
{
    if(num < '0' || num > '9'){correcto=false;}
    return correcto;
}

_Bool Octal(char num, bool correcto)
{
    if(num < '0' || num > '7'){correcto=false;}
    return correcto;
}

_Bool Hexa(char num, bool correcto)
{
    if((num < '0' || num > '9') && (num < 'a' || num > 'f') && (num < 'A' || num > 'F')){correcto=false;}
    return correcto;
}

void FinPalabra(bool *correcto, bool *octal, bool *hexa, bool *decimal, bool *novalido, bool *primeraSaltear, bool *hexaDistinto0X, FILE *archivoEscritura)
{
    if(*correcto)
    {
        if(*octal){EscribirEsConstanteEntera(archivoEscritura, OCTAL);}
        else if(*decimal){EscribirEsConstanteEntera(archivoEscritura, DECIMAL);}
        else if(*hexa){EscribirEsConstanteEntera(archivoEscritura, HEXADECIMAL);}
    }
    else {EscribirEsConstanteEntera(archivoEscritura, ERROR);}

    *correcto=true;
    *octal=false;
    *hexa=false;
    *decimal=false;
    *novalido=false;
    *primeraSaltear=false;
    *hexaDistinto0X=false;
    return;
}

void EscribirEsConstanteEntera(FILE *archivo, char texto[])
{
    fprintf(archivo, texto);
    return;
}

void CargarArchivo()
{
    FILE *archivoLectura;
    FILE *archivoEscritura;

	char caracter;
  bool correcto=true;//se asegura de que la palabra sea correcta
  bool octal=false;//se asegura de tomar la palabra como octal
  bool hexa=false;//se asegura de tomar la palabra como hexa
  bool decimal=false;//se asegura de tomar la palabra como decimal
  bool novalido=false;//se asegura de validar toda la palabra cuando no es valida
  bool primeraSaltear=false;//se asegura que no revise si la X de hexadecimal es valida ni los espacios que separan los numeros
	bool hexaDistinto0X=false;//se asegura que el hexadecimal sea distinto a 0x o 0X

	archivoLectura = fopen("prueba.txt","r");
	archivoEscritura = fopen("pruebaEscritura.txt","w");

	if (archivoLectura == NULL)
    {
        printf("\nError de apertura del archivo. \n\n");
    }
    else
    {
        while((caracter = fgetc(archivoLectura)) != EOF)
        {
            printf("%c",fputc(caracter, archivoEscritura));
            if(!novalido && !decimal && (caracter == '0' || octal || hexa))     //ES OCTAL O HEXADECIMAL
            {
                 if(caracter == 'x' || caracter == 'X' || hexa)     //ES HEXADECIMAL
                 {
                    hexa=true;
                    octal=false;
                    if(caracter == ' ')
                    {
                        FinPalabra(&correcto, &octal, &hexa, &decimal, &novalido, &primeraSaltear, &hexaDistinto0X, archivoEscritura);
                    }
                    else
                    {
                        if(primeraSaltear == false)
                        {
                            primeraSaltear=true;
                            correcto=false;
                        }
                        else
                        {
                            if(hexaDistinto0X==false)
                                {
                                    hexaDistinto0X=true;
                                    correcto=true;
                                }
                            correcto=Hexa(caracter, correcto);
                        }
                    }
                }
                else    //ES OCTAL
                {
                    octal=true;
                    if(caracter == ' ')
                    {
                        FinPalabra(&correcto, &octal, &hexa, &decimal, &novalido, &primeraSaltear, &hexaDistinto0X, archivoEscritura);
                    }
                    else{correcto=Octal(caracter, correcto);}
                }
            }
            else if(!novalido && ((caracter >= '1' && caracter <= '9') || decimal))     //ES DECIMAL
            {
                decimal=true;
                if(caracter == ' ')
                {
                    FinPalabra(&correcto, &octal, &hexa, &decimal, &novalido, &primeraSaltear, &hexaDistinto0X, archivoEscritura);
                }
                else{correcto=Decimal(caracter, correcto);}
            }
            else        //NO ES CONSTANTE ENTERA
            {
                novalido=true;
                if(primeraSaltear == false){primeraSaltear=true;}
                else if(caracter == ' ')
                {
                    correcto=false;
                    FinPalabra(&correcto, &octal, &hexa, &decimal, &novalido, &primeraSaltear, &hexaDistinto0X, archivoEscritura);
                }

            }
        }
        FinPalabra(&correcto, &octal, &hexa, &decimal, &novalido, &primeraSaltear, &hexaDistinto0X, archivoEscritura);
    }
    fclose(archivoLectura);
    fclose(archivoEscritura);
    return;
}
int main() {
  CargarArchivo();
  return 0;
}
