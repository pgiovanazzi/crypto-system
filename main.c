#include <stdio.h>
#include "MatrixEncrypt.h"

// Entrada del mensaje.
static void matrix_input(char msgIn[]) {
  // Formato de entrada
  char format[] = "%[^\n]%*c";
  printf("Ingrese el mensaje a codificar:\n");
  scanf(format, msgIn);
}

// Muestra los numeros de la tabla asociados univocamente a cada caracter del
// mensaje.
static void show_output_interface(const char* format, ValueTable* vtIn) {
  printf("%-21s", format);
  for (size_t i = 0; i < vtIn->sz; i++) {
    printf("%d", vtIn->data[i]);
  }
  puts("");
}

// Muestra la decodificacion del mensaje.
static void show_output_decode(ValueTable* vtIn) {
  printf("Su mensaje es: ");
  for (size_t i = 0; i < vtIn->sz; i++) {
    printf("%c", TABLE[vtIn->data[i]]);
  }
  puts("");
}

int main(int argc, char* argv[]) {
  char msg[100];

  matrix_input(msg);

  ValueTable* vt = matrix_value(msg, set_length_msg(msg));

  show_output_interface("Tabla sin codificar:", vt);

  matrix_encode(vt);

  show_output_interface("Tabla codificada:", vt);

  matrix_decode(vt);

  show_output_interface("Tabla decodificada:", vt);

  show_output_decode(vt);

  matrix_destroy(vt);

  return 0;
}