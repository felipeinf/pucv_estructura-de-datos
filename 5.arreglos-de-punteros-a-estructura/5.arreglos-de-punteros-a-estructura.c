/*--------------------------------------------------------------------------------------------------------------
  Descripcion: Ejemplo de listas de punteros a estructuras.
  Autor: Felipe Concha Almeida
  Asignatura: Estructura de datos [INF2240].
----------------------------------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CAPACIDAD_TOTAL 100000

/*--------------------------------------------------------------------------------------------
                                       Registros
----------------------------------------------------------------------------------------------*/
struct Persona 
{
  char* nombre;
  long pasaporte;
  short edad;
};

/*--------------------------------------------------------------------------------------------
                                  Prototipos de funcion
----------------------------------------------------------------------------------------------*/
struct Persona* crearPersona(char* nombre, long pasaporte, short edad);
short agregarPersona(struct Persona** listaPersonas, long tamano, struct Persona* nuevaPersona);
long buscarPersona(struct Persona** listaPersonas, long tamano, long pasaporte);
void mostrarLista(struct Persona** lista, long tamano);
struct Persona *eliminarPersona(struct Persona** listaPersonas, long tamano, long pasaporte);

/*--------------------------------------------------------------------------------------------
                                    Programa Principal
----------------------------------------------------------------------------------------------*/
int main(void)
{
  /*
    Esta es una lista de punteros a struct Persona. Cada posicion contiene un puntero a una
    estructura Persona, osea contiene las direcciones de memoria de las estructuras creadas. 
  */
  struct Persona** listaPresidentesLatam;  
  long capacidad;
  struct Persona* personaTemporal;

  capacidad = CAPACIDAD_TOTAL;
  listaPresidentesLatam = (struct Persona**) malloc((capacidad + 1) * sizeof(struct Persona*));

  /*
    Hay dos formas de agregar personas, la primera es con una variable temporal.
  */
  personaTemporal = crearPersona("Sebastian Piñera", 4989860, 69);
  agregarPersona(listaPresidentesLatam, capacidad, personaTemporal);

  /*
    La otra forma es traspasar la funcion directamente como parametro.
  */
  agregarPersona(listaPresidentesLatam, capacidad, crearPersona(
    "Mauricio Macri",   //Nombre
    3009855,            //Pasaporte
    60                  //Edad
  ));

  agregarPersona(listaPresidentesLatam, capacidad, crearPersona(
    "Jair Bolsonaro",
    4177669,
    63
  ));

  agregarPersona(listaPresidentesLatam, capacidad, crearPersona(
    "Ivan Duque",
    3987771,
    42
  ));

  agregarPersona(listaPresidentesLatam, capacidad, crearPersona(
    "Martin Vizcarra",
    3021960,
    55
  ));

  //Mostramos la lista con los presidentes agregados
  mostrarLista(listaPresidentesLatam, capacidad);

  /*
    Eliminaremos a Ivan Duque de la listas de presidente usando su identificador, que en este caso es el 
    pasaporte: 3987771
  */
  personaTemporal = eliminarPersona(listaPresidentesLatam, capacidad, 3987771);
  printf("\nPresidente eliminado: %s\n\n", personaTemporal->nombre);

  //Para terminar mostramos la lista luego de haber eliminado a Ivan Duque.
  mostrarLista(listaPresidentesLatam, capacidad);
}

/*--------------------------------------------------------------------------------------------
                                    Funciones (Modularizacion)
----------------------------------------------------------------------------------------------*/
struct Persona* crearPersona(char* nombre, long pasaporte, short edad)
{
  struct Persona* nuevaPersona;
  nuevaPersona = (struct Persona*) malloc(sizeof(struct Persona)); //Se reserva memoria para la nueva persona

  if(nuevaPersona != NULL)  //Esto es equivalente a  if(persona)
  {  
    nuevaPersona->pasaporte = pasaporte;
    nuevaPersona->edad = edad;
    /*
      Como los nombres tienen diferentes largos, se debe reservar memoria para el nombre de cada
      persona, para esto se utilizara la funcion strlen  de la libreria <string.h>.
    */
    nuevaPersona->nombre = (char*) malloc((strlen(nombre) + 1) * sizeof(char));
    //Recuerden que para copiar cadenas se debe usar la funcion strcpy(destino, cadenaAcopiar)
    strcpy(nuevaPersona->nombre, nombre);

    //Finalmente retornamos la persona creada.
    return nuevaPersona;
  }
  /*
    Se retorna NULL ya que la persona no se ha creado.
  */
  else return NULL;  
}

short agregarPersona(struct Persona** listaPersonas, long tamano, struct Persona* nuevaPersona)
{
  long i, posicion;
  /*
    Antes que nada, se debe verificar que la nueva persona se creo con exito. Si retorna NULL quiere
    decir que la persona no se ha creado o que no hay memoria, en ese caso se retorna 0 (false) de lo
    contrario se busca el espacio y se agrega la persona.
  */
  if(nuevaPersona)  //Esto es equivalente a   if(nuevaPersona != NULL).
  {
    posicion = buscarPersona(listaPersonas, tamano, nuevaPersona->pasaporte);

    /*
      Si la posicion es -1, quiere decir que la persona no se encontraba en la lista y solo queda 
      por encontrar un espacio vacio.
    */
    if(posicion == -1)
    {
      for(i = 0;  i < tamano;  i++)
      {
        if( ! listaPersonas[i])   //Esto es equivalente a  if(listaPersonas[i] == NULL).
        {  
          //Si hay espacio, se agrega la persona en esa posicion, donde anteriormente habia un NULL.
          listaPersonas[i] = nuevaPersona;
          return 1;
        }
      }
    }
    else return 0; //Se retorna 0 ya que se recorrio por completo la lista y no se ha encontrado espacio para la insercion.
  }
  else return 0; //Se retorna 0 ya que no se ha creado la persona. 
}

long buscarPersona(struct Persona** listaPersonas, long tamano, long pasaporte){
  long i;

  for(i = 0;  i < tamano;  i++)
  {
    if(listaPersonas[i])    //Esto es equivalente a  if(listaPersonas[i] != NULL) 
    {  
      /*
        Si se encuentra la persona se retorna su posicion.
      */
      if(listaPersonas[i]->pasaporte == pasaporte) return i;
    }
  }
  /*
    Si se termina el ciclo, osea si se recorre toda la lista y no se encuentra la persona entonces se
    retorna una posicion invalida que por lo general es -1  (Posicion que no existe en ningun arreglo)
  */
  return -1;
}

struct Persona *eliminarPersona(struct Persona** listaPersonas, long tamano, long pasaporte)
{
  long i, posicion;
  struct Persona* personaEliminada;

  posicion = buscarPersona(listaPersonas, tamano, pasaporte);

  //Si se encontro la persona, se inserta un NULL en la posicion donde fue encontrada.
  if(posicion != -1)
  {   //Antes de borrar la persona debe respaldarse en personaEliminada, para luego poder retornarla.
    personaEliminada = listaPersonas[posicion];
    listaPersonas[posicion] = NULL; //Se elimina la persona insertando un NULL en la lista.
    return personaEliminada; //Se retorna la persona eliminada que ha sido respaldada.
  }
  else return NULL;
}

void mostrarLista(struct Persona** listaPersonas, long tamano)
{
  long i;

  for(i = 0;  i < tamano;  i++)
  {
    if(listaPersonas[i]) 
    {
      printf("%s%s\n", "Nombre: ", listaPersonas[i]->nombre);
    }
  }
}