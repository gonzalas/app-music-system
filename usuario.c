#include "usuario.h"
#include "cancion.h"




int verificarUsuario(char usuario[], char pass[]){
    ///Si verifica = 0 -> el usuario no está en el archivo, si verifica = 1 -> el usuario sí está
    int verifica = 0;
    FILE * archivo = fopen(archivoUsuarios, "rb");
    if(archivo != NULL){
        Usuario aux;
        while(fread(&aux, sizeof(Usuario), 1, archivo) > 0 && verifica == 0){
            if(strcmpi(aux.nombreUsuario, usuario) == 0 && strcmpi(aux.pass, pass) == 0 && aux.eliminado == 0){
                verifica = 1;
            }
        }
    }
    fclose(archivo);
    return verifica;
}




Usuario menuRegistrarUsuario(){
    Usuario aux;
    char usuario[30];
    printf("- REGISTRAR -\n\n\n");
    printf("Nombre de usuario: ");
    fflush(stdin);
    gets(usuario);
    int verificar;
    do{
        verificar = verificarNombreUsuario(usuario);
        if(verificar == 1){
            strcpy(aux.nombreUsuario, usuario);
        } else {
            printf("\n\n*Advertencia*: Ya se encuentra un usuario registrado con ese nombre. Ingrese otro: ");
            fflush(stdin);
            gets(usuario);
        }
    }while(verificar != 1);
    printf("\n\nContrase%ca: ",164);
    fflush(stdin);
    gets(aux.pass);
    printf("\n\nA%co de nacimiento (4 d%cgitos): ",164,161);
    fflush(stdin);
    scanf("%i",&aux.anioNacimiento);
    printf("\n\nNacionalidad: ");
    fflush(stdin);
    gets(aux.pais);
    printf("\n\nG%cnero: ",130);
    fflush(stdin);
    scanf("%c",&aux.genero);
    printf("\n\nRol (0.ADMIN | 1.USUARIO): ");
    fflush(stdin);
    scanf("%i",&aux.rol);
    aux.eliminado = 0;
    aux.idUsuario = generarIdUsuario();

    return aux;
}

int verificarNombreUsuario(char usuario[]){
    int disponible = 1;
    FILE * archivo = fopen(archivoUsuarios, "rb");
    if(archivo != NULL){
        Usuario aux;
        while(fread(&aux, sizeof(Usuario), 1, archivo) > 0 && disponible == 1){
            if(strcmpi(aux.nombreUsuario, usuario) == 0 && aux.eliminado == 0){
                disponible = 0;
            }
        }
    }
    fclose(archivo);
    return disponible;
}

int generarIdUsuario(){
    int id = 0;
    FILE * archivo = fopen(archivoUsuarios, "rb");
    if(archivo != NULL){
        fseek(archivo, 0, SEEK_END);
        id = ftell(archivo)/sizeof(Usuario);
    }
    fclose(archivo);
    return id;
}

void mostrarUsuario(Usuario u){
    char rol[10];
    if(u.rol == 0){
        strcpy(rol, "ADMIN");
    } else if (u.rol == 1){
        strcpy(rol, "USER");
    }
    printf("Nombre de Usuario: %s\t|\tContrase%ca: %s\t|\tRol: %s\n",u.nombreUsuario, 164, u.pass, rol);
}

void mostrarArchivoUsuarios(){
    printf("- LISTADO DE USUARIOS REGISTRADOS -\n\n\n");
    FILE * archivo = fopen(archivoUsuarios, "rb");
    if(archivo != NULL){
        Usuario aux;
        while(fread(&aux, sizeof(Usuario), 1, archivo) > 0){
            if(aux.eliminado == 0){
                mostrarUsuario(aux);
            }
        }
    }
    fclose(archivo);
}

int contarUsuariosEnArchivo(){
    int total = 0;
    FILE * archivo = fopen(archivoUsuarios, "rb");
    if(archivo != NULL){
        Usuario aux;
        while(fread(&aux, sizeof(Usuario), 1, archivo) > 0){
            if(aux.eliminado == 0){
                total++;
            }
        }
    }
    fclose(archivo);
    return total;
}



