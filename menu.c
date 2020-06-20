#include "menu.h"


void comenzarPrograma(){

    recuadro("<< PLAYSIC >>");
    printf("\n\n\n\n\n");
    printf("\t\t\t\t   Tu app de m%csica favorita\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",163);
    getchar();
    system("cls");

    int tecla;

    do{
       textoPrimeraVentana();
       fflush(stdin);
       printf("\t\t");
       scanf("%i",&tecla);

       ///Mensaje de que la opción ingresada no es válida
       if(tecla != 0 && tecla != 1 && tecla != 2){
            opcionInvalida();
       }
       system("cls");

       ///Si 1 -> loguearse
       if(tecla == 1){
            ///Definimos un arreglo de listas de dimensión justa
            Celda *arregloDeListas;
            int validos = contarUsuariosEnArchivo();
            arregloDeListas = (Celda*)malloc(sizeof(Celda)*validos);

            ///Se carga el arreglo con usuarios
            validos = cargarADL(arregloDeListas, validos);
            ///Se cargan las canciones de cada usuario
            cargarCancionesEnADL(arregloDeListas, validos);

            ///Definimos árbol de canciones
            nodoArbolCancion*arbol = inicArbol();
            ///Carga de árbol de canciones
            arbol = cargarArbolDesdeArchivo(arbol);

            ///login
            loginUsuario(arregloDeListas, validos, arbol);
       } else
       ///Si 2 -> registrarse
       if (tecla == 2){
            registrarUsuario();
       }

    }while(tecla != 0);
}

void textoPrimeraVentana(){
    printf("\n\n\t\t1. Login\n\n");
    printf("\t\t2. Registrarse\n\n\n\n\t\t%c\n\n\n\n",175);
    printf("\t\t0. Salir del sistema\n\n");
}

void opcionInvalida(){
    printf("\n\n\n\n\t\tLa opci%cn ingresada no es v%clida.\n\n\t\t",162,160);
    system("pause");
}



void textoPantallaLogin(){
    printf("\n\n\t\t1. Login\n\n");
    printf("\t\t2. Volver\n\n");
}



void textoRegistrarUsuario(){
    printf("\n\n\t\t- REGISTRAR USUARIO -\n\n\n");
    printf("\t\t1. Registrar\n\n");
    printf("\t\t2. Volver\n\n");
}



void menuPrincipal(Usuario u, Celda adl[], int validos, nodoArbolCancion*arbol){
    if(u.rol == 0){     ///Si el usuario es ADMIN
        menuAdmin(adl, validos, arbol);
    } else
        if(u.rol == 1){     ///Si el usuario es USER
            menuUser(u, adl, validos, arbol);
        }
}


