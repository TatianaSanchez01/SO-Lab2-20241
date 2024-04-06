# Ejercicios de programación #

A continuación se colocan unos ejercicios de análisis y programación relacionados con el API de procesos con el objetivo de evaluar la comprensión y uso de dicho API en la solución de problemas de programación en C.

## Análisis de código ##

1. Dado el siguiente programa, explique cual es la salida de la línea comentada como ```LINE A```

```C
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int value = 5;
int main() {
    pid t pid;
    pid = fork();
    if (pid == 0) { /* child process */
        value += 15;
        return 0;
    }
    else if (pid > 0) { /* parent process */
        wait(NULL);
        printf("PARENT: value = %d",value); /* LINE A */
        return 0;
    }
}
```

Dado que el proceso hijo modifica su propia copia de value, el proceso padre continúa viendo el valor original (5). Por lo tanto, la salida de LINEA A será:

```C
    PARENT: value = 5
```

2. Incluyendo el proceso padre inicial ¿cuántos procesos son creados por el programa mostrado a continuación?

```C
#include <stdio.h>
#include <unistd.h>
int main() {
    /* fork a child process */
    fork();
    /* fork another child process */
    fork();
    /* and fork another */
    fork();
    return 0;
}
```

El programa crea un total de 4 procesos, incluyendo el proceso padre inicial.
    1. Primera llamada a fork: Crea un segundo proceso que es una copia del proceso padre. Ahora hay dos procesos en ejecución: el padre original y el hijo recién creado.
    2. Segunda llamada a fork: Se ejecuta en el proceso padre original y crea un tercer proceso, que es una copia del padre original. Ahora hay tres procesos en ejecución: el padre original, el hijo creado por la primera llamada a fork y el nuevo hijo creado por la segunda llamada.
    3. Tercera llamada a fork: Se ejecuta en el proceso padre original (no en los hijos) y crea un cuarto proceso, que es otra copia del padre original. Ahora hay cuatro procesos en ejecución: el padre original y tres hijos.

3. Incluyendo el proceso padre inicial ¿cuántos procesos  son creados por el programa mostrado a continuación?

```C
#include <stdio.h>
#include <unistd.h>

int main() {
    int i;
    for (i = 0; i < 4; i++)
        fork();
    return 0;
}
```

El programa crea un total de 15 procesos, incluyendo el proceso padre inicial.
    1. El bucle for se ejecuta 4 veces, lo que significa que se realizan 4 llamadas a fork.
    2. Cada llamada a fork crea un nuevo proceso hijo, independiente del proceso padre y de los demás hijos.
    3. Al finalizar el bucle for, hay 5 procesos en ejecución: el proceso padre original y 4 hijos.
    4. Cada uno de los 4 hijos también puede ejecutar fork. Sin embargo, en este programa, no se realizan más llamadas a fork después del bucle for.

4. En el siguiente código ¿la linea de codigo marcada como ```printf("LINE J")```  imprimirá el mensaje?

```C
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid t pid;
    /* fork a child process */
    pid = fork();
    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) { /* child process */
        execlp("/bin/ls","ls",NULL);
        printf("LINE J");
    }
    else { /* parent process */
        /* parent will wait for the child to complete */
        wait(NULL);
        printf("Child Complete");
    }
    return 0;
}
```

No, la línea de código marcada como printf("LINE J") no imprimirá el mensaje en la salida estándar.

5. Asumiendo que se tienen como pids para el padre y para el hijo los valores de 2600 y 2603 respectivamente. Identifique los valores del pid en las líneas comentadas como ```A```, ```B```, ```C``` y ```D```

```C
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid t pid, pid1;
    /* fork a child process */
    pid = fork();
    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) { /* child process */
        pid1 = getpid();
        printf("child: pid = %d",pid); /* A */
        printf("child: pid1 = %d",pid1); /* B */
    }
    else { /* parent process */
        pid1 = getpid();
        printf("parent: pid = %d",pid); /* C */
        printf("parent: pid1 = %d",pid1); /* D */
        wait(NULL);
    }
    return 0;
}
```
Line A (child): pid = 2603
Line B (child): pid1 = 2603
Line C (parent): pid = 2603
Line D (parent): pid1 = 2600