void mostrarArchivoUsuariosPorNombre(){
    int validos = contarUsuariosEnArchivo();
    printf("Usuarios registrados: %i\n\n",validos);
    Usuario listado[validos];
    int i = 0;
    printf("- LISTADO DE USUARIOS REGISTRADOS -\n\n\n");
    FILE * archivo = fopen(archivoUsuarios, "rb");
    if(archivo != NULL){
        Usuario aux;
        while(fread(&aux, sizeof(Usuario), 1, archivo) > 0){
            if(aux.eliminado == 0){
                listado[i] = aux;
                i++;
            }
        }
    }
    fclose(archivo);

    ///Función para ordenar alfabéticamente el arreglo y mostrarlo
    ordenarListadoPorNombreYMostrar(listado, validos);
}


void eliminarUsuario(char nombre[]){
    int flag = 0;
    FILE * archivo = fopen(archivoUsuarios, "r+b");
    if(archivo != NULL){
        Usuario aux;
        while(fread(&aux, sizeof(Usuario), 1, archivo) > 0 && flag == 0){
            if(strcmpi(aux.nombreUsuario, nombre) == 0 && aux.eliminado == 0){
                aux.eliminado = 1;
                fseek(archivo, sizeof(Usuario)*(-1), SEEK_CUR);
                fwrite(&aux, sizeof(Usuario), 1, archivo);
                flag = 1;
                fclose(archivo);
            }
        }
    }
    fclose(archivo);
}

void modificarUsuario(char nombre[]){
    int flag = 0;
    FILE * archivo = fopen(archivoUsuarios, "r+b");
    if(archivo != NULL){
        Usuario aux;
        while(fread(&aux, sizeof(Usuario), 1, archivo) > 0 && flag == 0){
            if(strcmpi(aux.nombreUsuario, nombre) == 0 && aux.eliminado == 0){
                Usuario modificado = pedirInfoParaModificar(aux);
                fseek(archivo, sizeof(Usuario)*(-1), SEEK_CUR);
                fwrite(&modificado, sizeof(Usuario), 1, archivo);
                flag = 1;
                fclose(archivo);
            }
        }
    }
    fclose(archivo);
    eliminarUsuario(nombre);
}



void mostrarPerfilUsuario(Usuario u){
    char rol[10], genero[10];
    u.rol == 0 ? strcpy(rol, "ADMIN") : strcpy(rol, "USER");
    u.genero == 'm' ? strcpy(genero, "Masculino") : strcpy(genero, "Femenino");
    linea();
    printf("\n\nID Usuario: %i",u.idUsuario);
    printf("\n\n\tNombre de usuario: %s\n\n",u.nombreUsuario);
    printf("\tContrase%ca: %s\n\n",164,u.pass);
    printf("\tA%co de nacimiento: %i\n\n",164,u.anioNacimiento);
    printf("\tG%cnero: %s\n\n",130,genero);
    printf("\tNacionalidad: %s\n\n",u.pais);
    printf("\tCuenta: %s\n\n",rol);
    linea();
}


void mostrarListadoUsuarios(Celda adl[], int validos){
    Usuario*aux = (Usuario*)malloc(sizeof(Usuario)*validos);
    for(int i = 0; i < validos; i++){
        aux[i] = adl[i].usuario;
    }
    ///Ordenamos el arreglo auxiliar
    printf("%c Usuarios registrados: %i  %c\n",218,validos,191);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n",192,196, 196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
    ordenarListadoPorNombreYMostrar(aux, validos);
}

int eliminarUsuarioDeAdl(Celda adl[], int validos, char nombre[]){
    int i = 0, flag = 0;
    while(i < validos && !flag){
        if(strcmp(adl[i].usuario.nombreUsuario, nombre) == 0){
            adl[i].usuario.eliminado = 1;
            flag = 1;
        }
        i++;
    }
    validos--;
    return validos;
}

void modificarUsuarioDeAdl(Celda adl[], int validos, char nombre[]){
    int i = 0, flag = 0, pos = -1;
    Usuario aux;
    while(i < validos && !flag){
        if(strcmp(adl[i].usuario.nombreUsuario, nombre) == 0){
            aux = pedirInfoParaModificar(adl[i].usuario);
            pos = i;
            flag = 1;
        }
        i++;
    }
    adl[pos].usuario = aux;
}

void pasarListaAArchivo(Celda adl[], int validos){
    FILE * archivo = fopen(archivoUsuarios, "wb");
    Usuario aux;
    for(int i = 0; i < validos; i++){
        aux = adl[i].usuario;
        fwrite(&aux, sizeof(Usuario), 1, archivo);
    }
    fclose(archivo);
}
