#ifndef PLAYLIST_H_INCLUDED
#define PLAYLIST_H_INCLUDED

#include "usuario.h"
#include "cancion.h"


typedef struct {
    int idPlaylist;
    int idUsuario;
    int idCancion;
}Playlist;

int generarIdPlaylist();
void agregarCancionAPlaylist(Usuario, Cancion);
int existePlaylist(Usuario);
int buscarPlaylist(Usuario);
void mostrarPlaylist(Playlist);
void recorrerPlayList(Usuario);
int ultimaCancionAgregadaAPlaylist(int);

#endif // PLAYLIST_H_INCLUDED
