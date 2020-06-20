#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cancion.h"




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

/*typedef struct{
    Usuario usuario;
    nodoListaCancion * listaCanciones;
}Celda;*/



int verificarUsuario(char[], char[]);
int verificarNombreUsuario(char[]);
int generarIdUsuario();
void mostrarUsuario(Usuario);
void mostrarArchivoUsuarios();
void eliminarUsuario(char[]);
void modificarUsuario(char[]);
int contarUsuariosEnArchivo();
void mostrarArchivoUsuariosPorNombre();




#endif // USUARIO_H_INCLUDED
