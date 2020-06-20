#include "playlist.h"


int generarIdPlaylist(){
    int id = 0;
    FILE * archivo = fopen(archivoPlaylist, "rb");
    if(archivo){
        fseek(archivo, 0, SEEK_END);
        id = ftell(archivo)/sizeof(Playlist);
    }
    fclose(archivo);
    return id;
}

int existePlaylist(Usuario u){
    int existe = 0, flag = 0;
    FILE * archivo = fopen(archivoPlaylist, "rb");
    if(archivo){
        Playlist aux;
        while(fread(&aux, sizeof(Playlist), 1, archivo) > 0 && !flag){
            if(aux.idUsuario == u.idUsuario){
                existe = 1;
                flag = 1;
            }
        }
    }
    fclose(archivo);
    return existe;
}

int buscarPlaylist(Usuario u){
    int id, flag = 0;
    FILE * archivo = fopen(archivoPlaylist, "rb");
    Playlist aux;
    while(fread(&aux, sizeof(Playlist), 1, archivo) > 0 && !flag){
        if(aux.idUsuario == u.idUsuario){
            id = aux.idPlaylist;
            flag = 1;
        }
    }
    fclose(archivo);
    return id;
}

void agregarCancionAPlaylist(Usuario u, Cancion c){
    Playlist playlist;
    playlist.idCancion = c.idCancion;
    playlist.idUsuario = u.idUsuario;
    if(existePlaylist(u) == 0){
        playlist.idPlaylist = generarIdPlaylist();
    } else {
        playlist.idPlaylist = buscarPlaylist(u);
    }
    FILE * archivo = fopen(archivoPlaylist, "ab");
    fwrite(&playlist, sizeof(Playlist), 1, archivo);
    fclose(archivo);
}

void mostrarPlaylist(Playlist p){
    printf("PlayList ID: %i\tUsuario ID: %i\tCanci%cn ID: %i\n",p.idPlaylist,p.idUsuario,162,p.idCancion);
}

void recorrerPlayList(Usuario u){
    FILE * archivo = fopen(archivoPlaylist, "rb");
    if(archivo){
        Playlist p;
        while(fread(&p, sizeof(Playlist), 1, archivo) > 0){
            if(p.idUsuario == u.idUsuario){
                mostrarPlaylist(p);
            }
        }
    }
    fclose(archivo);
}

int ultimaCancionAgregadaAPlaylist(int idUsuario){
    int idCancion = -1;
    FILE * archivo = fopen(archivoPlaylist, "rb");
    if(archivo){
        Playlist aux;
        while(fread(&aux, sizeof(Playlist), 1, archivo) > 0){
            if(aux.idUsuario == idUsuario){
                    idCancion = aux.idCancion;
              }
        }
    }
    fclose(archivo);
    return idCancion;
}

int comprobarExisteCancionEnPlaylist(Cancion c, Usuario u){
    int existe = 0;     /// --> no existe
    FILE * archivo = fopen(archivoPlaylist, "rb");
    if(archivo){
        Playlist p;
        while(fread(&p, sizeof(Playlist), 1, archivo) > 0 && !existe){
            if(c.idCancion == p.idCancion){
                if(u.idUsuario == p.idUsuario){
                    existe = 1;
                }
            }
        }
    }
    fclose(archivo);
    return existe;
}

