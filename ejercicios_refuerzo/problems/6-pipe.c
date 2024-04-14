#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    // Crear un pipe
    int fd[2];
    pipe(fd);

    // Crear dos procesos hijos
    pid_t pid1 = fork();
    if (pid1 == -1)
    {
        perror("Error al crear el primer proceso hijo");
        return 1;
    }

    pid_t pid2 = fork();
    if (pid2 == -1)
    {
        perror("Error al crear el segundo proceso hijo");
        return 1;
    }

    // Código para el primer proceso hijo
    if (pid1 == 0)
    {
        // Cerrar el extremo de lectura del pipe
        close(fd[0]);

        // Duplicar el extremo de escritura del pipe en la salida estándar
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        // Ejecutar un comando que escribe en la salida estándar
        execl("/bin/ls", "ls", "-l", NULL);
    }

    // Código para el segundo proceso hijo
    if (pid2 == 0)
    {
        // Cerrar el extremo de escritura del pipe
        close(fd[1]);

        // Duplicar el extremo de lectura del pipe en la entrada estándar
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        // Ejecutar un comando que lee de la entrada estándar
        execl("/usr/bin/wc", "wc", "-l", NULL);
    }

    // Código para el proceso padre
    else
    {
        // Cerrar los extremos del pipe que no se necesitan
        close(fd[0]);
        close(fd[1]);

        // Esperar a que ambos procesos hijos terminen
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
    }

    return 0;
}