void menuAdmin(Celda adl[], int validos, nodoArbolCancion*arbol)
{
    int tecla, verCanciones, verificar, id, idCancion;
    char nombreEliminar[30], nombreModificar[30], cancionEliminar[30];
    Cancion c;

    do
    {

        do
        {
            textoMenuAdmin();
            fflush(stdin);
            printf("\t\t");
            scanf("%i",&tecla);
            (tecla < 0 || tecla > 7) ? opcionInvalida() : 0;
            system("cls");
        }
        while(tecla < 0 || tecla > 7);

        if(tecla != 0)
        {

            switch(tecla)
            {
            case 1: ///listado usuarios -> cargar en un arreglo y mostrar por nombre de usuario
                //mostrarArchivoUsuariosPorNombre();
                mostrarListadoUsuarios(adl, validos);
                printf("\n\n\n\n");
                system("pause");
                system("cls");
                break;

            case 2: ///eliminar cuenta
                printf("Ingrese el usuario que desea eliminar: ");
                fflush(stdin);
                gets(nombreEliminar);
                int verificado = verificarNombreUsuario(nombreEliminar);    ///si es 0 -> está en archivo
                if(verificado == 0)
                {
                    //eliminarUsuario(nombreEliminar);
                    validos = eliminarUsuarioDeAdl(adl, validos, nombreEliminar);
                    printf("\n\n\nEl usuario '%s' fue eliminado del sistema.\n\n\n\n",nombreEliminar);
                }
                else
                {
                    printf("\n\nNo pudo eliminarse el usuario '%s', posiblemente porque no se encuentra en el sistema.\n\n\n\n",nombreEliminar);
                }
                system("pause");
                system("cls");
                break;

            case 3: ///modificar datos de una cuenta -> se ingresa número de usuario
                printf("Ingrese el usuario que desea modificar: ");
                fflush(stdin);
                gets(nombreModificar);
                int verif = verificarNombreUsuario(nombreModificar);    ///si es 0 -> está en archivo
                if(verif == 0)
                {
                    //modificarUsuario(nombreModificar);
                    modificarUsuarioDeAdl(adl, validos, nombreModificar);
                    printf("\n\n\nEl usuario '%s' fue modificado exitosamente.\n\n\n\n",nombreModificar);
                }
                else
                {
                    printf("\n\nNo pudo modificarse el usuario '%s', posiblemente porque no se encuentra en el sistema.\n\n\n\n",nombreModificar);
                }
                system("pause");
                system("cls");
                break;

            case 4: ///listado de canciones -> ver canciones por título(ordenado por selección) y por género(por inserción)
                do{
                    textoVerCanciones();
                    fflush(stdin);
                    scanf("%i",&verCanciones);
                    system("cls");
                    if(verCanciones == 1 || verCanciones == 2){
                        //pasarArchivoCancionesAArreglo(verCanciones);
                        pasarArbolAArreglo(arbol, verCanciones);
                    }
                    printf("\n\n\n");
                    system("pause");
                    system("cls");
                }while(verCanciones < 0 || verCanciones > 2);
                break;

            case 5: ///agregar canciones -> formulario de alta
                arbol = insertarNodoArbol(arbol, cargarCancion());
                //guardarCancion(c);
                printf("\n\n\t%c La canci%cn se ha registrado exitosamente en el sistema.\n\n\n\n",175,162);
                system("pause");
                system("cls");
                break;

            case 6: ///eliminar canciones
                printf("Ingrese el ID de la canci%cn a eliminar: ",162);
                fflush(stdin);
                scanf("%i",&idCancion);
                verificar = verificarExisteCancion(idCancion);
                //verificar = verificarExistenciaCancion(cancionEliminar);
                if(verificar == 1){
                    //eliminarCancion(cancionEliminar);
                    arbol = borrarUnNodoArbol(arbol, idCancion);
                    printf("\n\n\nLa canci%cn se ha eliminado exitosamente.\n\n\n\n",162);
                } else {
                    printf("\n\n\nLa canci%cn no pudo eliminarse, posiblemente porque no se encuentra registrada en el sistema.\n\n\n\n",162,cancionEliminar);
                }
                system("pause");
                system("cls");
                break;

            case 7: ///modificar canciones -> se ingresa el número de canción
                printf("Ingrese el n%cmero ID de la canci%cn que desea modificar: ",163,162);
                fflush(stdin);
                scanf("%i",&id);
                c = buscarCancionPorId(id);
                verificar = verificarExistenciaCancion(c.titulo);
                if(verificar == 1){
                    //modificarCancion(id);
                    arbol = modificarCancionEnArbol(arbol, id);
                    printf("\n\n\n%c La modificaci%cn se realiz%c exitosamente.\n\n\n\n",175,162,162);
                } else {
                    printf("\n\n\n%c No pudo realizarse la modificaci%cn, posiblemente porque el ID no es v%clido.\n\n\n\n",175,162,160);
                }
                system("pause");
                system("cls");
                break;
            }

            ///GUARDO TODOS LOS CAMBIOS REALIZADOS EN EL ARBOL AL ARCHIVO
            pasarArbolAArchivo(arbol);
            ///GUARDO TODOS LOS CAMBIOS REALIZADOS EN LA LISTA AL ARCHIVO
            pasarListaAArchivo(adl, validos);

        }
    }
    while(tecla != 0);
}

