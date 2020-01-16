/*--------------------------------------------------------------------------------------------------------------
    Descripcion: Ejemplo avanzado de arboles binarios de busqueda.
    Autor: Felipe Concha Almeida
    Asignatura: Estructura de datos [INF2240].
----------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elemento
{ 
    char *nombre;
    char *simbolo;
    int numeroAtomico;
    float masaAtomica;
};
	
struct NodoElemento
{
    int id;
    struct Elemento *elemento;
    struct NodoElemento *izq;
    struct NodoElemento *der;
};

/*-----------------------------------------------------------Recorridos de arboles----------------------------------------------------------
    
  Los arboles binarios tienen 3 formas de ser recorridos:
  
      - Pre orden: Se visita primero la raiz del arbol, luego la 
                    parte izquierda y finalmente la derecha.
      
      - In orden: Se visita primero la parte izquierda del arbol,
                  luego la raiz y finalmente la derecha.
      
      - Post orden: Se visita primero parte izquierda del arbol, 
                    luego la derecha y finalmente la raiz.

---------------------------------------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------Prototipos de funciones-----------------------------------------------------------------*/
  struct NodoElemento *crearNodoElemento( char*nombre, char* simbolo, int numeroAtomico, float masaAtomica);
  struct NodoElemento *buscarNodoEnArbolPreOrden( struct NodoElemento *arbol, long id );
  void insertarNodoElemento( struct NodoElemento **arbol, struct NodoElemento *nuevo );
  void intercambiarDatosNodoElemento( struct NodoElemento **elem1, struct NodoElemento **elem2  );
  void liberarNodoElemento( struct NodoElemento **elem );
  short tieneHijos( struct NodoElemento *elem );
  void podarNodoElemento( struct NodoElemento **arbol, long id );
  void mostrarArbolRecursivoInOrden( struct NodoElemento *arbol ) ;
  void mostrarEnFormato( struct NodoElemento *arbol, char *encabezado );
/*---------------------------------------------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------------------------------------------
                                                        Programa Principal
-----------------------------------------------------------------------------------------------------------------------------------------------*/
int main()
{
  struct NodoElemento *arbolElementos = NULL; //Al igual que las listas es de suma importancia inicializar en NULL.
  
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Vanadio",   "V",   23,  50.942 ));
  //El segundo Vanadio no lo agrega por que ya existe en el arbol.
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Vanadio",   "V",   23,  50.942 ));
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Magnesio",  "Mg",  12,  24.305 ));
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Osmio",     "Os",  76,  190.23 ));
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Radon",     "Rn",  86,  222    ));
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Cadmio",    "Cd",  48,  112.41 ));  
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Rubidio",   "Rb",  37,  24.305 ));
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Wolframio", "W",   74,  183.84 ));
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Astato",    "At",  85,  210    ));
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Telurio",   "Te",  52,  127.60 ));
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Arsenico",  "As",  33,  74.922 ));
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Antimonio", "Sb",  51,  121.76 ));
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Boro",      "B",   5,   10.81  ));  
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Escandio",  "Sc",  21,  44.956 ));
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Itrio",     "Y",   39,  88.906 ));
  insertarNodoElemento(&arbolElementos, crearNodoElemento( "Cadmio",    "Cd",  48,  112.41 ));  
  
  mostrarEnFormato(arbolElementos, "Elementos agregados:");
  
  //Se elimina el Magnesio Z: 12
  podarNodoElemento(&arbolElementos, 12);
  
  //Se elimina el Boro Z: 5
  podarNodoElemento(&arbolElementos, 5);
  
  mostrarEnFormato(arbolElementos, "Elementos despues de eliminar Boro y Magnesio:");
  return 0;
}
/*---------------------------------------------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------------------------------------------
                                                            Funciones
-----------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------Crea un nuevo nodo elemento-----------------------------------*/
  struct NodoElemento *crearNodoElemento( char*nombre, char* simbolo, int numeroAtomico, float masaAtomica)
  {
    struct NodoElemento *nuevo = ( struct NodoElemento * ) malloc( sizeof( struct NodoElemento ));
    
    nuevo->elemento = ( struct Elemento * ) malloc( sizeof( struct Elemento )); //Se reserva memoria para el elemento.
    nuevo->id = numeroAtomico; //Se asigna un identificador unico, en este caso es el numero atomico.
    
    nuevo->elemento->nombre = ( char * ) malloc( strlen(nombre) * sizeof(char));  //Se reserva memoria para el nombre segun su largo.
    strcpy( nuevo->elemento->nombre, nombre );	   

    nuevo->elemento->simbolo = ( char * ) malloc( strlen(simbolo) * sizeof(char)); //Se reseverma meoria para el simbolo.
    strcpy( nuevo->elemento->simbolo, simbolo );
    
    nuevo->elemento->numeroAtomico = numeroAtomico; //Se guarda el numero atomico.
    nuevo->elemento->masaAtomica = masaAtomica; //Se guarda la masa atomica.

    nuevo->izq = NULL;
    nuevo->der = NULL;
    
    return nuevo;
  }
