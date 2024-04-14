#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
        // **Variación 1: execl()**
        // execl("/bin/ls", "ls", "-l", NULL);

        // **Variación 2: execle()**
        char *envp[] = {"PATH=/bin", NULL};
        execle("/bin/ls", "ls", "-l", NULL, envp);

        // **Variación 3: execlp()**
        // execlp("ls", "ls", "-l", NULL);

        // **Variación 4: execv()**
        // char *args[] = {"ls", "-l", NULL};
        // execv("/bin/ls", args);

        // **Variación 5: execvp()**
        // execvp("ls", args);

        // **Variación 6: execvpe()**
        // char *envp[] = {"PATH=/bin", NULL};
        // execvpe("ls", args, envp);
    }

    // Código para el proceso padre
    else
    {
        // Esperar a que el proceso hijo termine
        wait(NULL);
    }

    return 0;
}

/**
 * Pregunta: ¿Por qué piensa usted que existen tantas variaciones para la misma
 * llamada básica?
 *
 * Las diferentes variaciones de la familia exec() existen para proporcionar
 * flexibilidad en la forma en que se especifica el comando a ejecutar y su entorno.
 * Algunas de las razones para estas variaciones incluyen:
 *
 * - Especificar diferentes argumentos: Algunas funciones exec() permiten especificar
 * los argumentos del comando como una lista de cadenas, mientras que otras permiten
 * especificarlos como un vector de punteros a cadenas.
 *
 * - Especificar el entorno del proceso: Algunas funciones exec() permiten especificar el
 * entorno del proceso como un conjunto de variables de entorno, mientras que otras usan el
 * entorno del proceso padre.
 *
 * - Compatibilidad con sistemas operativos antiguos: Algunas funciones exec() son
 * compatibles con sistemas operativos más antiguos que no tienen todas las características
 * de las funciones exec() más nuevas.
 */