void textoVerCanciones(){
    printf("- LISTADO DE CANCIONES -\n\n");
    printf("\n\t1.\t%c Ver canciones por t%ctulo %c",175,161,174);
    printf("\n\t2.\t%c Ver canciones por g%cnero %c",175,130,174);
    printf("\n\n\n\t0.\tVolver atr%cs\n\n",160);
}

void textoMenuAdmin(){
    printf("- MEN%c PRINCIPAL -\n\n\n",233);
    printf("\n\t\t%c Usuarios %c\n\n\n",175, 174);
    printf("1. Listado de Usuarios\n\n");
    printf("2. Eliminar una cuenta\n\n");
    printf("3. Modificar una cuenta\n\n");
    printf("\n\t\t%c Canciones %c\n\n\n",175, 174);
    printf("4. Listado de Canciones\n\n");
    printf("5. Agregar canciones al sistema\n\n");
    printf("6. Eliminar canciones del sistema\n\n");
    printf("7. Modificar canciones del sistema\n\n");
    printf("\n\t\t%c Salir %c\n\n\n",175, 174);
    printf("0. Salir\n\n");
}


void menuUser(Usuario u, Celda adl[], int validos, nodoArbolCancion*arbol){
    int tecla, id, verifica, ultima;
    char genero[15];
    Cancion c, listaRecomendadas[5];

    do{
        do
        {
            textoMenuUser();
            fflush(stdin);
            scanf("%i",&tecla);
            (tecla < 0 || tecla > 5) ? opcionInvalida() : 0;
            system("cls");
        }
        while(tecla < 0 || tecla > 5);

        if(tecla != 0){

            switch(tecla){
                case 1: ///mostrar el perfil propio
                    mostrarPerfilUsuario(u);
                    printf("\n\n\n");
                    system("pause");
                    system("cls");
                    break;

                case 2: ///elegir canciones
                    srand(time(NULL));
                    //mostrarArchivoCanciones((rand()%2)+1);
                    mostrarCanciones(arbol);
                    printf("\n\n\t\t%c Ingrese el ID de la canci%cn que quiere agregar a su PlayList: ",175,162);
                    fflush(stdin);
                    scanf("%i",&id);
                    verifica = verificarExistenciaCancion(verifica = buscarCancionPorId(id).titulo);
                    if(verifica == 1){
                        agregarCancionAPlaylist(u, buscarCancionPorId(id));
                        printf("\n\n\tLa canci%cn se ha agregado exitosamente a su PlayList.\n\n\n",162);
                    } else {
                        printf("\n\n\tLa canci%cn no se ha podido agregar a su PlayList.\n\n\n",162);
                    }
                    system("pause");
                    system("cls");
                    break;

                case 3: ///mostrar playlist -> mostrar por nombre o género
                    recorrerPlayList(u);
                    printf("\n\n\n");
                    system("pause");
                    system("cls");
                    break;

                case 4: ///escuchar canción -> se ingresa idCanción y se agrega en la playlist del usuario
                    printf("Ingrese el ID de la canci%cn que desea reproducir: ",162);
                    fflush(stdin);
                    scanf("%i",&id);
                    c = buscarCancionPorId(id);
                    verifica = comprobarExisteCancionEnPlaylist(c, u);
                    if(verifica == 1){
                        printf("\n\t%c Reproduciendo...\n\n\n\n",175);
                        reproducirCancion(c.ruta);
                        printf("\n\n\n\n");
                    } else {
                        printf("\nError: no existe la canci%cn ingresada en su playlist.\n\n\n",162);
                    }
                    system("pause");
                    system("cls");
                    break;

                case 5: ///canciones recomendadas
                    ultima = ultimaCancionAgregadaAPlaylist(u.idUsuario);
                    obtenerGeneroPorIdCancion(ultima, genero);
                    cincoCancionesRecomendadas(listaRecomendadas, genero);
                    printf("\t%c Te recomendamos las siguientes canciones:\n\n",175);
                    mostrarCancionesRecomendadas(listaRecomendadas, 5);
                    printf("\n\n\n");
                    system("pause");
                    system("cls");
                    break;
            }
        }

    }while(tecla != 0);
}

