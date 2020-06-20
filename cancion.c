#include "cancion.h"


nodoListaCancion* inicLista(){
    return NULL;
}

nodoListaCancion* crearNodoLista(Cancion c){
    nodoListaCancion * aux = (nodoListaCancion*)malloc(sizeof(nodoListaCancion));
    aux->cancion = c;
    aux->sig = NULL;
    return aux;
}

nodoListaCancion* agregarAlPrincipio(nodoListaCancion * lista, nodoListaCancion * nuevo){
    nuevo->sig = lista;
    lista = nuevo;
    return lista;
}

nodoListaCancion* buscarUltimo(nodoListaCancion * lista){
    nodoListaCancion * ultimo;
    if(lista != NULL){
        ultimo = buscarUltimo(lista->sig);
    }
    return ultimo;
}

nodoListaCancion* agregarAlFinal(nodoListaCancion * lista, nodoListaCancion * nuevo){
    if(!lista){
        lista = nuevo;

    } else {
        nodoListaCancion * ultimo = buscarUltimo(lista);
        ultimo->sig = nuevo;
    }
    return lista;
}

nodoListaCancion* agregarEnOrdenPorNombreDeCancion(nodoListaCancion * lista, nodoListaCancion * nuevo){
    if(!lista){
        lista = nuevo;

    } else {
        if(strcmp(nuevo->cancion.titulo, lista->cancion.titulo) < 0){
            lista = agregarAlPrincipio(lista, nuevo);

        } else {
            nodoListaCancion* ante;
            nodoListaCancion* seg = lista;
            while(seg != NULL && strcmp(nuevo->cancion.titulo, seg->cancion.titulo) > 0){
                ante = seg;
                seg = seg->sig;
            }
            ante->sig = nuevo;
            nuevo->sig = seg;
        }
    }
    return lista;
}

void mostrarCancion(Cancion c){
    printf("\n\nID Canci%cn: %i\n",162, c.idCancion);
    printf("\tT%ctulo: %s\n",161,c.titulo);
    printf("\tArtista: %s\n",c.artista);
    printf("\tDuraci%cn: %.2f minutos\n",162,c.duracion);
    printf("\t%clbum: %s\n",181,c.album);
    printf("\tA%co: %i\n",164,c.anio);
    printf("\tG%cnero: %s\n",130,c.genero);
    printf("\tComentario: %s\n\n",c.comentario);
    linea();
}

void mostrarLista(nodoListaCancion * lista){
    if(lista != NULL){
        mostrarCancion(lista->cancion);
        mostrarLista(lista->sig);
    }
}

nodoListaCancion* borrarNodoPorIdCancion(nodoListaCancion * lista, int id){
    if(lista && lista->cancion.idCancion == id){
        nodoListaCancion * aux = lista;
        lista = lista->sig;
        free(aux);

    } else {
        nodoListaCancion * ante;
        nodoListaCancion * seg = lista;
        while(seg != NULL && seg->cancion.idCancion != id){
            ante = seg;
            seg = seg->sig;
        }
        if(seg != NULL){
            ante->sig = seg->sig;
            free(seg);
        }
    }
    return lista;
}



///***********************************************************************************************//

nodoArbolCancion* inicArbol(){
    return NULL;
}

nodoArbolCancion* crearNodoArbol(Cancion c){
    nodoArbolCancion * aux = (nodoArbolCancion*)malloc(sizeof(nodoArbolCancion));
    aux->cancion = c;
    aux->izq = NULL;
    aux->der = NULL;
    return aux;
}

nodoArbolCancion* insertarNodoArbol(nodoArbolCancion * arbol, Cancion c){
    if(!arbol){
        arbol = crearNodoArbol(c);

    } else {
        if(c.idCancion < arbol->cancion.idCancion){
            arbol->izq = insertarNodoArbol(arbol->izq, c);

        } else {
            arbol->der = insertarNodoArbol(arbol->der, c);
        }
    }
    return arbol;
}


void inorderArbol(nodoArbolCancion * arbol){
    if(arbol){
        inorderArbol(arbol->izq);
        mostrarCancion(arbol->cancion);
        inorderArbol(arbol->der);
    }
}

void preorderArbol(nodoArbolCancion * arbol){
    if(arbol){
        mostrarCancion(arbol->cancion);
        preorderArbol(arbol->izq);
        preorderArbol(arbol->der);
    }
}

void postorderArbol(nodoArbolCancion * arbol){
    if(arbol){
        postorderArbol(arbol->izq);
        postorderArbol(arbol->der);
        mostrarCancion(arbol->cancion);
    }
}

nodoArbolCancion* buscarCancion(nodoArbolCancion * arbol, int id){
    nodoArbolCancion * rta = NULL;
    if(arbol){
        if(arbol->cancion.idCancion == id){
            rta = arbol;

        } else {
            if(arbol->cancion.idCancion < id){
                rta = buscarCancion(arbol->izq, id);

            } else {
                rta = buscarCancion(arbol->der, id);
            }
        }
    }
    return rta;
}


