#include <stdio.h>
#include <stdlib.h> // Para usar rand() por ejemplo.
#include <string.h>
#include <time.h>   // Para usar la funcion time()
#include <unistd.h> // Para usar sleep()

// Estructura de datos
struct barcos
{
    int tamanio;
};

//------------------------------------------
// declaracion de funciones obligatorias
// -----------------------------------------
// la estrucutra barco, el numero de barcos nBarcos y la matriz matriz_pos_jugador. N y M son variables globales.)
void colocarBarcosManualmente(struct barcos *info, int numero_barcos, int *i_matriz_pos_jugador);
void colocarBarcosAutomaticamente(struct barcos *info, int numero_barcos, int *i_matriz_pos_jugador);
void inicializarTablero(int *tablero, int filas, int columnas);
void imprimirTablero(int *i_matriz_pos); // i_matriz_pos_jugador o i_matriz_pos_maquina
int comprobacionEspacioParaBarco(int *i_matriz_espacio, int ifila, int icolumna, int iorientacion, int tamanio_barco);
int compruebaGanador(int *matriz_barcos);
void compruebaDisparo(int *matriz_barcos, int *matriz_tiradas, int fila, int columna);
void juegoManual(int *matriz_pos_jugador, int *matriz_pos_computadora, int *matriz_disparos_jugador, int *matriz_disparos_computadora);
void juegoAutomatico(int *matriz_pos_jugador, int *matriz_pos_computadora, int *matriz_disparos_jugador, int *matriz_disparos_computadora);

// declaración de funciones auxiliares
void inicializarBarcos(struct barcos *info, int tam);
void guardar_archivo(struct barcos *datos);
void leer_Archivo(struct barcos *datos);
void colocarBarcos(); // contruye las 4 matrices que se usarán para el juego y las asigna a las variables globales
// declaracion de Menus
void menu_ConfigurarTableroBarcos();
void menu_jugar_ovuj();

// declaracion de variables globales
int N = 0;               // nº de filas
int M = 0;               // nº de columnas
int nBarcos = 0;         // nº de barcos
struct barcos barco[10]; // establecemos un máximo de 10 barcos
// declaracion como punteros de las 4 matrices de posiciones y disparos
int *matriz_pos_jugador = NULL;          // matriz de posiciones del jugador
int *matriz_pos_computadora = NULL;      // matriz de posiciones de la computadora
int *matriz_disparos_jugador = NULL;     // marcador de disparos del jugador
int *matriz_disparos_computadora = NULL; // marcador de disparos de la computadora

int main()
{
    // hundir la flota escrito en c

    // declaracion de variables
    int opcion = 0;
    char input[10];

    // Inicializar los números aleatorios.
    srand(time(NULL));

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
                // LLama al submenu jugar ordenador versus ordenador.
                // inicializamos las matrices
                colocarBarcos();
                // Colocamos los barcos del jugador en el tablero
                colocarBarcosAutomaticamente(barco, nBarcos, matriz_pos_jugador);
                // Colocamos los barcos del ordenador en el tablero
                colocarBarcosAutomaticamente(barco, nBarcos, matriz_pos_computadora);
                // Empezamos el juego de forma automatica
                juegoAutomatico(matriz_pos_jugador, matriz_pos_computadora, matriz_disparos_jugador, matriz_disparos_computadora);
                break;

            case 4:
                printf("\nYour Welcome for Playing my GAME!\n");
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
            printf("Los datos se leerán del archivo 'datos.txt'\n");
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
            fgets(input, 10, stdin);        // Lee una cadena del teclado
            opcion = atoi(input);           // Convertir el string a int
            if (opcion <= 0 || opcion > 10) // Si la entrada no es un número o es negativo o mayor que 10.
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
}

