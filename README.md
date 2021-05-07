# TP1_Algo2_PescaPokemon
TP1 Algoritmos II - Pesca Pokemon

INTRODUCCION
El trabajo consiste en tres archivos principales:
- evento_pesca.h: es el header brindado por la cátedra, el cual contiene las primitivas a las que se podrá llamar para realizar las diferentes acciones que el programa requiere.
- evento_pesca.c: en este se implementan las funciones primitivas.
- main.c: es donde transcurre el flujo principal del programa. Este es el que podrá ser modificado por el programador.
Además se requiere de algún archivo .txt que contenga los datos de los pokemones que se podrán encontrar en un arrecife.

El programa ingresa pokemons al arrecife mediante un archivo de texto. También se podrá crear un acuario al cual se podrán ingresar pokemons siempre que cumplan con la/las condición/es que se le impongan. En todo momento se podrá censar el arrecife y se imprimirán en pantalla los pokemons que se encuentren actualmente en él.
Luego se guardarán en un archivo de texto los pokemones (y sus características) que se encuentran en el acuario. 


COMPILACION Y EJECUCIÓN
Se compila con la linea "gcc *.c -Wall -Werror -Wconversion -std=c99 -o evento_pesca", la cual contiene la implementación de las funciones presentes en el archivo "evento_pesca.h", y se ejecuta mediante el comando "valgrind --leak -check=full --track -origins=yes --show -reachable=yes ./ evento_pesca" para asegurarse que no se haya producido pérdida alguna de memoria durante la ejecución.


EXPLICACIÓN DE CONCEPTOS UTILIZADOS
1- Punteros: se trata de un tipo de variable que "apunta" a una dirección de memoria. Sin importar a que tipo de variable apunte, siempre ocupa el mismo tamaño en el stack. A diferencia de otros tipos de variables, al definir una variable de tipo puntero, éstos pueden ser redimensionados. Además pueden modificar las variables que contienen los elementos a los que apuntan.

2- Aritmética de Punteros: permite desplazar la dirección a la que apunta un puntero. Al incrementar un puntero en una unidad, este apuntará n bytes hacia "adelante". Esa cantidad de bytes corresponderá al tamaño que tiene una unidad de la variable a la que este apuntando dicho puntero.

3- Punteros a Funciones: son punteros que, como indica su nombre, apuntan a funciones de la misma forma que podrían apuntar a cualquier otro tipo de dato.

4- Malloc y Realloc: son funciones de asignación de memoria dinámica. Permiten modificar el tamaño de las variables en tiempo de ejecución según sea necesario. Se utilizan con variables de tipo puntero. Malloc reserva un espacio de memoria inicial para la variable y Realloc redimensiona el espacio de memoria que posee una variable.