nodoArbolCancion* nodoChico(nodoArbolCancion * arbol){
    nodoArbolCancion * aux = arbol;
    while(aux && aux->izq != NULL){
        aux = aux->izq;
    }
    return aux;
}

nodoArbolCancion* borrarUnNodoArbol(nodoArbolCancion * arbol, int id){
    if(arbol){
        if(id < arbol->cancion.idCancion){
            arbol->izq = borrarUnNodoArbol(arbol->izq, id);

        } else if(id > arbol->cancion.idCancion){
            arbol->der = borrarUnNodoArbol(arbol->der, id);

        } else{
                if(arbol->izq == NULL){
                    nodoArbolCancion * aux = arbol->der;
                    free(arbol);
                    return aux;

                } else if(arbol->der == NULL){
                    nodoArbolCancion * aux = arbol->izq;
                    free(arbol);
                    return aux;
                }
                nodoArbolCancion * aux = nodoChico(arbol->der);
                arbol->cancion.idCancion = aux->cancion.idCancion;
                arbol->der = borrarUnNodoArbol(arbol->der, aux->cancion.idCancion);
        }
    }
    return arbol;
}


nodoArbolCancion* cargarArbolDesdeArchivo(nodoArbolCancion * arbol){
    int validos = contarCancionesEnArchivo();
    Cancion listado[validos];
    pasarArchivoCanArreglo(listado, validos);
    ordenacionSeleccionCancion(listado, validos);       ///--> ordena el arreglo por título, así se "desordenan" los id
    for(int i = 0; i < validos; i++){
        arbol = insertarNodoArbol(arbol, listado[i]);
    }
    return arbol;
}

void mostrarCanciones(nodoArbolCancion*arbol){
    inorderArbol(arbol);
}

int recorrerArbolInorder(nodoArbolCancion*arbol, Cancion listado[], int i){
    if(arbol){
        i = recorrerArbolInorder(arbol->izq, listado, i);
        listado[i] = arbol->cancion;
        i++;
        i = recorrerArbolInorder(arbol->der, listado, i);
    }
    return i;
}

void pasarArbolAArreglo(nodoArbolCancion*arbol, int verCanciones){
    int validos = contarCancionesEnArchivo();
    Cancion listado[validos];

    validos = recorrerArbolInorder(arbol, listado, 0);

     if(verCanciones == 1){
        ordenacionSeleccionCancion(listado, validos);       /// -> ordena por título
        mostrarArregloCancion(listado, validos);
    } else {
        ordenacionInsercionCancion(listado, validos);       /// -> ordena por género
        mostrarArregloCancion(listado, validos);
    }
}

int verificarExisteCancion(int id){
    int existe = 0;
    FILE * archivo = fopen(archivoCanciones, "rb");
    if(archivo){
        Cancion aux;
        while(fread(&aux, sizeof(Cancion), 1, archivo) > 0 && !existe){
            if(aux.idCancion == id){
                existe = 1;
            }
        }
    }
    fclose(archivo);
    return existe;
}

nodoArbolCancion* recorrerArbolParaModificar(nodoArbolCancion*arbol, int id){
    if(arbol){
        if(arbol->cancion.idCancion == id){
            Cancion nuevo = pedirDatosParaModificar(id);
            arbol->cancion = nuevo;
        }
        arbol->izq = recorrerArbolParaModificar(arbol->izq, id);
        arbol->der = recorrerArbolParaModificar(arbol->der, id);
    }
    return arbol;
}

nodoArbolCancion* modificarCancionEnArbol(nodoArbolCancion*arbol, int id){
    return recorrerArbolParaModificar(arbol, id);
}

void recorrerArbol(nodoArbolCancion*arbol, FILE *archivo){
    if(arbol){
        Cancion aux = arbol->cancion;
        fwrite(&aux, sizeof(Cancion), 1, archivo);
        recorrerArbol(arbol->izq, archivo);
        recorrerArbol(arbol->der, archivo);
    }
}

void pasarArbolAArchivo(nodoArbolCancion*arbol){
    FILE * archivo = fopen(archivoCanciones, "wb");
    Cancion aux;
    recorrerArbol(arbol, archivo);
    fclose(archivo);
}

///****************************************************************************************//

int generarIdCancion(){
    int id = 0;
    FILE * archivo = fopen(archivoCanciones, "rb");
    if(archivo){
        fseek(archivo, 0, SEEK_END);
        id = ftell(archivo)/sizeof(Cancion);
    }
    fclose(archivo);
    return id;
}




void guardarCancion(Cancion c){
    FILE * archivo = fopen(archivoCanciones, "ab");
    fwrite(&c, sizeof(Cancion), 1, archivo);
    fclose(archivo);
}