// Submenu jugar (ordenador versus jugador)
void menu_jugar_ovuj()
{
    int opcion = 0;
    char input[10];
    colocarBarcos(); // antes de cualquiera de estas opcines hay que crear las matrices y asignarles memoria.
START:               // Etiqueta para poder usar luego goto.
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
            // Colocamos los barcos del jugador en el tablero
            colocarBarcosAutomaticamente(barco, nBarcos, matriz_pos_jugador);
            // Colocamos los barcos del ordenador en el tablero
            colocarBarcosAutomaticamente(barco, nBarcos, matriz_pos_computadora);
            // Empezamos el juego de forma manual
            juegoManual(matriz_pos_jugador, matriz_pos_computadora, matriz_disparos_jugador, matriz_disparos_computadora);
            break;
        case 2:
            // Colocamos los barcos del jugador en el tablero de forma manual
            colocarBarcosManualmente(barco, nBarcos, matriz_pos_jugador);
            // Colocamos los barcos del ordenador en el tablero de forma automatica
            colocarBarcosAutomaticamente(barco, nBarcos, matriz_pos_computadora);
            // Empezamos el juego de forma manual
            juegoManual(matriz_pos_jugador, matriz_pos_computadora, matriz_disparos_jugador, matriz_disparos_computadora);
        default:
            printf("Salir\n");
            break;
        }
    }
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
        if (opcion <= 0)         // Si la entrada no es un numero
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
/* A esta función se le pasará una matriz (de barcos o de tiradas) y asignará el valor 0 a todas sus posicio-
nes. */
void inicializarTablero(int *tablero, int filas, int columnas)
{
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

// Colocar Barcos Automáticamente
/* A esta función se le pasará una matriz de barcos y su tamaño y la configuración de bar-
cos y colocará los barcos especificados en la configuración automáticamente mediante 
la generación de números aleatorios */
void colocarBarcosAutomaticamente(struct barcos *info, int numero_barcos, int *i_matriz_pos_jugador)
{
    int fila, columna, orientacion, tamanio, resultado;
    // Realiza un bucle con el número de barcos que se han introducido.
    // En vez de goto se puede usar una función auxiliar que se repita las mismas veces.
    for (int k = 0; k < numero_barcos; k++)
    {
    START_BUCLE:
        fila = rand() % N;
        columna = rand() % M;
        orientacion = rand() % 2; // 0 = horizontal, 1 = vertical
        tamanio = info[k].tamanio;

        // Comprobar que la posición del barco no esté ocupada y que entre el barco
        resultado = comprobacionEspacioParaBarco(i_matriz_pos_jugador, fila, columna, orientacion, tamanio);
        if (resultado == 1 && orientacion == 0) // Coloca los barcos horizontalmente
        {
            for (int i = 0; i < tamanio; i++)
            {
                i_matriz_pos_jugador[fila * M + columna + i] = tamanio;
            }
        }
        else if (resultado == 1 && orientacion == 1) // Coloca los barcos verticalmente.
        {
            for (int i = 0; i < tamanio; i++)
            {
                i_matriz_pos_jugador[(fila + i) * M + columna] = tamanio;
            }
        }

        else
        {
            k--;
        }
    }
}

// Imprime cualquier tablero que se le pase como parámetro
/* a esta función se le pasará una matriz (de barcos o de tiradas) e imprimirá de forma organizada todas
sus posiciones. */
void imprimirTablero(int *i_matriz_pos)
{
    int contador = 0;
    printf("    ");
    for (int k = 0; k < M; k++)
    {
        printf(" %d ", k);
    }
    printf("\n");
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d   ", contador);
        for (int j = 0; j < M; j++)
        {
            if (i_matriz_pos[i * M + j] < 0)
            {
                printf("%d ", i_matriz_pos[i * M + j]);
            }
            else
            {
                printf(" %d ", i_matriz_pos[i * M + j]);
            }
        }
        printf("\n");
        contador++;
    }
}

