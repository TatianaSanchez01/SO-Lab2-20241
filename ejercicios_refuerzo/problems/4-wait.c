#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  // Crear un proceso hijo
  pid_t pid = fork();

  if (pid == -1) {
    perror("Error al crear el proceso hijo");
    return 1;
  }

  // Código para el proceso hijo
  if (pid == 0) {
    // Ejecutar un comando
    execl("/bin/ls", "ls", "-l", NULL);
  }

  // Código para el proceso padre
  else {
    // Esperar a que el proceso hijo termine
    int status;
    pid_t child_pid = wait(&status);

    // Imprimir el PID del proceso hijo que terminó
    printf("Proceso hijo con PID %d terminado\n", child_pid);

    // Revisar el valor de retorno del hijo
    if (WIFEXITED(status)) {
      printf("El hijo terminó con código de salida %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      printf("El hijo terminó por la señal %d\n", WTERMSIG(status));
    }
  }

  return 0;
}

/**
 * Pregunta 1:
 * ¿Cuál es el valor de retorno de la función ```wait()```
 * La función wait() devuelve el PID del proceso hijo que terminó. Si se produjo
 * un error al esperar al proceso hijo, se devuelve un valor de -1.
 * 
 * Pregunta 2:
 * ¿Qué pasa si usted usa la función ```wait``` en el hijo?
 * Si la función wait() se usa en el proceso hijo, el proceso hijo se bloqueará hasta
 * que otro proceso lo espere. Esto generalmente no es lo que se desea, ya que el
 * proceso hijo no podrá realizar ningún trabajo mientras esté bloqueado.
*/