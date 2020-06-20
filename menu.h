#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "usuario.h"
#include "cancion.h"
#include "playlist.h"

/// ARCHIVO DE USUARIOS
#define archivoUsuarios "usuarios.dat"

///ARCHIVO DE CANCIONES
#define archivoCanciones "canciones.dat"

///ARCHIVO DE PLAYLISTS
#define archivoPlaylist "playlist.dat"

typedef struct {
    int idUsuario;
    char nombreUsuario[30];
    char pass[20];
    int anioNacimiento;
    char genero;
    char pais[20];
    int eliminado;
    int rol;    /// 0 = ADMIN; 1 = USER
}Usuario;

typedef struct {
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
}Cancion;

typedef struct {
    Cancion cancion;
    struct nodoListaCancion * sig;
}nodoListaCancion;

typedef struct{
    Cancion cancion;
    struct nodoArbolCancion * izq;
    struct nodoArbolCancion * der;
}nodoArbolCancion;


typedef struct{
    Usuario usuario;
    nodoListaCancion * listaCanciones;
}Celda;

void comenzarPrograma();
void textoPrimeraVentana();
void opcionInvalida();
void textoPantallaLogin();
void textoRegistrarUsuario();
void menuPrincipal(Usuario, Celda[], int, nodoArbolCancion*);
void menuAdmin(Celda[], int, nodoArbolCancion*);
void textoMenuAdmin();
void menuUser(Usuario, Celda[], int, nodoArbolCancion*);
void textoMenuUser();
void linea();

void loginUsuario(Celda[], int, nodoArbolCancion*);
void agregarCancionAUsuario(Celda[],int,Cancion,Usuario);
int buscarPosicionUsuario(Celda[],int,Usuario);
Usuario buscarUsuario(char[]);
void guardarUsuario(Usuario);
Usuario pedirInfoParaModificar(Usuario);
void ordenarListadoPorNombreYMostrar(Usuario[], int);
void ordenacionInsercionPorNombre(Usuario[], int);
void insertarPorNombre(Usuario[], Usuario, int);
void registrarUsuario();
Usuario menuRegistrarUsuario();

Cancion cargarCancion();
int posicionMenorCancion(Cancion[], int, int);
void ordenacionSeleccionCancion(Cancion[], int);
void insertarCancion(Cancion[], int, Cancion, int);
void ordenacionInsercionCancion(Cancion[], int);
void mostrarArregloCancion(Cancion[], int);
Cancion buscarCancionPorId(int);
Cancion pedirDatosParaModificar(int);
void pasarArchivoCanArreglo(Cancion[], int);

void recuadro(char[]);
int cargarADL(Celda [], int);
int buscarPosicionEnADL(Celda [], int, int);
Cancion obtenerCancionDePlaylist(int);
void cargarCancionesEnADL(Celda[], int);


#endif // MENU_H_INCLUDED
