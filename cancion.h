#ifndef CANCION_H_INCLUDED
#define CANCION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
#include "menu.h"

/*typedef struct {
    int idCancion;
    char titulo[30];
    char artista[20];
    float duracion;
    char album[20];
    int anio;
    char genero[20];
    char comentario[100];
    char ruta[40];
    int eliminado;
}Cancion;*/

/*typedef struct {
    int idUsuario;
    char nombreUsuario[30];
    char pass[20];
    int anioNacimiento;
    char genero;
    char pais[20];
    int eliminado;
    int rol;    /// 0 = ADMIN; 1 = USER
}Usuario;*/


/*typedef struct {
    Cancion cancion;
    struct nodoListaCancion * sig;
}nodoListaCancion;*/


/*typedef struct{
    Cancion cancion;
    struct nodoArbolCancion * izq;
    struct nodoArbolCancion * der;
}nodoArbolCancion;*/



/*typedef struct{
    Usuario usuario;
    nodoListaCancion * listaCanciones;
}Celda;*/



///FUNCIONES DE LISTAS
/*nodoListaCancion* inicLista();
nodoListaCancion* crearNodoLista(Cancion);
nodoListaCancion* agregarAlPrincipio(nodoListaCancion*, nodoListaCancion*);
nodoListaCancion* agregarAlFinal(nodoListaCancion*, nodoListaCancion*);
nodoListaCancion* buscarUltimo(nodoListaCancion*);
nodoListaCancion* agregarEnOrdenPorNombreDeCancion(nodoListaCancion*, nodoListaCancion*);
void mostrarCancion(Cancion);
void mostrarLista(nodoListaCancion*);
nodoListaCancion* borrarNodoPorIdCancion(nodoListaCancion*, int id);



///FUNCIONES DE ÁRBOLES
nodoArbolCancion* inicArbol();
nodoArbolCancion* crearNodoArbol(Cancion);
nodoArbolCancion* insertarNodoArbol(nodoArbolCancion*, Cancion);
void inorderArbol(nodoArbolCancion*);
void preorderArbol(nodoArbolCancion*);
void postorderArbol(nodoArbolCancion*);
nodoArbolCancion* buscarCancion(nodoArbolCancion*, int idCancion);
nodoArbolCancion* borrarUnNodoArbol(nodoArbolCancion*, int idCancion);
nodoArbolCancion* nodoChico(nodoArbolCancion*);
void cargarArbolDesdeArchivo(nodoArbolCancion*);*/


///Funciones de ABML Canción
int generarIdCancion();
void guardarCancion(Cancion);
int contarCancionesEnArchivo();
void pasarArchivoCancionesAArreglo(int);
void eliminarCancion(char[]);
int verificarExistenciaCancion(char[]);
void modificarCancion(int);
void mostrarArchivoCanciones(int);
void reproducirCancion(char[]);
void obtenerGeneroPorIdCancion(int, char[]);


#endif // CANCION_H_INCLUDED
