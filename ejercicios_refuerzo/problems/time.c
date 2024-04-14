#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Uso: %s <comando>\n", argv[0]);
        return 1;
    }

    // Obtener el tiempo inicial
    struct timeval start_time;
    gettimeofday(&start_time, NULL);

    // Crear un proceso hijo
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Error al crear el proceso hijo");
        return 1;
    }

    // Código para el proceso hijo
    if (pid == 0)
    {
        // Ejecutar el comando especificado
        execvp(argv[1], argv + 1);
        perror("Error al ejecutar el comando");
        exit(1);
    }

    // Código para el proceso padre
    else
    {
        // Esperar a que el proceso hijo termine
        wait(NULL);

        // Obtener el tiempo final
        struct timeval end_time;
        gettimeofday(&end_time, NULL);

        // Calcular el tiempo transcurrido
        double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                              (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

        // Imprimir el tiempo transcurrido
        printf("Tiempo transcurrido: %.6f\n", elapsed_time);
    }

    return 0;
}