/*----------------------------------------------------------------------------------------------*/


/*-----------------Retorna un nodo buscado en un arbol o NULL en caso contrario-----------------*/
	struct NodoElemento *buscarNodoEnArbolPreOrden( struct NodoElemento *arbol, long id )
	{
		struct NodoElemento *actual = arbol;
		
		while( actual != NULL )
		{
			if( id != actual->id )
			{
				if( id < actual->id ) 
				{
					actual = actual->izq;
				}
				else actual = actual->der;
			}
			else return actual;
		}
		return NULL;		
	}
/*----------------------------------------------------------------------------------------------*/


/*-----------------------------------Inserta un nodo ordenado-----------------------------------*/
	void insertarNodoElemento( struct NodoElemento **arbol, struct NodoElemento *nuevo )
	{        
		struct NodoElemento *anterior = NULL, *actual = *arbol;

    if(buscarNodoEnArbolPreOrden(*arbol, nuevo->id) == NULL) //Esta restricion es opcional se usa para no insertar elementos con el mismo Id.
    {                                                        //Si retona NULL entonces el elemento no fue encontrado y se inserta.
      if( *arbol != NULL  )
      {//Esto deben dibujarlo y rutearlo para que puedan entenderlo mas rapido.
        do
        {
          anterior = actual;

          if( nuevo->id < actual->id ) 
          {
            actual = actual->izq;
          }
          else actual = actual->der;
        }
        while( actual != NULL );

        actual = nuevo;

        if( nuevo->id < anterior->id ) 
        {
          anterior->izq = actual;
        }
        else anterior->der = actual;

      }
      else *arbol = nuevo;
    }
	}
/*----------------------------------------------------------------------------------------------*/


