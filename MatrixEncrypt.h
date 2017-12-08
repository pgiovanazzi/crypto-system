#ifndef __MATRIXENCRYPT_H__
#define __MATRIXENCRYPT_H__

#define LEN(X) (sizeof(X) / sizeof(*X))

typedef struct _ValueTable {
  int sz;
  int *data;
} ValueTable;

// tabla de caracteres con los valores del indice de un arreglo.
static const char TABLE[] =
    " abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ"
    "!?*$#@&^()+-<>0123456789";
// matriz de codificacion.
static const int MATRIX_C[][3] = {{1, 2, 3}, {2, 5, 8}, {3, 6, 10}};
// matriz de decodificacion.
static const int MATRIX_D[][3] = {{2, -2, 1}, {4, 1, -2}, {-3, 0, 1}};

// Toma un mensaje y su logitud y devuelve su tabla de valores.
ValueTable *matrix_value(char msgIn[], int msgLenIn);

// Toma un tabla de valores y la codifica.
void matrix_encode(ValueTable *vtIn);

// Toma una tabla de valores codificada y la decodifica.
void matrix_decode(ValueTable *vtIn);

// Calula la longitud del mensaje y lo guarda en msgLenIn.
void set_length_msg(char *msgIn, int *msgLenIn);

// Destruye la tabla de valores.
void matrix_destroy(ValueTable *vtIn);

#endif /* __MATRIXENCRYPT_H__ */