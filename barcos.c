#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de datos
struct barcos
{
    int tamanio;
};

// declaracion de funciones obligatorias
void colocarBarcosManualmente();
void colocarBarcosAutomaticamente();
void inicializarTablero();
void imprimirTablero();
void comprobacionEspacioParaBarco();
void compruebaGanador();
void compruebaDisparo();
void juegoManual();
void juegoAutomatico();

// declaración de funciones auxiliares
void inicializarBarcos(struct barcos *info, int tam);

// declaracion de Menus
void menu_ConfigurarTableroBarcos();
void menu_jugar_ovuj();

// declaracion de variables globales
int N = 0;       // nº de filas
int M = 0;       // nº de columnas
int nBarcos = 0; // nº de barcos

int main()
{
    // hundir la flota escrito en c

    // declaracion de variables
    int opcion = 0;
    char input[10];

    // llamar al menu de opciones
    while (opcion != 4)
    {
        system("clear");
        printf("*---------------- HUNDIR LA FLOTA ----------------*\n");
        printf("                                                   \n");
        printf("1.- Configurar el tablero y los barcos\n");
        printf("2.- Jugar (Ordenador vs jugador)\n");
        printf("3.- Jugar (Ordenador vs ordenador)\n");
        printf("4.- Salir\n");
        printf("                                                   \n");
        printf("*-------------------------------------------------*\n");
        printf("SELECCIONE UNA OPCION: ");
        // El condicional es para que el usuario ingrese un numero entero
        // si mete una letra o un caracter no lo toma como un numero.
        fgets(input, 10, stdin);
        opcion = atoi(input);
        if (opcion <= 0 || opcion > 4 || strlen(input) > 2)
        {
            printf("\nERROR: DEBE INTRODUCIR UN NUMERO VÁLIDO\n");
            printf("Pulse Intro para continuar...\n");
            // Limpiar el buffer
            getchar();
        }
        else
        {
            switch (opcion)
            {
            case 1:
                // LLama al submenu configurar tablero y barcos.
                menu_ConfigurarTableroBarcos();
                break;

            case 2:
                // LLama al submenur jugar ordenador versus jugador.
                menu_jugar_ovuj();
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

// SUBMENUS

// Configurar tablero y los barcos
void menu_ConfigurarTableroBarcos()
{
    int opcion = 0;
    char input[10];
get_input: // Etiqueta para poder usar luego goto.
    system("clear");
    printf("*--- CONFIGURAR EL TABLERO Y LOS BARCOS ---*\n");
    printf("                                            \n");
    printf("1.- Utilizar configuración almacenada en un archivo\n");
    printf("2.- Indicar una nueva configuración\n");
    printf("3.- Volver\n");
    printf("                                            \n");
    printf("--------------------------------------------\n");
    printf("SELECCIONE UNA OPCION: ");
    fgets(input, 10, stdin);                            // Lee una cadena del teclado
    opcion = atoi(input);                               // Convertir el string a int
    if (opcion == 0 || opcion > 3 || strlen(input) > 2) // Si la entrada no es un numero o el string es mayor que 2 (numero mas \0)
    {
        printf("\nERROR: DEBE INTRODUCIR UN NUMERO VÁLIDO\n");
        printf("Pulse Intro para continuar...\n");
        getchar();
        goto get_input;
    }
    else
    {
        switch (opcion)
        {

        case 1:
            printf("\nUtilizar configuración almacenada en un archivo\n");
            break;
        case 2:
            printf("\nCONFIGURACION DEL TABLERO\n");
            printf("                                          \n");
        START_FILAS:
            printf("Introduzca el número de filas: \n");
            fgets(input, 10, stdin); // Lee una cadena del teclado
            opcion = atoi(input);    // Convertir el string a int
            if (opcion <= 0)         // Si la entrada no es un numero o el string es mayor que 2 (numero mas \0)
            {
                printf("\nERROR: DEBE INTRODUCIR UN NUMERO POSITIVO VÁLIDO\n");
                printf("Pulse Intro para continuar...\n");
                getchar();
                goto START_FILAS;
            }
            else
            {
                N = opcion;
            }
        START_COLUMNAS:
            printf("Introduzca el número de columnas: \n");
            fgets(input, 10, stdin); // Lee una cadena del teclado
            opcion = atoi(input);    // Convertir el string a int
            if (opcion <= 0)         // Si la entrada no es un numero o el string es mayor que 2 (numero mas \0)
            {
                printf("\nERROR: DEBE INTRODUCIR UN NUMERO POSITIVO VÁLIDO\n");
                printf("Pulse Intro para continuar...\n");
                getchar();
                goto START_COLUMNAS;
            }
            else
            {
                M = opcion;
            }
        START_BARCOS:
            printf("Introduzca el número de barcos: \n");
            fgets(input, 10, stdin); // Lee una cadena del teclado
            opcion = atoi(input);    // Convertir el string a int
            if (opcion <= 0)         // Si la entrada no es un numero o el string es mayor que 2 (numero mas \0)
            {
                printf("\nERROR: DEBE INTRODUCIR UN NUMERO POSITIVO VÁLIDO\n");
                printf("Pulse Intro para continuar...\n");
                getchar();
                goto START_BARCOS;
            }
            else
            {
                nBarcos = opcion;
                struct barcos barco[nBarcos];
                inicializarBarcos(barco, nBarcos);
                break;
            }

        default:
            printf("Salir\n");
            break;
        }
    }
    /* Pendiente de completar y dejar funciones para cada opcion */
}

// Submenu jugar (ordenador versus jugador)
void menu_jugar_ovuj()
{
    int opcion = 0;
    char input[10];
START: // Etiqueta para poder usar luego goto.
    system("clear");
    printf("*--- Opción 2. JUGAR (ORDENADOR vs JUGADOR). ---*\n");
    printf("                                                 \n");
    printf("1.- Colocar los Barcos de forma automática.\n");
    printf("2.- Colocar los Barcos de forma manual.\n");
    printf("3.- Volver.\n");
    printf("                                                 \n");
    printf("-------------------------------------------------\n");
    printf("SELECCIONE UNA OPCION: ");
    fgets(input, 10, stdin);                            // Lee una cadena del teclado
    opcion = atoi(input);                               // Convertir el string a int
    if (opcion == 0 || opcion > 3 || strlen(input) > 2) // Si la entrada no es un numero o el string es mayor que 2 (numero mas \0)
    {
        printf("\nERROR: DEBE INTRODUCIR UN NUMERO VÁLIDO\n");
        printf("Pulse Intro para continuar...\n");
        getchar();
        goto START;
    }
    else
    {
        printf("sub_menu opcion 2\n");
    }
    /* Pendiente de completar y dejar funciones para cada opcion */
}

// Funciones Auxialiares
void inicializarBarcos(struct barcos *info, int tam)
{
    int i;
    int opcion = 0;
    char input[10];
    for (i = 0; i < tam; i++)
    {
    START_BARCOS: // Etiqueta para poder usar luego goto.
        printf("Introduzca el tamaño del barco %d: \n", i + 1);
        fgets(input, 10, stdin); // Lee una cadena del teclado
        opcion = atoi(input);    // Convertir el string a int
        if (opcion <= 0)         // Si la entrada no es un numero o el string es mayor que 2 (numero mas \0
        {
            printf("\nERROR: DEBE INTRODUCIR UN NUMERO VÁLIDO\n");
            printf("Pulse Intro para continuar...\n");
            getchar();
            goto START_BARCOS;
        }
        else
        {
            info[i].tamanio = opcion;
        }
    }
    int total = 0;
    i = 0;
    for (i = 0; i < tam; i++)
    {
        total += info[i].tamanio;
    }
    // if (total <= 2*N || total <= 2*M) ANTES
    if ((total*2) <= (N*M))
    {
        printf("\nBARCOS INICIALIZADOS CORRECTAMENTE\n");
        printf("Pulse Intro para continuar...\n");
        getchar();
    }
    else
    {
        printf("\nERROR: EL TAMAÑO TOTAL DE LOS BARCOS ES MAYOR QUE EL TAMAÑO DEL TABLERO\n");
        printf("AVISO!!! el número de casillas del tablero que son %d\n", N*M);
        printf("ha de ser al menos el doble de las posiciones ocupadas -%d- por los barcos\n", total);
        printf("Pulse Intro para continuar...\n");
        getchar();
        i = 0; // Reiniciar el bucle
        goto START_BARCOS;
    }
}
/* En esta funcion hay QUE TERMINAR DE GUARDAR LOS DATOS EN UN FICHERO.*/