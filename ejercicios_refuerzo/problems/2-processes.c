#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> // Include for wait() function


int main() {
  // Crear un proceso hijo
  pid_t pid = fork();

  if (pid == -1) {
    perror("Error al crear el proceso hijo");
    return 1;
  }

  // Código para el proceso hijo
  if (pid == 0) {
    // Imprimir "Hello" desde el proceso hijo
    printf("Hello\n");
    
    // **Punto clave:** Esperar un tiempo para asegurar que el padre imprima después
    sleep(1);
  }

  // Código para el proceso padre
  else {
    // **Punto clave:** Esperar a que el hijo termine antes de imprimir
    wait(NULL);
    
    // Imprimir "goodbye" desde el proceso padre
    printf("goodbye\n");
  }

  return 0;
}