void textoMenuUser(){
    printf("- MEN%c PRINCIPAL -\n\n\n",233);
    printf("1. Ver perfil\n\n");
    printf("2. Elegir canciones\n\n");
    printf("3. Mostrar playlist\n\n");
    printf("4. Escuchar canci%cn\n\n",162);
    printf("5. Canciones recomendadas\n\n");
    printf("0. Salir\n\n");
}



void linea(){
    for(int i = 0; i < 50; i++){
        printf("%c", 176);
    }
}


void loginUsuario(Celda adl[], int validos, nodoArbolCancion*arbol){
    char usuario[30], pass[20];
    int tecla;

    do{
        textoPantallaLogin();
        fflush(stdin);
        printf("\t\t");
        scanf("%i",&tecla);
        system("cls");

        if(tecla == 1){
            printf("- LOGIN -\n\n");
            printf("\tUsuario: ");
            fflush(stdin);
            gets(usuario);
            printf("\n\n\tContrase%ca: ",164);
            fflush(stdin);
            gets(pass);

            int verificado = verificarUsuario(usuario, pass);

            if(verificado == 0){
                printf("\n\n*Advertencia*: El usuario o la contrase%ca no son v%clidos.\n\n\n\n",164,160);
                system("pause");
                system("cls");
            } else {
                system("cls");
                menuPrincipal(buscarUsuario(usuario), adl, validos, arbol);
            }
        }

    }while(tecla != 2);
}


void agregarCancionAUsuario(Celda adl[], int validos, Cancion c, Usuario u){
    nodoListaCancion * cancion = crearNodoLista(c);
    int posUsuario = buscarPosicionUsuario(adl, validos, u);
    if(posUsuario == -1){

    }
    adl[posUsuario].listaCanciones = agregarAlFinal(adl[posUsuario].listaCanciones, cancion);
}

int buscarPosicionUsuario(Celda adl[], int validos, Usuario u){
    int pos = -1, i = 0;
    while(i < validos && !pos){
        if(adl[i].usuario.idUsuario == u.idUsuario){
            pos = i;
        }
        i++;
    }
    return pos;
}

Usuario buscarUsuario(char usuario[]){
    Usuario encontrado;
    short flag = 0;
    FILE * archivo = fopen(archivoUsuarios, "rb");
    if(archivo != NULL){
        Usuario aux;
        while(fread(&aux, sizeof(Usuario), 1, archivo) > 0 && flag == 0){
            if(strcmpi(aux.nombreUsuario, usuario) == 0){
                encontrado = aux;
                flag = 1;
            }
        }
    }
    fclose(archivo);
    return encontrado;
}

void guardarUsuario(Usuario u){
    FILE * archivo = fopen(archivoUsuarios, "ab");
    fwrite(&u, sizeof(Usuario), 1, archivo);
    fclose(archivo);
}

Usuario pedirInfoParaModificar(Usuario u){
    Usuario aux;
    printf("\n\nIngrese nuevo nombre: ");
    fflush(stdin);
    gets(aux.nombreUsuario);
    printf("\n\nIngrese nueva contrase%ca: ",164);
    fflush(stdin);
    gets(aux.pass);
    printf("\n\nIngrese nuevo a%co de nacimiento (4 d%cgitos): ",164,161);
    fflush(stdin);
    scanf("%i",&aux.anioNacimiento);
    printf("\n\nIngrese nueva nacionalidad: ");
    fflush(stdin);
    gets(aux.pais);
    printf("\n\nIngrese nuevo g%cnero: ",130);
    fflush(stdin);
    scanf("%c",&aux.genero);
    aux.eliminado = 0;
    aux.rol = u.rol;
    aux.idUsuario = u.idUsuario;
    return aux;
}