int contarCancionesEnArchivo(){
    int total = 0;
    FILE * archivo = fopen(archivoCanciones, "rb");
    if(archivo){
        Cancion aux;
        while(fread(&aux, sizeof(Cancion), 1, archivo) > 0){
            if(aux.eliminado == 0){
                total++;
            }
        }
    }
    fclose(archivo);
    return total;
}

void pasarArchivoCancionesAArreglo(int verCanciones){
    int validos = contarCancionesEnArchivo(), i = 0;
    Cancion listado[validos];
    FILE * archivo = fopen(archivoCanciones, "rb");
    if(archivo){
        Cancion aux;
        while(fread(&aux, sizeof(Cancion), 1, archivo) > 0){
            if(aux.eliminado == 0){
                listado[i] = aux;
                i++;
            }
        }
    }
    fclose(archivo);

    if(verCanciones == 1){
        ordenacionSeleccionCancion(listado, validos);       /// -> ordena por título
        mostrarArregloCancion(listado, validos);
    } else {
        ordenacionInsercionCancion(listado, validos);       /// -> ordena por género
        mostrarArregloCancion(listado, validos);
    }
}




void eliminarCancion(char titulo[]){
    int flag = 0;
    FILE * archivo = fopen(archivoCanciones, "r+b");
    if(archivo){
        Cancion aux;
        while(fread(&aux, sizeof(Cancion), 1, archivo) > 0 && !flag){
            if(strcmpi(aux.titulo, titulo) == 0 && aux.eliminado == 0){
                aux.eliminado = 1;
                fseek(archivo, sizeof(Cancion)*(-1), SEEK_CUR);
                fwrite(&aux, sizeof(Cancion), 1, archivo);
                flag = 1;
                fclose(archivo);
            }
        }
    }
    fclose(archivo);
}

int verificarExistenciaCancion(char titulo[]){
    int existe = 0;
    FILE * archivo = fopen(archivoCanciones, "rb");
    if(archivo){
        Cancion aux;
        while(fread(&aux, sizeof(Cancion), 1, archivo) > 0 && !existe){
            if(strcmpi(aux.titulo, titulo) == 0 && aux.eliminado == 0){
                existe = 1;
            }
        }
    }
    fclose(archivo);
    return existe;
}

void modificarCancion(int id){
    int flag = 0;
    FILE * archivo = fopen(archivoCanciones, "r+b");
    if(archivo){
        Cancion aux;
        while(fread(&aux, sizeof(Cancion), 1, archivo) > 0 && !flag){
            if(aux.idCancion == id && aux.eliminado == 0){
                fseek(archivo, sizeof(Cancion)*(-1), SEEK_CUR);
                Cancion modificada = pedirDatosParaModificar(id);
                fwrite(&modificada, sizeof(Cancion), 1, archivo);
                flag = 1;
                fclose(archivo);
            }
        }
    }
    fclose(archivo);
}






void mostrarArchivoCanciones(int num){
    int validos = contarCancionesEnArchivo();
    Cancion listado[validos];
    pasarArchivoCanArreglo(listado, validos);
    switch(num)
    {
    case 1: ///mostrar canciones por id
        for(int i = 0; i < validos; i++){
            mostrarCancion(listado[i]);
        }
        printf("\n\n\n");
        break;
    case 2: ///mostrar canciones por título
        ordenacionSeleccionCancion(listado, validos);
        for(int i = 0; i < validos; i++){
            mostrarCancion(listado[i]);
        }
        printf("\n\n\n");
        break;
    }
}

void reproducirCancion(char ruta[]){
    char folder[] = {".\\Songs\\"};
    char link[30];
    strcat(folder, ruta);
    strcpy(link,folder);
    system(link);
}

void obtenerGeneroPorIdCancion(int idCancion, char genero[]){
    FILE * archivo = fopen(archivoCanciones, "rb");
    if(archivo){
        Cancion aux;
        int flag = 0;
        while(fread(&aux, sizeof(Cancion), 1, archivo) > 0 && !flag){
            if(aux.idCancion == idCancion){
                strcpy(genero, aux.genero);
                flag = 1;
                fclose(archivo);
            }
        }
    }
    fclose(archivo);
}


void cincoCancionesRecomendadas(Cancion listado[], char genero[]){
    FILE * archivo = fopen(archivoCanciones, "rb");
    if(archivo){
        int i = 0;
        Cancion aux;
        while(fread(&aux, sizeof(Cancion), 1, archivo) > 0 && i < 5){
            if(strcmp(aux.genero, genero) == 0){
                listado[i] = aux;
                i++;
            }
        }
    }
    fclose(archivo);
}

void mostrarCancionesRecomendadas(Cancion listado[], int validos){
    printf("\n\n\n");
    for(int i = 0; i < validos; i++){
        printf("\t\t\t%c %s  -\t %s\n\n\n",254,listado[i].titulo, listado[i].artista);
    }
}

