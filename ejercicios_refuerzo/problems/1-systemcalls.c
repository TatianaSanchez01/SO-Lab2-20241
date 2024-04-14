#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    // Abrir un archivo
    int fd = open("archivo.txt", O_RDWR | O_CREAT, 0664);
    if (fd == -1)
    {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Crear un proceso hijo
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Error al crear el proceso hijo");
        return 1;
    }

    // Código para el proceso padre
    if (pid > 0)
    {
        // Escribir en el archivo desde el proceso padre
        char mensaje_padre[] = "Hola desde el padre\n";
        write(fd, mensaje_padre, sizeof(mensaje_padre));

        // Esperar a que el proceso hijo termine
        wait(NULL);

        // Cerrar el archivo
        close(fd);
    }

    // Código para el proceso hijo
    else
    {
        // Escribir en el archivo desde el proceso hijo
        char mensaje_hijo[] = "Hola desde el hijo\n";
        write(fd, mensaje_hijo, sizeof(mensaje_hijo));

        // Cerrar el archivo
        close(fd);
    }

    return 0;
}

/**
 * Pregunta 1: 
 * ¿Pueden el padre y el hijo acceder al file descriptor retornado por ```open()```?
 * Sí, tanto el padre como el hijo pueden acceder al descriptor de archivo retornado
 * por open(). Esto se debe a que el descriptor de archivo se comparte entre el proceso
 * padre y el hijo después de la llamada a fork().
 * 
 * Pregunta 2: 
 * ¿Qué pasa si ellos empiezan a escribir el archivo de manera concurrente, es decir,
 * a la misma vez?
 * Si el padre y el hijo intentan escribir en el archivo de forma concurrente, el
 * resultado puede ser impredecible. El orden en que se escriben los datos no está
 * definido y es posible que se entremezclen.
 * 
 * Para evitar esto, se pueden utilizar técnicas de sincronización como semáforos
 * para controlar el acceso al archivo.
*/