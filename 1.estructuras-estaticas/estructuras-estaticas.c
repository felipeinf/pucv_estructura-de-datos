/*--------------------------------------------------------------------------------------------------------------
  Descripcion: Implementación de estructuras estaticas.
  Autor: Felipe Concha Almeida
  Asignatura: Estructura de datos [INF2240].
----------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elemento
{ 
  char nombre[32];
  int numeroAtomico;
  float masaAtomica;
  float cantidadMicroGramos;
};

void imprimirElemento(struct Elemento elemento);
	
int main(void)
{
  struct Elemento reactivo1;
  struct Elemento reactivo2;

  // Para acceder a los elementos de una estructura, se utiliza el operador ' . ' (punto).

  // Inicializamos el reactivo 1
  strcpy(reactivo1.nombre, "Wolframio");
  reactivo1.numeroAtomico = 74;
  reactivo1.masaAtomica = 183.84;
  reactivo1.cantidadMicroGramos = 100000.0;

  // Inicializamos el reactivo 2
  strcpy(reactivo2.nombre, "Telurio");
  reactivo2.numeroAtomico = 52;
  reactivo2.masaAtomica = 127.60;
  reactivo2.cantidadMicroGramos = 50000.0;

  imprimirElemento(reactivo1);
  imprimirElemento(reactivo2);

  return 0;
}

void imprimirElemento(struct Elemento elemento)
{
  printf("%s%s\n",   "Nombre del elemento: ", elemento.nombre);
  printf("%s%d\n",   "Numero atomico: ",      elemento.numeroAtomico);
  printf("%s%f\n",   "Masa atomica: ",        elemento.masaAtomica);
  printf("%s%f\n\n", "Cantidad [µg]: ",       elemento.cantidadMicroGramos);
}
