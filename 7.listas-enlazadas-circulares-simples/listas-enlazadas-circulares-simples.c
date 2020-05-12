/*--------------------------------------------------------------------------------------------------------------------------
  Descripcion: Listas enlazadas circulares simples.
  Autor: Felipe Concha Almeida
  Asignatura: Estructura de datos [INF2240].
----------------------------------------------------------------------------------------------------------------------------*/
  
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

/*--------------------------------------------------------------------------------------------------------------------------------------------
                                                        Registros
----------------------------------------------------------------------------------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------------------------------------------------------------------------------
                                                        Funciones
----------------------------------------------------------------------------------------------------------------------------------------------*/
    
struct NodoProducto *crearProducto(int id, long precio)
{
  struct NodoProducto *nuevo = (struct NodoProducto*) malloc(sizeof(struct NodoProducto)); //Se reserva para el nodo
  nuevo->ptrProducto = (struct Producto*) malloc(sizeof(struct Producto));                 //Se reserva para el contenido

  nuevo->ptrProducto->id = id;
  nuevo->ptrProducto->precio = precio;
  nuevo->sig = NULL;
  return nuevo;
}

//Agrega un nodo en una lista circular, sin necesidad de recorrerla.
void agregarProducto(struct NodoProducto **productos, struct NodoProducto *nuevo){
      
  struct NodoProducto *head = *productos;
  
  if((*productos) == NULL) //Esta vacia
  {
    nuevo->sig = nuevo;
    (*productos) = nuevo;
  }
  else
  {
    nuevo->sig = (*productos)->sig; 
    (*productos)->sig = nuevo;
  }
}

void mostrarProductos(struct NodoProducto* productos)
{        
  struct NodoProducto *pos, *head = productos;
  
  pos = head;
  
  do
  {
    printf("  %s%d\n  %s%ld\n", "Id: ", pos->ptrProducto->id, "Precio: ", pos->ptrProducto->precio);
    printf("\n\n");
    pos = pos->sig;
      
  } while(pos != head);
       
}
/*---------------------------------------------------------------------------------------------------------------------------------------*/

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

  return 0;
}