// Comprueba si el barco entra en la posición que se le pasa como parámetro
// y el espacio no está ocupado
/* A esta función se le pasará una matriz de barcos, una posición inicial (fila y columna),
un tamaño de barco y una orientación (vertical u horizontal).
Comprobará si es posible almacenar un barco del tamaño especificado en el tablero que se le pasa como parámetro toman-
do como posición inicial y orientación la especificada por los argumentos. 
Devolverá información sobre si es posible o no. */
int comprobacionEspacioParaBarco(int *i_matriz_espacio, int ifila, int icolumna, int iorientacion, int tamanio_barco)
{
    if (iorientacion == 0) // Si la orientación es horizontal
    {
        if (icolumna + tamanio_barco <= M) // Comprueba que el barco no se sale del tablero.
        {
            // Comprueba que no haya otro barco en la posición
            for (int i = 0; i < tamanio_barco; i++)
            {
                if (i_matriz_espacio[ifila * M + icolumna + i] != 0)
                {
                    return 0; // Si hay otro barco en la posición devuelve 0
                }
            }
            return 1; // Si el barco no se sale del tablero y no hay otro barco en la posición, devuelve 1.
        }
        else
        {
            return 0; // Si el barco se sale del tablero o no hay otro barco en la posición, devuelve 0.
        }
    }
    else // Si la orientación es vertical.
    {
        if (ifila + tamanio_barco <= N) // Comprueba que el barco no se sale del tablero
        {
            // Comprueba que no haya otro barco en la posición
            for (int i = 0; i < tamanio_barco; i++)
            {
                if (i_matriz_espacio[(ifila + i) * M + icolumna] != 0)
                {
                    return 0; //    Si hay otro barco en la posición devuelve 0
                }
            }
            return 1; // Si el barco no se sale del tablero y no hay otro barco en la posición, devuelve 1.
        }
        else
        {
            return 0; // Si el barco se sale del tablero o no hay otro barco en la posición, devuelve 0.
        }
    }
}
// Juego manual Computador vs Jugador.
/* Esta función realizará las operaciones necesarias para que el usuario adivine dónde tiene 
los barcos el ordenador. */
void juegoManual(int *matriz_pos_jugador, int *matriz_pos_computadora, int *matriz_disparos_jugador, int *matriz_disparos_computadora)
{
    char input[10];
    int opcion = -1;
    int fila, columna;
    int resultado = 0;
    do
    {
        system("clear");
        printf("*---------------------------- HUNDIR LA FLOTA ------------------------*\n");
        printf("\n");
        printf("*------------------  TU TABLERO DE BARCOS --------------------*\n");
        printf("\n");
        imprimirTablero(matriz_pos_jugador);
        printf("\n");
        printf("*------------------  TABLERO DE DISPAROS ----------------------*\n");
        printf("\n");
        imprimirTablero(matriz_disparos_jugador);
        printf("\n");
        printf("DISPARA: \n");
    // Introduce la fila y la columna que quieres disparar y verifica los datos introducidos.
    TURNO_JUGADOR:
        do
        {
            printf("Fila (0-%d): ", N - 1);
            fgets(input, 10, stdin);
            opcion = atoi(input);
            if (opcion <= 0 || opcion >= N)
            {
                if (input[0] == '0')
                {
                    opcion = 0;
                }
                else
                {
                    printf("\n");
                    printf("Error, introduce un número entre 0 y %d\n", N - 1);
                    printf("\n");
                    opcion = -1;
                }
            }
            fila = opcion;
        } while (opcion == -1);
        opcion = -1;
        do
        {
            printf("Columna (0-%d): ", M - 1);
            fgets(input, 10, stdin);
            opcion = atoi(input);
            if (opcion <= 0 || opcion >= M)
            {
                if (input[0] == '0')
                {
                    opcion = 0;
                }
                else
                {
                    printf("\n");
                    printf("Error, introduce un número entre 0 y %d\n", M - 1);
                    printf("\n");
                    opcion = -1;
                }
            }
            columna = opcion;
        } while (opcion == -1);
        // Si el jugador vuelve a disparar a una zona que ya lo hizo (-1=Agua) o vuelve a disparar
        // donde ya lo hizo y habia un barco(tocado es 1,2,3,4,...) reinicia la función.
        if ((matriz_disparos_jugador[fila * M + columna] == -1) || (matriz_disparos_jugador[fila * M + columna] > 0))
        {
            printf("Ya has disparado en esa posición.");
            getchar();
            goto TURNO_JUGADOR;
        }
        printf("JUGADOR:  ->  ");
        // getchar();
        // Comprueba si el disparo es correcto para el jugador.
        compruebaDisparo(matriz_pos_computadora, matriz_disparos_jugador, fila, columna);
        resultado = compruebaGanador(matriz_pos_computadora); // Comprueba si el jugador ha ganado.
        if (resultado == 1)
        {
            printf("\a\nHAS GANADO - JUGADOR 1 -!!!\n");
            printf("Pulsa una tecla para continuar...");
            getchar();
        }
        if (resultado != 1) // Si el jugador no ha ganado, pasa al siguiente turno.
        {
        TURNO_COMPUTADORA:
            // Turno de la computadora.
            fila = rand() % N;
            columna = rand() % M;
            // Comprueba si el disparo es correcto para la computadora.
            // Si el computardor vuelve a disparar a una zona que ya lo hizo (-1=Agua) o vuelve a disparar
            // donde ya lo hizo y habia un barco(tocado es 1,2,3,4,...) reinicia la función.
            if ((matriz_disparos_computadora[fila * M + columna] == -1) || (matriz_disparos_computadora[fila * M + columna] > 0))
            {
                goto TURNO_COMPUTADORA;
            }
            printf("\nCOMPUTADORA: F%d - C%d ->  ", fila, columna);
            compruebaDisparo(matriz_pos_jugador, matriz_disparos_computadora, fila, columna);
            resultado = compruebaGanador(matriz_pos_jugador); // Comprueba si la computadora ha ganado.
            if (resultado == 1)
            {
                printf("\a\nHAS PERDIDO - GANA LA COMPUTADORA -!!!\n");
                printf("Pulsa una tecla para continuar...");
                getchar();
            }
            if (resultado != 1)
                getchar();
        }
    } while (resultado == 0);
}

