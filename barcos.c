#include <stdio.h>
#include <stdlib.h>


// declaracion de funciones
void colocarBarcosManualmente();
void colocarBarcosAutomaticamente();
void inicializarTablero();
void imprimirTablero();
void comprobacionEspacioParaBarco();
void compruebaGanador();
void compruebaDisparo();
void juegoManual();
void juegoAutomatico();


int main()
{
    // hundir la flota escrito en c

    // declaracion de variables
    int opcion = 0;

    // llamar al menu de opciones
    while (opcion != 4)
    {
        printf("*---------------- Hundir la flota ---------------*\n");
        printf("1.- Configurar el tablero y los barcos\n");
        printf("2.- Jugar (Ordenador vs jugador)\n");
        printf("3.- Jugar (Ordenador vs ordenador)\n");
        printf("4.- Salir\n");
        printf("*------------------------------------------------*\n");
        printf("SELECCIONE UNA OPCION: ");
        // El condicional es para que el usuario ingrese un numero entero
        // si mete una letra o un caracter no lo toma como un numero.
        if (scanf("%d", &opcion)==0)
        {
            printf("\nERROR: DEBE INTRODUCIR UN NUMERO VÁLIDO\n");
            // Limpiar el buffer
            getchar();
            getchar();
            system("clear");
        }
        else
        {
            switch (opcion)
            {
            case 1:
                printf("\n  Configurar el Tablero y los Barcos\n");
                printf("*---------------------------------------*\n");
                printf("1.- Utilizar configuración almacenada en un archivo\n");
                printf("2.- Indicar una nueva configuración\n");
                printf("3.- Volver\n");
                printf("*---------------------------------------*\n");
                printf("SELECCIONE UNA OPCION: ");
                if (scanf("%d", &opcion)==0)
                {
                    printf("\nERROR: DEBE INTRODUCIR UN NUMERO VÁLIDO\n");
                    // Limpiar el buffer
                    getchar();
                    getchar();
                    system("clear");
                }
                else
                {
                   printf("sub_menu opcion 1\n");
                }
                           
            case 2:
                printf("\nJugar (Ordenador vs jugador)\n");
                break;
            case 3:
                printf("\nJugar (Ordenador vs ordenador)\n");
                break;
            case 4:
                printf("\nSALIR\n");
                break;
            default:
                printf("\nERROR: DEBE INTRODUCIR UNA OPCION VALIDA\n");
                break;
            }
        }

    }
    return 0;
}

