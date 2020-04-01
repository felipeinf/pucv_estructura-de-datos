/*----------------------------------------------------------------------------------------------------------------------
  Descripcion: Punteros a estructuras.
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
  float cantidadMicroGramos;
};


/*-------------------------------------------------------Prototipos de funciones---------------------------------------------*/
void imprimirElemento(struct Elemento elemento);
void crearReactivo( struct Elemento *punteroElemento, char *nombre, int numeroAtomico, float masaAtomica, float cantidad);
	

/*---------------------------------------------------------Programa Principal------------------------------------------------*/
int main(void)
{
  struct Elemento reactivo1;
  struct Elemento reactivo2;

  // Anteponiendo el operador ' & ', traspasaremos a la funcion la direccion de memoria de
  // la estructura. En otras palabras, en la funcion recibiremos un puntero a la estructura.
  // Esto se hace cuando se quieren realizar cambios permanentes en la estructura.
  crearReactivo(&reactivo1, "Wolframio", 74, 183.84, 10000.0);
  crearReactivo(&reactivo2, "Telurio", 52, 127.60, 50000.0);

  // En el caso siguiente, solamente queremos realizar una impresion en consola por lo que 
  // no necesitamos hacer cambios sobre la estructura y la traspasamos de forma normal.
  imprimirElemento(reactivo1);
  imprimirElemento(reactivo2);

  return 0;
}

/*-----------------------------------------------------------Funciones-------------------------------------------------------*/
void crearReactivo(struct Elemento *punteroElemento, char *nombre, int numeroAtomico, float masaAtomica, float cantidad)
{ 
  // Como se menciono anteriormente, en esta funcion recibimos un puntero al elemento por
  // lo que cualquier cambio que realizemos en la estructura se guardara en la memoria.
  // Al estar trabajando con un puntero a la estructura ( struct Elemento * ) , debemos
  // utilizar el operador ' -> ' (flecha) para acceder a los campos del registro.

  strcpy(punteroElemento->nombre, nombre);
  punteroElemento->numeroAtomico = numeroAtomico;
  punteroElemento->masaAtomica = masaAtomica;
  punteroElemento->cantidadMicroGramos = cantidad;

  // RECORDAR: struct   : Utilizamos el operador punto. 
  //           struct * : Utilizamos el operador flecha.
}

void imprimirElemento(struct Elemento elemento)
{
  printf("%s%s\n",   "Nombre del elemento: ", elemento.nombre);
  printf("%s%d\n",   "Numero atomico: ",      elemento.numeroAtomico);
  printf("%s%f\n",   "Masa atomica: ",        elemento.masaAtomica);
  printf("%s%f\n\n", "Cantidad [µg]: ",       elemento.cantidadMicroGramos);
}