6. Dado el siguiente programa, ¿cuál sería la salida desplegada en las líneas comentadas como ```LINE X``` y ```LINE Y```?

```C
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#define SIZE 5
int nums[SIZE] = {0,1,2,3,4};

int main() {
    int i;
    pid t pid;
    pid = fork();
    if (pid == 0) {
        for (i = 0; i < SIZE; i++) {
            nums[i] *= -i;
            printf("CHILD: %d ",nums[i]); /* LINE X */
        }
    }
    else if (pid > 0) {
        wait(NULL);
        for (i = 0; i < SIZE; i++)
            printf("PARENT: %d ",nums[i]); /* LINE Y */
    }
    return 0;
}
```
El programa utiliza fork para crear el proceso hijo, y ambos padre e hijo modifican y comparten el arreglo de números

LINE X (CHILD): Output: -0 1 -4 9 -16
LINE Y (PARENT): Output: -0 1 -4 9 -16


## Problemas de programación ##

1. Escriba un programa que abra un archivo (con la llamada ```open()```) y entonces llame a ```fork()```. Nota: El siguiente [enlace](https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/) puede ser de utilidad para entender la llamada open().
   * ¿Pueden el padre y el hijo acceder al file descriptor retornado por ```open()```?
   * ¿Qué pasa si ellos empiezan a escribir el archivo de manera concurrente, es decir, a la misma vez?

2. Escriba un programa usando fork(). El proceso hijo imprimirá ```"Hello"```; el proceso padre imprimirá ```"goodbye"```. Usted deberá asegurar que el proceso hijo imprima siempre en primer lugar.

3. Escriba un programa que llame ```fork()``` y entonces llame alguna forma de exec() para correr el programa ```/bin/ls```. Intente probar todas las variaciones de la familia de funciones ```exec()``` incluyendo (en linux) ```execl()```, ```execle()```, ```execlp()```, ```execv()```, ```execvp()``` y ```execvpe()```. ¿Por qué piensa usted que existen tantas variaciones para la misma llamada básica?
   
4. Escriba ahora un programa que use ```wait()``` para esperar que el proceso hijo finalice su ejecución. ¿Cuál es el valor de retorno de la función ```wait()```?, ¿Qué pasa si usted usa la función ```wait``` en el hijo?

5. Haga un programa como el del ejercicio anterior con una breve modificación la cual consiste en usar ```waitpid()``` en lugar de ```wait()```, ¿cuándo podría ser ```waitpid()``` útil?

6. Escriba un programa que cree dos hijos y conecte la salida estándar de un hijo a la entrada estándar del otro usando la llamada a sistema ```pipe()```.

7. Escriba un programa en C llamado **time.c** que determine la cantidad de tiempo necesaria para correr un comando desde la línea de comandos. Este programa será ejecutado como "```time <command>```" y mostrará la cantidad de tiempo gastada para ejecutar el comando especificado. Para resolver el problema haga uso de ```fork()``` y ```exec()```, así como de la función ```gettimeofday()``` para determinar el tiempo transcurrido. 
   
   La estrategia general es hacer un fork para crear un proceso hijo el cual ejecutara el comando especificado. Sin embargo, antes de que el proceso hijo ejecute el comando espeficado, debera almacenar el tiempo actual (**starting time**). El padre invocará el wait para esperar por la culminación del proceso hijo. Luego, una vez que el proceso hijo culmine, el padre almacenara el tiempo actual en este punto (**ending time**). La diferencia entre los tiempos **inicial** y **final** (**starting** y **endind**) representará el tiempo gastado para ejecutar el comando. Por ejemplo la salida en pantalla de abajo muestra la cantidad de tiempo para correr el comando ```ls```:

```
./time ls
time.c
time

Elapsed time: 0.25422
```