/*------------------------Intercambia el contenido de dos nodos elemento------------------------*/
void intercambiarDatosNodoElemento( struct NodoElemento **elem1, struct NodoElemento **elem2  )
{
  struct Elemento *elemento;
  long id;

  elemento = ( *elem1 )->elemento;
  id = ( *elem1 )->id;

  ( *elem1 )->elemento = ( *elem2 )->elemento;
  ( *elem1 )->id = ( *elem2 )->id;

  ( *elem2 )->elemento = elemento;
  ( *elem2 )->id = id;

  *elem1 = *elem2;		
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------Libera la memoria de un nodo elemento y lo inicializa-----------------------*/
  void liberarNodoElemento( struct NodoElemento **elem )
  {
    free( *elem );
    *elem = NULL;
  }
/*----------------------------------------------------------------------------------------------*/


/*-----------------------Verifica si un nodo de un arbol tiene nodos hijos----------------------*/
  short tieneHijos( struct NodoElemento *elem )
  {
    if( elem->izq != NULL  ||  elem->der != NULL ) return 1;
    else return 0;
  }
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------Suprime un nodo de un arbol---------------------------------*/
  void podarNodoElemento( struct NodoElemento **arbol, long id )
  {
      struct NodoElemento *nodoPadre = NULL, *nodoTemporal = NULL, *nodoActual = *arbol;

      if(*arbol)
      {        
        if( !tieneHijos( *arbol ) && ( *arbol )->id == id )  //Si la raiz del arbol no tiene hijos y es el nodo que se quiere borrar entonces el arbol se hace NULL.
        {
          *arbol = NULL;
          return; 
        } 

        while( nodoActual != NULL ) //Esto tambien deben rutearlo y hacer un dibujo.
        {
          if( id != nodoActual->id )
          {
            nodoPadre = nodoActual;

            if( id < nodoActual->id )
            {
              nodoActual = nodoActual->izq;	
            } 
            else nodoActual = nodoActual->der;
          }
          else
          {
            if( !tieneHijos( nodoActual ))
            {
              if( nodoPadre != NULL )
              {
                if( nodoPadre->izq == nodoActual )
                {
                  nodoPadre->izq = NULL;
                }
                else nodoPadre->der = NULL;
              }

              liberarNodoElemento( &nodoActual );
              return;
            }
            else
            {
              nodoPadre = nodoActual;

              if( nodoActual->der != NULL ) 
              {
                  nodoTemporal = nodoActual->der;
                  
                  while(nodoTemporal->izq != NULL)
                  {
                    nodoPadre = nodoTemporal;
                    nodoTemporal = nodoTemporal->izq;
                  }
                  /*
                      Tambien se puede hacer en una linea con un for, pero tecnicamente lo correcto es usar un while porque se desconoce
                      la cantidad de veces que va a iterar.

                      for( nodoTemporal = nodoActual->der;  nodoTemporal->izq != NULL;  nodoPadre = nodoTemporal,	nodoTemporal = nodoTemporal->izq );
                  */
              }
              else //Aca lo mismo:  for( nodoTemporal = nodoActual->izq;  nodoTemporal->der != NULL;  nodoPadre = nodoTemporal, nodoTemporal = nodoTemporal->der );
              {
                nodoTemporal = nodoActual->izq;
              }

              while(nodoTemporal->der != NULL)
              {
                nodoPadre = nodoTemporal;
                nodoTemporal = nodoTemporal->der;
              }
          
              intercambiarDatosNodoElemento( &nodoActual, &nodoTemporal );
            }
          }
        }
      }
    }
/*----------------------------------------------------------------------------------------------*/


/*----------Imprime de forma recursiva el contenido de un arbol en formato de tabla-------------*/
	void mostrarArbolRecursivoInOrden( struct NodoElemento *arbol ) 
	{		
		if ( arbol != NULL ) 
		{
			mostrarArbolRecursivoInOrden( arbol->izq );
			printf( "\t%s\n", "|              |              |         |                      |" );
            
            //El -13 antes del %s indica la cantidad de espacios de derecha a izquierda que va a usar al imprimir
            //El \t es para tabular.
            
			printf( "\t%s%-13s%s%-13s%s",  "| ", arbol->elemento->nombre, "| ", arbol->elemento->simbolo, "| "  );   
            
            //El .3 antes de %f es la cantidad de decimales.
			printf( "%-8d%s%-21.3f%s\n", arbol->elemento->numeroAtomico, "| ", arbol->elemento->masaAtomica, "|");
            
            
			printf( "\t%s\n","|______________|______________|_________|______________________|" );
			mostrarArbolRecursivoInOrden( arbol->der );
		}
		else return;	
	}
/*----------------------------------------------------------------------------------------------*/
	

/*--------------------Muestra el contenido de un arbol, en formato de tabla---------------------*/
    void mostrarEnFormato( struct NodoElemento *arbol, char *encabezado )
    {
        printf( "\n\t%s\n", encabezado );
        printf( "\t%s\n",  " ______________________________________________________________" );
        printf( "\t%s\n",  "|              |              |         |                      |" );
        printf( "\t%s\n",  "|   NOMBRE     |   SIMBOLO    | ATOMICO |     MASA ATOMICA     |" );
        printf( "\t%s\n",  "|______________|______________|_________|______________________|" );
        mostrarArbolRecursivoInOrden( arbol );
        printf( "\n\t" );
    }
/*----------------------------------------------------------------------------------------------*/