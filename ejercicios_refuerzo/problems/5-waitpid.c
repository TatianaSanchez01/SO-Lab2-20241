#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

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

/**
 * Pregunta: ¿cuándo podría ser ```waitpid()``` útil?
 * 
 * La función waitpid() puede ser útil en las siguientes situaciones:
 * - Esperar a un proceso hijo específico: La función waitpid() permite especificar
 * el PID del proceso hijo que desea esperar. Esto puede ser útil si tiene varios
 * procesos hijos en ejecución y solo desea esperar a uno específico.
 *
 * - Obtener información adicional sobre el estado de salida del proceso hijo: La
 * función waitpid() proporciona más información sobre el estado de salida del
 * proceso hijo que la función wait(). Por ejemplo, puede obtener el código de
 * salida del proceso hijo o la señal que lo terminó.
 *
 * - Recibir notificaciones cuando un proceso hijo cambia de estado: La función
 * waitpid() se puede utilizar para recibir notificaciones cuando un proceso hijo
 * cambia de estado, como cuando se detiene o se reanuda.
 */