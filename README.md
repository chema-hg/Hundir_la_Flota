# Hundir_la_Flota

**1. Desarrollo del juego**

El juego consiste en adivinar en un panel de N casillas de alto
por M casillas de ancho dónde se sitúan los barcos del contrincante. 
Gana el que lo consiga antes.
Cada jugador, por turnos, indicará una fila (número de 0 a N-1)
y una columna (número de 0 a M-1). Si el contrincante tiene en esa
posición un barco indicará “Tocado” y el número de posiciones que
ocupa ese barco. En caso contrario indicará “Agua”. A continuación
será el turno del otro jugador. Este proceso se repetirá hasta que
todas las casillas donde estén los barcos del contrincante hayan
sido “Tocadas”.
NOTA: no es obligatorio indicar si un barco ha sido “Hundido”
(todas las casillas que ocupa han sido “Tocadas”).

**1.1.  Componentes básicos**

**1.1.1. Tablero de juego**

1. El programa tiene 4 matrices. Dos para cada jugador. En una
se almacenan los tiros recibidos por el contrincante. En la
otra, los tiros realizados a los barcos del contrincante.
2. El jugador sólo podrá ver sus dos matrices (disparos realizados,
 posición de sus barcos).
3. El tamaño N y M lo especificará el usuario al iniciar el
juego y será obligatorio configurar el tamaño del tablero
asi como el número de barcos antes de empezar a jugar.

**1.1.2. Tipos de barcos**

La flota de barcos es configurable por el usuario. Se indicará cuántos
barcos se utilizarán y cómo son de grandes (cuántas posiciones ocupan) al
inicio de la partida. La configuración que aparece por defecto en el 
archivo datos.txt en relación a los barcos es la siguiente:

– 4 barcos que ocupan 1 posición.

– 3 barcos que ocupan 2 posiciones.

– 2 barcos que ocupan 3 posiciones.

– 1 barco que ocupa 4 posiciones.


**1.1.3. Posición de los barcos**

A la hora de colocar los barcos hay que tener en cuenta:

– En una posición sólo puede haber un barco.

– Para los barcos que ocupan más de una posición han de ocupar 
casillas consecutivas (verticales u horizontales).

– Los barcos que ocupan 1 posición pueden ir en cualquier lugar 
de la matriz.

– Todas las posiciones que ocupa un barco han de estar dentro
del tablero.

– Los barcos pueden estar juntos sin que tenga que haber necesariamente
espacios en blanco alrededor de los mismos.

**1.2.Reglas del juego**

Inicialmente se muestra un menú con las siguientes opciones:

1. Configurar el tablero y los barcos a utilizar.
2. Jugar (ordenador vs jugador).
3. Jugar (ordenador vs ordenador).
4. Salir.

El usuario podrá elegir una de esas 4 opciones.

**1.2.1. Opción 1. Configurar el tablero y los barcos a utilizar.**

Si se elige esta opción, se muestrá el siguiente menú:
1. Utilizar una configuración almacenada en un archivo.
2. Indicar una nueva configuración.
3. Volver.

Si se escoge la opción 1, se leerá el archivo "datos.txt" donde
estará la configuración del tablero y los barcos.
Si se escoge la opción 2, se introducirá el tamaño del tablero y de los
barcos a utilizar (cuántos y de qué tamaño cada uno) con una restricción
(el número de casillas del tablero ha de ser al menos el doble de las 
posiciones ocupadas por los barcos).

Se guardará esta configuración en el archivo "datos.txt" con 
la siguiente estructura:

primera línea: número de filas del tablero;

segunda línea: número de columnas del tablero;

tercera línea: número de barcos;

cuarta línea y sucesivas:
número de barco  número de barcos de esas posiciones número de posiciones que ocupan).

Con la opción 3 se vuelve al menú principal.


**1.2.2. Opción 2. Jugar (ordenador vs jugador).**

Una vez elegida esta opción, nos mostrará el siguiente menú:

1. Colocar los barcos de forma automática.
2. Colocar los barcos de forma manual.
3. Volver.

Si se elige la opción 1, los barcos se colocarán de forma automática.

Si se elige la opción 2, el usuario deberá introducir, para cada
barco, la fila y columna donde lo quiere almacenar y si lo quiere en
vertical u horizontal.
Se supone que el barco, si se quiere almacenar en posición horizontal 
ocupa las columnas siguientes a la columna especificada (todas en la misma fila) 
y si se quiere almacenar en posición vertical, ocupa las filas siguientes 
a la fila dada (en la misma columna).

A continuación, se comenzará a jugar de forma manual.
Para la jugada (fila,columna) especificada se indicará si no hay ningún barco 
en dicha posición (Agua) o si hay alguno (Tocado y cuántas posiciones tiene
el barco). No se indicará si se ha hundido un barco ya que se ve en pantalla.

**1.2.3. Opción 2. Jugar (ordenador vs ordenador).**
Se jugará de forma automática, la máquina contra si misma.
El computador tomará el mando del jugador 1 y moverá automaticamente
por él. Al final mostrará el ganador.

***1.2.4. Opción 3. Salir.***

Al elegir esta opción, finaliza la ejecución del programa.