// A esta función se le pasan dos matrices (una de barcos y otra de tiradas) y una posición de disparo.
// Comprueba si hay un barco en esa posición. Si lo hay, actualizará esa posición en los barcos del contrario
// (que pasará a estar tocado) y en las tiradas del jugador (indicará que se ha tocado un barco). Si no lo hay
// indicará en las tiradas del jugador que en esa posición no hay ningún barco.
void compruebaDisparo(int *matriz_barcos, int *matriz_tiradas, int fila, int columna)
{
    int num_pos; // Número en esa posicion (tamaño del barco).
    if (matriz_barcos[fila * M + columna] == 0)
    {
        printf("Agua");
        matriz_tiradas[fila * M + columna] = -1; // en la matriz de tiradas, -1 es agua.
    }
    else
    {
        printf("\aTocado!!!");
        num_pos = matriz_barcos[fila * M + columna];    // Número en esa posicion (tamaño del barco).
        matriz_tiradas[fila * M + columna] = num_pos;   // Indica que se ha tocado un barco en la matriz de tiradas y su tamaño.
        matriz_barcos[fila * M + columna] = -(num_pos); // Indica que se ha tocado un barco cambiando el signo de su tamaño.
    }
}

// A esta función se le pasa una matriz de barcos y en función de si todos sus barcos están hundidos o no,
// devuelve un 1 o un 0. Esto pasará si todos los numeros de la matriz de barcos son negativos o iguales a cero.
int compruebaGanador(int *matriz_barcos)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (matriz_barcos[i * M + j] > 0)
            {
                return 0; // Si hay un barco que no está hundido habra una posicion con 1,2.. y , devuelve 0.
            }
        }
    }
    return 1; // Si todos los barcos están hundidos(matriz barcos todos los valores menores a 0), devuelve 1.
}

