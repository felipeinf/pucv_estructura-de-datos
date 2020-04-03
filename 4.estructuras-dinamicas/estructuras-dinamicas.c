/*----------------------------------------------------------------------------------------------------------------------
  Descripcion: Estructuras compuestas.
  Autor: Felipe Concha Almeida
  Asignatura: Estructura de datos [INF2240].
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Al igual que los struct, enum es otra de las estructuras de datos que nos provee el lenguaje y se utilizan para
// hacer enumeraciones.  
enum Prevision
{
  Fonasa = 1,
  Isapre,     
  Ffaa
};

struct Paciente 
{
  char *rut;
  char *nombre;
  char *apellido;
  int prevision; 
};

struct FichaAtencionMedica
{ 
  int identificador;
  struct Paciente * paciente;  // Esto es un puntero a una estructura Paciente.
  char *prescripcion;
};

// Muchas veces resultara mas conveniente utilizar punteros en las estructuras para hacer mas eficiente
// el uso de la memoria. En este caso como se van a generar una o mas fichas del mismo paciente, resultaria 
// un desperdicio de memoria guardar los datos repetidos del paciente en cada ficha, por lo que crearemos 
// los pacientes una sola vez y luego guardaremos la direccion de memoria de cada paciente en cada una de sus 
// fichas. 


/*-------------------------------------------------------Prototipos de funciones---------------------------------------------*/
void crearPaciente(struct Paciente *ptrPaciente, char *rut, char *nombre, char *apellido, int prevision);
void crearFicha(struct FichaAtencionMedica *ptrFicha, int id, struct Paciente *ptrPaciente, char *prescripcion);


/*---------------------------------------------------------Programa Principal------------------------------------------------*/
int main(void)
{
  struct Paciente paciente1, paciente2;
  struct FichaAtencionMedica ficha1, ficha2, ficha3;

  crearPaciente(&paciente1, "7.155.618-2", "Jaime", "Mañalich", Fonasa);
  crearPaciente(&paciente2, "6.069.264-5", "Gloria", "Hutt", Isapre);

  crearFicha(&ficha1, 1, &paciente1, "Reposo por 3 dias. Control en 7 dias desde la fecha.");
  crearFicha(&ficha2, 2, &paciente2, "Amoxicilina 500mg a cada 6 horas por 10 dias.");
  crearFicha(&ficha3, 3, &paciente1, "Control con resultados positivos pero se extiende reposo por 3 dias mas.");

  // Otra de las mayores ventajas de trabajar con un puntero al paciente en la ficha, es que si tenemos que hacer un cambio
  // en los datos de cualquier paciente, bastara con hacerlo una sola vez accediendo con su direccion de memoria. Por el contrario,
  // si tuvieramos la estructura paciente propiamente tal en la ficha, tendriamos que hacer los cambios en cada una de sus fichas.

  return 0;
}


/*-----------------------------------------------------------Funciones-------------------------------------------------------*/
void crearPaciente(struct Paciente *ptrPaciente, char *rut, char *nombre, char *apellido, int prevision)
{
  // Primero reservamos memoria para los elementos dinamicos de la estructura con malloc.
  ptrPaciente->rut = (char *) malloc( strlen(rut) + 1); // Le sumamos 1 al tamano por el '\0'.
  ptrPaciente->nombre = (char *) malloc( strlen(nombre) + 1);
  ptrPaciente->apellido = (char *) malloc( strlen(apellido) + 1);

  // Luego guardamos los valores recibidos por parametro en la estructura.
  strcpy(ptrPaciente->rut, rut);
  strcpy(ptrPaciente->nombre, nombre);
  strcpy(ptrPaciente->apellido, apellido);
  ptrPaciente->prevision = prevision;
}

void crearFicha(struct FichaAtencionMedica *ptrFicha, int id, struct Paciente *ptrPaciente, char *prescripcion){
  ptrFicha->prescripcion = (char *) malloc( strlen(prescripcion) + 1);
  ptrFicha->identificador = id;
  ptrFicha->paciente = ptrPaciente;
  ptrFicha->prescripcion = prescripcion;
}
