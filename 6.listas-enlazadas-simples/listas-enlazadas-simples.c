/*--------------------------------------------------------------------------------------------------------------------------
  Descripcion: Ejemplo de listas enlazadas.
  Autor: Felipe Concha Almeida
  Asignatura: Estructura de datos [INF2240].
----------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--------------------------------------------------------------------------------------------------------------------------
                                                        Registros
----------------------------------------------------------------------------------------------------------------------------*/
struct Producto
{
  int id;
  long precio;
};

struct NodoProducto
{
  struct Producto *ptrProducto;
  struct NodoProducto *sig;
};

struct Tienda
{
  char* rutGerente;
  struct NodoProducto *productos;
};

/*--------------------------------------------------------------------------------------------------------------------------
                                                        Funciones
----------------------------------------------------------------------------------------------------------------------------*/
struct NodoProducto *crearProducto(int id, long precio)
{
  struct NodoProducto *nuevo = (struct NodoProducto*) malloc(sizeof(struct NodoProducto)); //Se reserva para el nodo
  nuevo->ptrProducto = (struct Producto*) malloc(sizeof(struct Producto));                 //Se reserva para el contenido

  nuevo->ptrProducto->id = id;
  nuevo->ptrProducto->precio = precio;
  nuevo->sig = NULL;
  return nuevo;
}

void agregarProducto(struct NodoProducto **productos, struct NodoProducto *nuevo){
  struct NodoProducto *pos;

  pos = *productos;

  if( *productos != NULL) //Si la lista no esta vacia 
  {
    while(pos != NULL)
    {
      if(pos->sig == NULL)
      {
        pos->sig = nuevo;
        pos = pos->sig;
      }

      pos = pos->sig;
    }
  }
  else *productos = nuevo; //Si esta vacia el nuevo es el primer nodo osea es la lista.   
}

struct NodoProducto *eliminarProducto(struct NodoProducto **productos, int id){
  struct NodoProducto *pos, *respaldo;

  pos = *productos;

  if( *productos != NULL)
  {
    while(pos != NULL)
    {
      if(pos->ptrProducto != NULL)
      {
        if(id == pos->sig->ptrProducto->id)
        {
          respaldo = pos->sig;
          pos->sig = pos->sig->sig;
          return respaldo;
        }
      }

      pos = pos->sig;
    }
    return NULL;
  }  
  return NULL;    
}

void mostrarProductos(struct NodoProducto* productos)
{        
  struct NodoProducto *pos;

  pos = productos;  

  while(pos != NULL)
  {
    if(pos->ptrProducto != NULL)
    {
      printf("  %s%d\n  %s%ld\n", "Id: ", pos->ptrProducto->id, "Precio: ", pos->ptrProducto->precio);
    }

    pos = pos->sig;
  }
  printf("\n\n");
}

int main()
{
  struct NodoProducto *productos, *eliminado;
  productos = NULL;

  agregarProducto(&productos, crearProducto(1, 19990));
  agregarProducto(&productos, crearProducto(2, 2500));
  agregarProducto(&productos, crearProducto(3, 5000));
  agregarProducto(&productos, crearProducto(4, 1990));
  agregarProducto(&productos, crearProducto(5, 7800));
  agregarProducto(&productos, crearProducto(6, 2900));
  agregarProducto(&productos, crearProducto(7, 4990));
  
  mostrarProductos(productos);

  //Se guarda el nodo eliminado para mostrar luego su contenido.
  eliminado = eliminarProducto(&productos, 4);
  
  if(eliminado != NULL)
  {
    printf("%s%d  %s%ld\n\n", "[Producto eliminado] Id: ", eliminado->ptrProducto->id, "Precio: ", eliminado->ptrProducto->precio);
  } 
  
  mostrarProductos(productos);
  return 0;
}