// Contruye las 4 matrices que se usarán para el juego y las asigna a las variables globales
// Declara la memoria dinámica de los punteros que se usan.
void colocarBarcos()
{
    matriz_pos_jugador = (int *)malloc(sizeof(int *) * N * M);
    inicializarTablero(matriz_pos_jugador, N, M);
    matriz_pos_computadora = (int *)malloc(sizeof(int *) * N * M);
    inicializarTablero(matriz_pos_computadora, N, M);
    matriz_disparos_jugador = (int *)malloc(sizeof(int *) * N * M);
    inicializarTablero(matriz_disparos_jugador, N, M);
    matriz_disparos_computadora = (int *)malloc(sizeof(int *) * N * M);
    inicializarTablero(matriz_disparos_computadora, N, M);
}

// funcion para colocar los barcos del jugador de forma manual.
/* A esta función se le pasará una
matriz de barcos y su tamaño y la configuración de barcos
y colocará los barcos especificados en la configuración solici-
tando la información necesaria al usuario. */
void colocarBarcosManualmente(struct barcos *info, int numero_barcos, int *i_matriz_pos_jugador)
{
    int fila, columna, orientacion, tamanio, resultado;
    int opcion = 0;
    char input[10];

    // Realiza un bucle con el número de barcos que se han introducido.
    // En vez de goto se puede usar una función auxiliar que se repita las mismas veces.
    for (int k = 0; k < numero_barcos; k++)
    {
        system("clear");
    START_BUCLE:
        printf("*--------------- COLOCANDO LOS BARCOS DEL JUGADOR ---------------*\n");
        printf("\n");
        imprimirTablero(i_matriz_pos_jugador);
        printf("\nColoca el barco %d de %d de tamaño %d\n", k + 1, numero_barcos, info[k].tamanio);

        // Se pide la fila donde colocaremos el barco
        do
        {
            printf("Fila (0-%d): ", N - 1);
            fgets(input, 10, stdin);
            opcion = atoi(input);
            if (opcion <= 0 || opcion >= N)
            {
                if (input[0] == '0')
                {
                    opcion = 0;
                }
                else
                {
                    printf("\n");
                    printf("Error, introduce un número entre 0 y %d\n", N - 1);
                    printf("\n");
                    opcion = -1;
                }
            }
            fila = opcion;
        } while (opcion == -1);
        opcion = -1;
        // Se pide la columna donde colocaremos el barco.
        do
        {
            printf("Columna (0-%d): ", M - 1);
            fgets(input, 10, stdin);
            opcion = atoi(input);
            if (opcion <= 0 || opcion >= M)
            {
                if (input[0] == '0')
                {
                    opcion = 0;
                }
                else
                {
                    printf("\n");
                    printf("Error, introduce un número entre 0 y %d\n", M - 1);
                    printf("\n");
                    opcion = -1;
                }
            }
            columna = opcion;
        } while (opcion == -1);
        opcion = -1;
        // Se pide la orientación del barco.
        do
        {
            printf("Orientación (0 - Horizontal, 1 - Vertical): ");
            fgets(input, 10, stdin);
            opcion = atoi(input);
            if (opcion <= 0 || opcion > 1)
            {
                if (input[0] == '0')
                {
                    opcion = 0;
                }
                else
                {
                    printf("\n");
                    printf("Error, introduce 0 - Horizontal o 1 - Vertical\n");
                    printf("\n");
                    opcion = -1;
                }
            }
            orientacion = opcion;
        } while (opcion == -1);
        // El tamaño ya esta dado por cada posición del barco.
        tamanio = info[k].tamanio;

        // Comprobar que la posición del barco no esté ocupada y que entre el barco
        resultado = comprobacionEspacioParaBarco(i_matriz_pos_jugador, fila, columna, orientacion, tamanio);
        if (resultado == 1 && orientacion == 0) // Coloca los barcos horizontalmente
        {
            for (int i = 0; i < tamanio; i++)
            {
                i_matriz_pos_jugador[fila * M + columna + i] = tamanio;
            }
        }
        else if (resultado == 1 && orientacion == 1) // Coloca los barcos verticalmente.
        {
            for (int i = 0; i < tamanio; i++)
            {
                i_matriz_pos_jugador[(fila + i) * M + columna] = tamanio;
            }
        }

        else
        {
            printf("\a");
            k--;
        }
    }
}