void ordenarListadoPorNombreYMostrar(Usuario listado[], int validos){
    ordenacionInsercionPorNombre(listado, validos);
    for(int i = 0; i < validos; i++){
        mostrarUsuario(listado[i]);
    }
}

void ordenacionInsercionPorNombre(Usuario listado[], int validos){
    int i = 0;
    while(i < validos - 1){
        insertarPorNombre(listado, listado[i+1], i);
        i++;
    }
}

void insertarPorNombre(Usuario listado[], Usuario u, int ultima){
    int i = ultima;
    while(i >= 0 && strcmpi(u.nombreUsuario, listado[i].nombreUsuario) < 0){
        listado[i+1] = listado[i];
        i--;
    }
    listado[i+1] = u;
}

void registrarUsuario(){
    int tecla;
    do{
        textoRegistrarUsuario();
        fflush(stdin);
        printf("\t\t");
        scanf("%i",&tecla);
        system("cls");

        if(tecla == 1){
            Usuario aux = menuRegistrarUsuario();
            guardarUsuario(aux);
            printf("\n\nSe ha registrado exitosamente.\n\n\n\n");
            system("pause");
            system("cls");
        } else
            if(tecla != 2){
                opcionInvalida();
            }

    }while(tecla != 2 && tecla != 1);
}

Cancion cargarCancion(){
    Cancion aux;

    printf("\n\nIngrese el t%ctulo: ",161);
    fflush(stdin);
    gets(aux.titulo);
    printf("\n\nIngrese el artista: ");
    fflush(stdin);
    gets(aux.artista);
    printf("\n\nIngrese el %clbum: ",160);
    fflush(stdin);
    gets(aux.album);
    printf("\n\nIngrese el a%co (4 d%cgitos): ",164,161);
    fflush(stdin);
    scanf("%i",&aux.anio);
    printf("\n\nIngrese el g%cnero: ",130);
    fflush(stdin);
    gets(aux.genero);
    printf("\n\nIngrese la duraci%cn (en minutos): ",162);
    fflush(stdin);
    scanf("%f",&aux.duracion);
    printf("\n\nIngrese un comentario: ");
    fflush(stdin);
    gets(aux.comentario);
    printf("\n\nIngrese la ruta del archivo: ");
    fflush(stdin);
    gets(aux.ruta);
    aux.idCancion = generarIdCancion();
    aux.eliminado = 0;

    return aux;
}


///Ordenar listado de canciones por título con algoritmo de selección
int posicionMenorCancion(Cancion listado[], int validos, int pos){
    Cancion menor = listado[pos];
    int posMenor = pos, index = pos+1;
    while(index < validos){
        if(strcmpi(menor.titulo, listado[index].titulo) > 0){
            menor = listado[index];
            posMenor = index;
        }
        index++;
    }
    return posMenor;
}

void ordenacionSeleccionCancion(Cancion listado[], int validos){
    int posMenor = -1, i = 0;
    Cancion aux;
    while(i < validos-1){
        posMenor = posicionMenorCancion(listado, validos, i);
        aux = listado[posMenor];
        listado[posMenor] = listado[i];
        listado[i] = aux;
        i++;
    }
}



///Ordenar listado de canciones por género con algoritmo de inserción
void insertarCancion(Cancion listado[], int validos, Cancion c, int ultima){
    int i = ultima;
    while(i >= 0 && strcmpi(c.genero, listado[i].genero) < 0){
        listado[i+1] = listado[i];
        i--;
    }
    listado[i+1] = c;
}

void ordenacionInsercionCancion(Cancion listado[], int validos){
    int i = 0;
    while(i < validos-1){
        insertarCancion(listado, validos, listado[i+1], i);
        i++;
    }
}


void mostrarArregloCancion(Cancion listado[], int validos){
    printf("- CANCIONES -\n\n\n");
    for(int i = 0; i < validos; i++){
        mostrarCancion(listado[i]);
    }
}

