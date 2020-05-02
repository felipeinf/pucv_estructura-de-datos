/*----------------------------------------------------------------------------------------------------------------------
  Descripcion: Estructuras compuestas.
  Autor: Felipe Concha Almeida
  Asignatura: Estructura de datos [INF2240].
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elemento
{ 
  char nombre[32];
  int numeroAtomico;
  float masaAtomica;
};

struct Reactivo
{
  struct Elemento elemento;
  float cantidadMicroGramos;
};

/*-------------------------------------------------------Prototipos de funciones---------------------------------------------*/
void crearReactivo( struct Reactivo *punteroReactivo, float cantidad, char *nombre, int numeroAtomico, float masaAtomica);
void crearElemento( struct Elemento *punteroElemento, char *nombre, int numeroAtomico, float masaAtomica);
void imprimirReactivo(struct Reactivo reactivo);
void imprimirElemento(struct Elemento elemento);
	

/*---------------------------------------------------------Programa Principal------------------------------------------------*/
int main(void)
{
  struct Reactivo reactivo1;
  
  crearReactivo(&reactivo1, 100.0, "Wolframio", 74, 183.84);
  imprimirReactivo(reactivo1);

  return 0;
}


/*-----------------------------------------------------------Funciones-------------------------------------------------------*/
void crearReactivo(struct Reactivo *punteroReactivo, float cantidad, char *nombre, int numeroAtomico, float masaAtomica)
{
  punteroReactivo->cantidadMicroGramos = cantidad;
  crearElemento( &(punteroReactivo->elemento), nombre, numeroAtomico, masaAtomica);
}

void crearElemento(struct Elemento *punteroElemento, char *nombre, int numeroAtomico, float masaAtomica)
{ 
  strcpy(punteroElemento->nombre, nombre);
  punteroElemento->numeroAtomico = numeroAtomico;
  punteroElemento->masaAtomica = masaAtomica;
}

void imprimirReactivo(struct Reactivo reactivo)
{
  printf("%s%f\n\n", "Cantidad de reactivo [µg]: ", reactivo.cantidadMicroGramos);
  imprimirElemento(reactivo.elemento);
}

void imprimirElemento(struct Elemento elemento)
{
  printf("%s%s\n",   "Nombre del elemento: ", elemento.nombre);
  printf("%s%d\n",   "Numero atomico: ",      elemento.numeroAtomico);
  printf("%s%f\n",   "Masa atomica: ",        elemento.masaAtomica);
}
