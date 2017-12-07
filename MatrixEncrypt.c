#include <stdio.h>
#include <stdlib.h>

#define len(s) (sizeof(s) / sizeof(*s))

typedef struct _ValueTable {
  int sz;
  int *data;
} ValueTable;

// tabla de caracteres con los valores del indice de un arreglo
const char TABLE[] =
    " abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ!?*$#@&^()+-<>";
// matriz de codificacion
const int MATRIX_C[][3] = {{1, 2, 3}, {2, 5, 8}, {3, 6, 10}};
// matriz de decodificacion
const int MATRIX_D[][3] = {{2, -2, 1}, {4, 1, -2}, {-3, 0, 1}};
// Toma un mensaje y su logitud y devuelve su tabla de valores
ValueTable *matrix_value(char msg[], int msgLen) {
  ValueTable *vt = malloc(sizeof(ValueTable));
  vt->sz = msgLen + ((msgLen % 3 != 0) ? (3 - msgLen % 3) : 0);
  vt->data = malloc(sizeof(int) * vt->sz);

  for (size_t i = 0; i < vt->sz; i++)
    vt->data[i] = 0;

  for (size_t i = 0; i < msgLen; i++) {
    for (size_t j = 0; j < len(TABLE) - 1; j++) {
      if (msg[i] == TABLE[j]) {
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
void matrix_multiply(ValueTable *vt, const int matrix[][3], int init) {
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
void matrix_encode(ValueTable *vt) {
  for (size_t i = 0; i < vt->sz; i += 3) {
    matrix_multiply(vt, MATRIX_C, i);
  }
}
// Toma una tabla de valores codificada y la decodifica
void matrix_decode(ValueTable *vt) {
  for (size_t i = 0; i < vt->sz; i += 3) {
    matrix_multiply(vt, MATRIX_D, i);
  }
}

int main(int argc, char *argv[]) {
  char msg[100];
  int ml = 0;
  char format[] = "%[^\n]%*c";
  printf("Ingrese el mensaje a codificar:\n");
  scanf(format, msg);
  // Ajustamos el tamaño
  for (; msg[ml]; ml++)
    ;

  ValueTable *vt = matrix_value(msg, ml);

  printf("Tabla sin codificar: ");
  for (size_t i = 0; i < vt->sz; i++) {
    printf("%d", vt->data[i]);
  }
  puts("");

  matrix_encode(vt);

  printf("Tabla codificada: ");
  for (size_t i = 0; i < vt->sz; i++) {
    printf("%d", vt->data[i]);
  }
  puts("");

  matrix_decode(vt);

  printf("Tabla decodificada: ");
  for (size_t i = 0; i < vt->sz; i++) {
    printf("%d", vt->data[i]);
  }
  puts("");

  printf("Su mensaje es: ");
  for (size_t i = 0; i < vt->sz; i++) {
    printf("%c", TABLE[vt->data[i]]);
  }
  puts("");
  free(vt->data);
  free(vt);

  return 0;
}