Cancion buscarCancionPorId(int id){
    Cancion encontrada;
    int flag = 0;
    FILE * archivo = fopen(archivoCanciones, "rb");
    if(archivo){
        Cancion aux;
        while(fread(&aux, sizeof(Cancion), 1, archivo) > 0 && !flag){
            if(aux.idCancion == id && aux.eliminado == 0){
                encontrada = aux;
                flag = 1;
            }
        }
    }
    fclose(archivo);
    return encontrada;
}

Cancion pedirDatosParaModificar(int id){
    char cambiarRuta = 'n';
    Cancion aux;

    printf("\n\nIngrese el nuevo t%ctulo: ",161);
    fflush(stdin);
    gets(aux.titulo);
    printf("\n\nIngrese el nuevo artista: ");
    fflush(stdin);
    gets(aux.artista);
    printf("\n\nIngrese el nuevo %clbum: ",160);
    fflush(stdin);
    gets(aux.album);
    printf("\n\nIngrese la nueva duraci%cn (en minutos): ",162);
    fflush(stdin);
    scanf("%f",&aux.duracion);
    printf("\n\nIngrese el nuevo a%co (4 d%cgitos): ",164,161);
    fflush(stdin);
    scanf("%i",&aux.anio);
    printf("\n\nIngrese el nuevo g%cnero: ",130);
    fflush(stdin);
    gets(aux.genero);
    printf("\n\nIngrese el nuevo comentario: ");
    fflush(stdin);
    gets(aux.comentario);
    aux.idCancion = id;
    aux.eliminado = 0;
    printf("\n\n\t%c %cDesea cambiar la ruta? (s/n): ",207, 168);
    fflush(stdin);
    scanf("%c",&cambiarRuta);
    if(cambiarRuta == 's'){
        printf("\n\nIngrese la nueva ruta: ");
        fflush(stdin);
        gets(aux.ruta);
    } else {
        Cancion original = buscarCancionPorId(id);
        strcpy(aux.ruta, original.ruta);
    }
    return aux;
}


void pasarArchivoCanArreglo(Cancion listado[], int validos){
    int i = 0;
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
}

void recuadro(char texto[]){
    printf("\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
    printf("\t\t\t\t\t  %s\n",texto);
    printf("\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
}

int cargarADL(Celda adl[], int dim){
    int validos = 0;
    FILE * archivo = fopen(archivoUsuarios, "rb");
    if(archivo){
        Usuario aux;
        while(fread(&aux, sizeof(Usuario), 1, archivo) > 0 && (validos < dim)){
            if(aux.eliminado == 0){
                adl[validos].usuario = aux;
                adl[validos].listaCanciones = inicLista();
                validos++;
            }
        }
    }
    fclose(archivo);
    return validos;
}

int buscarPosicionEnADL(Celda adl[], int validos, int idUsuario){
    int pos = -1, i = 0;
    while(i < validos && !pos){
        if(adl[i].usuario.idUsuario == idUsuario){
            pos = i;
        }
        i++;
    }
    return pos;
}

Cancion obtenerCancionDePlaylist(int idCancion){
    int flag = 0;
    Cancion retornada;
    FILE * archivo = fopen(archivoCanciones, "rb");
    if(archivo){
        Cancion aux;
        while(fread(&aux, sizeof(Cancion), 1, archivo) > 0 && !flag){
            if(aux.idCancion == idCancion){
                retornada = aux;
                flag = 1;
            }
        }
    }
    fclose(archivo);
    return retornada;
}

void cargarCancionesEnADL(Celda adl[], int validos){
    int pos = -1;
    FILE * archivo = fopen(archivoPlaylist, "rb");
    if(archivo){
        Playlist aux;
        while(fread(&aux, sizeof(Playlist), 1, archivo) > 0){
            pos = buscarPosicionEnADL(adl, validos, aux.idUsuario);
            if(pos != -1){
                Cancion cancion = obtenerCancionDePlaylist(aux.idCancion);
                adl[pos].listaCanciones = agregarAlFinal(adl[pos].listaCanciones, cancion);
            }
        }
    }
    fclose(archivo);
}
