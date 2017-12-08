#include <stdio.h>
#include <stdlib.h>

#define len(s) (sizeof(s) / sizeof(*s))

typedef struct _ValueTable {
  int sz;
  int *data;
} ValueTable;

// tabla de caracteres con los valores del indice de un arreglo
const char TABLE[] = " abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ"
                     "!?*$#@&^()+-<>0123456789";
// matriz de codificacion
const int MATRIX_C[][3] = {{1, 2, 3}, {2, 5, 8}, {3, 6, 10}};
// matriz de decodificacion
const int MATRIX_D[][3] = {{2, -2, 1}, {4, 1, -2}, {-3, 0, 1}};
// Toma un mensaje y su logitud y devuelve su tabla de valores
static ValueTable *matrix_value(char msgIn[], int msgLenIn) {
  ValueTable *vt = malloc(sizeof(ValueTable));
  vt->sz = msgLenIn + ((msgLenIn % 3 != 0) ? (3 - msgLenIn % 3) : 0);
  vt->data = malloc(sizeof(int) * vt->sz);

  for (size_t i = 0; i < vt->sz; i++)
    vt->data[i] = 0;

  for (size_t i = 0; i < msgLenIn; i++) {
    for (size_t j = 0; j < len(TABLE) - 1; j++) {
      if (msgIn[i] == TABLE[j]) {
        vt->data[i] = j;
        break;
      }
    }
  }

  return vt;
}
// Toma una tabla de valores, una matriz de codificacion/decodificacion y un
// entero
// que representara el inicio de cada terna de numeros para multiplicarlos con
// la matriz.
static void matrix_multiply(ValueTable *vt, const int matrix[][3], int init) {
  int code;
  int *data = malloc(sizeof(int) * 3);
  for (size_t i = 0; i < 3; i++) {
    data[i] = vt->data[init + i];
  }
  for (size_t i = 0; i < 3; i++) {
    code = 0;
    for (size_t j = 0; j < 3; j++) {
      code += matrix[i][j] * data[j];
    }
    vt->data[init + i] = code;
  }
  free(data);
}
// Toma un tabla de valores y la codifica
static void matrix_encode(ValueTable *vtIn) {
  for (size_t i = 0; i < vtIn->sz; i += 3) {
    matrix_multiply(vtIn, MATRIX_C, i);
  }
}
// Toma una tabla de valores codificada y la decodifica
static void matrix_decode(ValueTable *vtIn) {
  for (size_t i = 0; i < vtIn->sz; i += 3) {
    matrix_multiply(vtIn, MATRIX_D, i);
  }
}

static void matrix_input(char msgIn[]) {
  // Formato de entrada
  char format[] = "%[^\n]%*c";
  printf("Ingrese el mensaje a codificar:\n");
  scanf(format, msgIn);
}

static void show_output_interface(const char *format, ValueTable *vtIn) {
  printf("%-21s", format);
  for (size_t i = 0; i < vtIn->sz; i++) {
    printf("%d", vtIn->data[i]);
  }
  puts("");
}

static void show_output_decode(ValueTable *vtIn) {
  printf("Su mensaje es: ");
  for (size_t i = 0; i < vtIn->sz; i++) {
    printf("%c", TABLE[vtIn->data[i]]);
  }
  puts("");
}

static void set_length_msg(char *msgIn, int *msgLenIn) {
  // Ajustamos el tamaño
  for (; msgIn[*msgLenIn]; (*msgLenIn)++)
    ;
}

static void matrix_destroy(ValueTable *vtIn) {
  free(vtIn->data);
  free(vtIn);
}

int main(int argc, char *argv[]) {
  char msgIn[100];
  int msgLenIn = 0;

  matrix_input(msg);
  set_length_msg(msg, &msgLen);

  ValueTable *vt = matrix_value(msg, msgLen);

  show_output_interface("Tabla sin codificar:", vt);

  matrix_encode(vt);

  show_output_interface("Tabla codificada:", vt);

  matrix_decode(vt);

  show_output_interface("Tabla decodificada:", vt);

  show_output_decode(vt);

  matrix_destroy(vt);

  return 0;
}