// funcion para definir el juego automatico
/* esta función realizará las operaciones necesarias para que se realice una partida automática, incluyen-
do la escritura en el archivo. */
void juegoAutomatico(int *matriz_pos_jugador, int *matriz_pos_computadora, int *matriz_disparos_jugador, int *matriz_disparos_computadora)
{
    int fila, columna;
    int resultado = 0;
    do
    {
        system("clear");
        printf("\n");
        printf("*------------------  TU TABLERO DE BARCOS --------------------*\n");
        printf("\n");
        imprimirTablero(matriz_pos_jugador);
        printf("\n");
        printf("*------------------  TABLERO DE DISPAROS ----------------------*\n");
        printf("\n");
        imprimirTablero(matriz_disparos_jugador);
    // printf("\n");
    // Introduce la fila y la columna que quieres disparar y verifica los datos introducidos.
    TURNO_JUGADOR:
        fila = rand() % N;
        columna = rand() % M;
        // Si el jugador vuelve a disparar a una zona que ya lo hizo (-1=Agua) o vuelve a disparar
        // donde ya lo hizo y habia un barco(tocado es 1,2,3,4,...) reinicia la función.
        if ((matriz_disparos_jugador[fila * M + columna] == -1) || (matriz_disparos_jugador[fila * M + columna] > 0))
        {
            goto TURNO_JUGADOR;
            // juegoAutomatico(matriz_pos_jugador, matriz_pos_computadora, matriz_disparos_jugador, matriz_disparos_computadora);
        }
        printf("\nJUGADOR:  ->  F%d - C%d\t", fila, columna);
        // Comprueba si el disparo es correcto para el jugador.
        compruebaDisparo(matriz_pos_computadora, matriz_disparos_jugador, fila, columna);
        resultado = compruebaGanador(matriz_pos_computadora); // Comprueba si el jugador ha ganado.
        if (resultado == 1)
        {
            printf("\a\nHAS GANADO - JUGADOR 1 -!!!\n");
            printf("Pulsa una tecla para continuar...");
            getchar();
        }
        if (resultado != 1) // Si el jugador no ha ganado, pasa al siguiente turno.
        {
        TURNO_COMPUTADORA:
            // Turno de la computadora.
            fila = rand() % N;
            columna = rand() % M;
            // Comprueba si el disparo es correcto para la computadora.
            // Si el computardor vuelve a disparar a una zona que ya lo hizo (-1=Agua) o vuelve a disparar
            // donde ya lo hizo y habia un barco(tocado es 1,2,3,4,...) reinicia la función.
            if ((matriz_disparos_computadora[fila * M + columna] == -1) || (matriz_disparos_computadora[fila * M + columna] > 0))
            {
                goto TURNO_COMPUTADORA;
            }
            printf("\tCOMPUTADORA: F%d - C%d ->  ", fila, columna);
            compruebaDisparo(matriz_pos_jugador, matriz_disparos_computadora, fila, columna);
            resultado = compruebaGanador(matriz_pos_jugador); // Comprueba si la computadora ha ganado.
            if (resultado == 1)
            {
                printf("\a\nHAS PERDIDO - GANA LA COMPUTADORA -!!!\n");
                printf("Pulsa una tecla para continuar...");
                getchar();
            }
            // retrasa un segundo para ver los resultados.
            if (resultado != 1)
                sleep(1);
        }
    } while (resultado == 0);
}
