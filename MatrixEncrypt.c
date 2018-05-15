#include "MatrixEncrypt.h"
#include <stdio.h>
#include <stdlib.h>

ValueTable* matrix_value(char msgIn[], int msgLenIn) {
  ValueTable* vt = malloc(sizeof(ValueTable));
  vt->sz = msgLenIn + ((msgLenIn % 3 != 0) ? (3 - msgLenIn % 3) : 0);
  vt->data = malloc(sizeof(int) * vt->sz);

  for (size_t i = 0; i < vt->sz; i++)
    vt->data[i] = 0;

  for (size_t i = 0; i < msgLenIn; i++) {
    for (size_t j = 0; j < LEN(TABLE) - 1; j++) {
      if (msgIn[i] == TABLE[j]) {
        vt->data[i] = j;
        break;
      }
    }
  }

  return vt;
}

// Toma una tabla de valores, una matriz de codificacion/decodificacion y un
// entero que representara el inicio de cada terna de numeros para
// multiplicarlos con la matriz.
static void matrix_multiply(ValueTable* vt, const int matrix[][3], int init) {
  int code;
  int* data = malloc(sizeof(int) * 3);
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

void matrix_encode(ValueTable* vtIn) {
  for (size_t i = 0; i < vtIn->sz; i += 3) {
    matrix_multiply(vtIn, MATRIX_C, i);
  }
}

unsigned set_length_msg(char* msgIn) {
	unsigned msgLen = 0;
  // Ajustamos el tamaño
  for (; msgIn[msgLen]; msgLen++)
    ;
	return msgLen;
}

void matrix_decode(ValueTable* vtIn) {
  for (size_t i = 0; i < vtIn->sz; i += 3) {
    matrix_multiply(vtIn, MATRIX_D, i);
  }
}

void matrix_destroy(ValueTable* vtIn) {
  free(vtIn->data);
  free(vtIn);
}