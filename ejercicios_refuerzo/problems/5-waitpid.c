#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> // Include the sys/wait.h header to resolve warnings

int main()
{
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
        // Ejecutar un comando
        execl("/bin/ls", "ls", "-l", NULL);
    }

    // Código para el proceso padre
    else
    {
        // Esperar a que el proceso hijo termine
        int status;
        pid_t child_pid = waitpid(pid, &status, 0);

        // Imprimir el PID del proceso hijo que terminó
        printf("Proceso hijo con PID %d terminado\n", child_pid);

        // Revisar el valor de retorno del hijo
        if (WIFEXITED(status))
        {
            printf("El hijo terminó con código de salida %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("El hijo terminó por la señal %d\n", WTERMSIG(status));
        }
    }

    return 0;
}
