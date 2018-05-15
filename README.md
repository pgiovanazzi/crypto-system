# Ejemplo de criptografia hecho en C #

### Resumen ###

Encripta y desencripta un mensaje utilizando una matriz y su inversa de 3x3 de enteros.
___
### ¿Como ejecutarlo? ###

* Se necesita el gcc instalado
* Escribimos en la terminal $gcc -o NombreDelEjecutable main.c MatrixEncrypt.c
* Luego lo ejecutamos $./NombreDelEjecutable

Ejemplo:
~~~
$gcc -o test main.c MatrixEncrypt.c
Ingrese el mensaje a codificar:
~~~
input>
~~~
hola que tal
~~~
output>
~~~
Tabla sin codificar: 817121019235022112
Tabla codificada:    781972465815419333719960145192
Tabla decodificada:  817121019235022112
Su mensaje es: hola que tal
~~~
___
### Autor ###

Paulo