# Playsic, music app system

It's a system made in C language to apply concepts of searching nodes as trees and linked lists.

This is my final practical work of subject "Laboratorio 2" at Universidad Tecnológica Nacional de Mar del Plata.


#### Manual de usuario

El sistema se trata del alta, baja, modificación y
consulta tanto de usuarios como de canciones
para llevar a cabo su tarea de servir como
plataforma para escuchar música. Contiene
ventanas muy simples e intuitivas y su
interacción se centra en la elección de la opción
deseada en consola para desplazarse por la
aplicación.

La primera ventana que aparece es un saludo con el nombre de la app “Playsic” y una línea
con el spot de la marca. Introduciendo cualquier tecla se accede a la segunda ventana en
donde tendremos que tomar la primera decisión en el programa. Si el que accede, es decir el
usuario, quiere ingresar a
su cuenta en caso de
tener una o, de lo
contrario, optará por
registrarse primero.
En caso de Registrarse, el
sistema proveerá de
información para que el
usuario ingrese y, a partir
de la misma, se creará un
perfil con los accesos correspondientes.

Cabe aclarar que un usuario estándar tendrá los privilegios para interactuar con el sistema de
manera que pueda ver su perfil, ver las canciones disponibles, agregarlas a su playlist,
escucharlas e, incluso, recibir recomendaciones de acuerdo a su gusto. En cambio, un
administrador no podrá escuchar música, sino que sus privilegios se centrarán en la
administración del sistema, controlando el listado de usuarios y canciones, y pudiendo
agregarlos o eliminarlos cuando crea conveniente, tanto a los usuarios como a las canciones.
Un usuario con privilegios de usuario debe recordar siempre su
nombre y contraseña, dado que, de lo contrario, debería hablar
con un administrador para que le facilite la información en caso
de olvidarse.

El administrador conoce los nombres de usuario, contraseñas y
rol de todos los que se han registrado. Además, puede agregar
las canciones que deseé al sistema. Sin embargo, para que
realmente el sistema la permite escuchar la música, tendrá que
incluir manualmente el archivo .mp3 dentro de la carpeta Songs
para que, de esta manera, la aplicación, cada vez que un
usuario quiera escuchar una
canción, tenga la misma a disposición y la busque a través de la
ruta que se le brindó cuando se cargó la canción.

En conclusión, el sistema resulta muy simple para su utilización,
tanto para el usuario estándar como para el administrador.
Cumple todas las funciones presentadas para que se pueda
escuchar música realmente. Por el lado del administrador,
deberá prestar atención al momento de cargar una canción de
que la ruta sea la misma que introdujo en la carpeta y con la
terminación “.mp3”. Aunque, en el caso de que la ruta estuviera
mal escrita, el propio sistema avisará del error y no se cerrará
bruscamente sino que proseguirá con el resto de las tareas.
