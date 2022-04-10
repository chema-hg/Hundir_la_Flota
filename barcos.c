#include <stdio.h>
#include <stdlib.h> // Para usar o rand() por ejemplo.
#include <string.h>

// Estructura de datos
struct barcos
{
    int tamanio;
};

// declaracion de funciones obligatorias
void colocarBarcosManualmente();
void colocarBarcosAutomaticamente();
void inicializarTablero(int *tablero, int filas, int columnas);
void imprimirTablero();
void comprobacionEspacioParaBarco();
void compruebaGanador();
void compruebaDisparo();
void juegoManual();
void juegoAutomatico();

// declaración de funciones auxiliares
void inicializarBarcos(struct barcos *info, int tam);
void guardar_archivo(struct barcos *datos);
void leer_Archivo(struct barcos *datos);
// declaracion de Menus
void menu_ConfigurarTableroBarcos();
void menu_jugar_ovuj();

// declaracion de variables globales
int N = 0;               // nº de filas
int M = 0;               // nº de columnas
int nBarcos = 0;         // nº de barcos
struct barcos barco[10]; // establecemos un máximo de 10 barcos
// declaracion como punteros de las 4 matrices de posiciones y disparos
int *matriz_pos_jugador = NULL; //matriz de posiciones del jugador
int *matriz_pos_computadora = NULL; //matriz de posiciones de la computadora
int *matriz_disparos_jugador = NULL; // marcador de disparos del jugador
int *matriz_disparos_computadora = NULL; // marcador de disparos de la computadora

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
                // LLama al submenu jugar ordenador versus jugador.
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
            printf("Los datos de leeran del archivo 'datos.txt'\n");
            printf("Pulse Intro para continuar...\n");
            getchar();
            leer_Archivo(barco);
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
            printf("Introduzca el número de barcos (máximo 10): \n");
            fgets(input, 10, stdin); // Lee una cadena del teclado
            opcion = atoi(input);    // Convertir el string a int
            if (opcion <= 0 || opcion>10)         // Si la entrada no es un número o es negativo o mayor que 10.
            {
                printf("\nERROR: DEBE INTRODUCIR UN NUMERO POSITIVO VÁLIDO\n");
                printf("Pulse Intro para continuar...\n");
                getchar();
                goto START_BARCOS;
            }
            else
            {
                nBarcos = opcion;
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
        switch (opcion)
        {
            case 1:
                // Inicializamos los 4 tableros y declaramos la memoria dinamica de los punteros.
                matriz_pos_jugador = (int *)malloc(sizeof(int *) * N * M);
                inicializarTablero(matriz_pos_jugador, N, M);
                matriz_pos_computadora = (int *)malloc(sizeof(int *) * N * M);
                inicializarTablero(matriz_pos_computadora, N, M);
                matriz_disparos_jugador = (int *)malloc(sizeof(int *) * N * M);
                inicializarTablero(matriz_disparos_jugador, N, M);
                matriz_disparos_computadora = (int *)malloc(sizeof(int *) * N * M);
                inicializarTablero(matriz_disparos_computadora, N, M);
                break;
            case 2:
                break;
            default:
                printf("Salir\n");
                break;
        }
    }
    /* Pendiente de completar y dejar funciones para cada opcion */
}

// Funciones Auxiliares
void inicializarBarcos(struct barcos *info, int tam)
{
    /* Inicializa todos los barcos, pidiendo su numero total y tamaño y comprobando que sean correctos
    y entren en el tablero. El numero de casillas del tablero ha de ser por lo menos el doble
    que las posiciones ocupadas por el barco.*/
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
    if ((total * 2) <= (N * M))
    {
        printf("\nBARCOS INICIALIZADOS CORRECTAMENTE\n");
        printf("Pulse Intro para continuar...\n");
        getchar();
        // Una vez inicializados los barcos, gurdamos las principales variables en un archivo.
        guardar_archivo(info);
    }
    else
    {
        printf("\nERROR: EL TAMAÑO TOTAL DE LOS BARCOS ES MAYOR QUE EL TAMAÑO DEL TABLERO\n");
        printf("AVISO!!! el número de casillas del tablero que son %d\n", N * M);
        printf("ha de ser al menos el doble de las posiciones ocupadas -%d- por los barcos\n", total);
        printf("Pulse Intro para continuar...\n");
        getchar();
        i = 0; // Reiniciar el bucle
        goto START_BARCOS;
    }
}
// Función para Guardar los datos en un archivo
void guardar_archivo(struct barcos *datos)
{
    /* En el archivo se guardan los datos de los barcos en formato:
    primera fila: N numero de filas
    segunda fila: M numero de columnas
    tercera fila: nBarcos numero de barcos
    cuarta y siguientes filas: numero de barco y tamaño del barco
    el numero de barco empieza en 0 y termina en nBarcos-1
    */

    FILE *archivo;
    archivo = fopen("datos.txt", "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    fprintf(archivo, "%d\n", N);       // Guardar el número de Filas
    fprintf(archivo, "%d\n", M);       // Guardar el número de Columnas
    fprintf(archivo, "%d\n", nBarcos); // Guardar el número de Barcos
    for (int i = 0; i < nBarcos; i++)
    {
        fprintf(archivo, "%d %d\n", i, datos[i].tamanio); // Guardar el tamaño de cada barco
    }
    fclose(archivo);
}

// Funcion para leer los datos de un archivo llamado datos.txt
void leer_Archivo(struct barcos *datos)
{
    int n_barco;
    FILE *f;
    f = fopen("datos.txt", "r");
    // si el archivo no puede abrirse devuelve Null por lo que
    // mostramos el mensaje de error y salimos del archivo.
    if (f == NULL)
    {
        fprintf(stderr, "Ha ocurrido un error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }
    fscanf(f, "%d", &N);       // Lee el número de filas de la primera linea del archivo datos.txt
    fscanf(f, "%d", &M);       // Lee el número de columnas de la segunda linea del archivo datos.txt
    fscanf(f, "%d", &nBarcos); // Lee el número de barcos de la tercera linea del archivo datos.txt
    for (int i = 0; i < nBarcos; i++)
    {
        fscanf(f, "%d %d", &n_barco, &datos[i].tamanio); // Lee el tamaño de cada barco de la cuarta y siguientes lineas del archivo datos.txt
    }
    fclose(f);
}

// Función para inicializar el tablero
void inicializarTablero(int *tablero, int filas, int columnas){
    /* Inicializa el tablero con todos los valores a 0.
    El tablero es un array de enteros, por lo que se inicializa con 0.
    El tablero es de N filas por M columnas.
    */
    int i, j;
    for (i = 0; i < filas; i++)
    {
        for (j = 0; j < columnas; j++)
        {
            tablero[i * columnas + j] = 0;
        }
    }

}