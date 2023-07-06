#include "usuario.h"
#include "consumible.h"
#include "../config/files.h"

/** \fn stUsuario agregarUsuarioPorParametro(int id, int tipo, char nombre[], char apellido[], char dni[], char contrasena[], int edad, char telefono[], char genero, int hijos, char estadoCivil[])
 * \brief recibe por parametro los datos de la estructura stUsuario
 * \param id id
 * \param tipo huesped 0, empleado 1, administrador 2
 * \param nombre nombre de usuario
 * \param apellido apellido de usuario
 * \param dni "44860125"
 * \param contrasena contraseña del usuario
 * \param edad edad del usuario
 * \param telefono telefono del usuario
 * \param genero genero del usuario 'm','f','o'
 * \param hijos  cantidad de hijos del usuario
 * \param estadocivil  estado civil del usuario "Soltero, Divorciado, Viudo, Casado"
 * \return Devuelvo una estructura stUsuario con los datos cargados.
 */
stUsuario agregarUsuarioPorParametro(int id, int tipo, char nombre[], char apellido[], char dni[], char contrasena[], int edad, char telefono[], char genero, int hijos, char estadoCivil[])
{
    stUsuario u;
    u.id = id;
    u.borrado = 0;
    u.tipo = tipo; // huesped 0, empleado 1, administrador 2.
    strcpy(u.nombre, nombre);
    strcpy(u.apellido, apellido);
    strcpy(u.DNI, dni);
    strcpy(u.contrasena, contrasena);
    u.edad = edad; // años
    strcpy(u.telefono, telefono);
    u.genero = genero; // m = masculino , f = femenino, o = otros
    u.hijos = hijos;
    strcpy(u.estadoCivil, estadoCivil); // 0 soltero, 1 divorciado, 2 viudo, 3 casado
    return u;
}

/** \fn void agregarUsuarioArchivo()
 * \brief Abre el archivo al final y pide al usuario cargar los datos de la estructura stUsuario en el archivo.
 */
void agregarUsuarioArchivo()
{
    FILE *archi = fopen(aUsuarios, "ab");
    stUsuario u;
    agregarUsuario(&u);
    fwrite(&u, sizeof(stUsuario), 1, archi);
    fclose(archi);
}

/** \fn void agregarUsuarioArchivo2(stUsuario u)
 * \brief Abre el archivo al final y carga los datos de la estructura stUsuario en el archivo.
 * \param u estructura stUsuario con datos
 */
void agregarUsuarioArchivo2(stUsuario u)
{
    FILE *archi = fopen(aUsuarios, "ab");
    fwrite(&u, sizeof(stUsuario), 1, archi);
    fclose(archi);
}

/** \fn float extraerConsumoUsuario (int id)
 * \brief Obtiene el valor "u.totalconsumo" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a obtener
 * \return Devuelve el valor obtenido como "float"
 */
float extraerConsumoUsuario(int id)
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "rb");
    if (archi != NULL)
    {
        int encontrado = 0;
        float consumo;
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id)
            {
                consumo = usuario.totalconsumo;
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&usuario, sizeof(stUsuario), 1, archi);
                encontrado = 1;
                break;
            }
        }
        if (!encontrado)
        {
            printf("Usuario no encontrado.\n");
        }
        fclose(archi);
        return consumo;
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}


void agregarConsumoConsumible(stUsuario u, stConsumibles c)
{
    cambiarConsumoUsuario(u.id, c.precio);
}


/** \fn int obtenerUltimoIdUsuario()
 * \brief Accede al archivo, obtine el ultimo id usuario y lo retorna
 * \return Devuelve el ultimo id usuario
 */
int obtenerUltimoIdUsuario()
{
    FILE *archi = fopen(aUsuarios, "rb");
    int ultId = 0;
    stUsuario usuario;

    if (archi == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return -1;
    }

    fseek(archi, -sizeof(stUsuario), SEEK_END); // Posiciona el cursor al final del archivo con el - del size of leo patriky

    if (fread(&usuario, sizeof(stUsuario), 1, archi))
    {
        ultId = usuario.id;
    }

    fclose(archi);
    return ultId;
}

/** \fn int buscarUsuarioDocumento(char documento[])
 * \brief Busca en el archivo un documento enviado por parametro
 * \param documento string que recibe el numero de documento para buscar
 * \return Devuelve el valor de id dentro del archivo de usuarios
 */
int buscarUsuarioDocumento(char documento[])
{
    int idEncontrado = -1;
    FILE *archi = fopen(aUsuarios, "rb");
    stUsuario u;
    while (fread(&u, sizeof(stUsuario), 1, archi))
    {
        if (strcmp(u.DNI, documento) == 0)
        {
            idEncontrado = u.id;
        }
    }

    return idEncontrado;
}

/** \fn int buscarUsuarioCelular(char celular[])
 * \brief Busca en el archivo un documento enviado por parametro
 * \param celular string que recibe el numero de documento para buscar
 * \return Devuelve el valor de id dentro del archivo de usuarios
 */
int buscarUsuarioCelular(char celular[])
{
    int idEncontrado = -1;
    FILE *archi = fopen(aUsuarios, "rb");
    stUsuario u;
    while (fread(&u, sizeof(stUsuario), 1, archi))
    {
        if (strcmp(u.telefono, celular) == 0)
        {
            idEncontrado = u.id;
        }
    }
    return idEncontrado;
}

//-------------------| MODIFICAR USUARIO |-------------------

/** \fn int cambiarConsumoUsuario(int id, float consumo)
 * \brief Modifica el valor "u.totalconsumo" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param consumo este valor puede ser positivo o negativo para modificar el consumo
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra
 */
int cambiarConsumoUsuario(int id, float consumo)
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id)
            {
                usuario.totalconsumo += consumo;
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&usuario, sizeof(stUsuario), 1, archi);
                encontrado = 1;
                break;
            }
        }
        fclose(archi);
        return encontrado;
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}

/** \fn int cambiarContrasenaUsuario(int id, char nuevacontrasena[])
 * \brief Modifica el valor "u.contrasena" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevacontrasena este valor es un string y sera la nueva contraseña
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra
 */
int cambiarContrasenaUsuario(int id, char nuevaContrasena[])
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id)
            {
                system("cls || clear");
                memset(usuario.contrasena, 0, 20);
                strcpy(usuario.contrasena, nuevaContrasena);
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&usuario, sizeof(stUsuario), 1, archi);
                encontrado = 1;
                break;
            }
        }
        fclose(archi);
        return encontrado;
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
        return -1;
    }
}

/** \fn int cambiarNombreUsuario(int id, char nombre[])
 * \brief Modifica el valor "u.nombre" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevoNombre este valor es un string y sera la nueva contraseña
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarNombreUsuario(int id, char nuevoNombre[])
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id)
            {
                memset(usuario.nombre, 0, 50);
                strcpy(usuario.nombre, nuevoNombre);
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&usuario, sizeof(stUsuario), 1, archi);
                return 1;
                break;
            }
        }
        fclose(archi);
        return 0;
    }
    else
    {
        return -1;
    }
}

/** \fn int cambiarApellidoUsuario(int id, char nuevoApellido[])
 * \brief Modifica el valor "u.nombre" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevoNombre este valor es un string y sera la nueva contraseña
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarApellidoUsuario(int id, char nuevoApellido[])
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id)
            {
                memset(usuario.apellido, 0, 50);
                strcpy(usuario.apellido, nuevoApellido);
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&usuario, sizeof(stUsuario), 1, archi);
                return 1;
                break;
            }
        }
        fclose(archi);
        return 0;
    }
    else
    {
        return -1;
    }
}

/** \fn void cambiarBorradoUsuario(int id)
 * \brief Modifica el valor "u.borrado" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 */
void cambiarBorradoUsuario(int id)
{
    stUsuario u;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        while (!feof(archi) && fread(&u, sizeof(stUsuario), 1, archi))
        {
            if (id == u.id)
            {
                switch (u.borrado)
                {
                case 1:
                    u.borrado = 0;
                    break;

                case 0:
                    u.borrado = 1;
                    break;
                }
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&u, sizeof(stUsuario), 1, archi);
                break;
            }
            fclose(archi);
        }
    }
}

/** \fn void agregarUsuario(stUsuario *u)
 * \brief recibe por parametro la estructura usuario, y pide al usuario que ingrese los datos
 * \param c estructura stUsuario
 */
void agregarUsuario(stUsuario *u)
{
    int opcion = 0;
    u->id = obtenerUltimoIdUsuario() + 1;
    printf("Usuario n%cmero = %i\n", 163, u->id);
    printf("Ingrese el nombre del usuario = ");
    fflush(stdin);
    gets(u->nombre);
    printf("\nIngrese apellido del usuario = ");
    fflush(stdin);
    gets(u->apellido);

    printf("\nIngrese documento del usuario = ");
    fflush(stdin);
    gets(u->DNI);
    strcpy(u->contrasena, u->DNI);

    printf("\nIngrese edad del usuario = ");
    fflush(stdin);
    scanf("%i", &u->edad);

    printf("\nIngrese estado civil del usuario = \n");
    printf("0- Soltero\n1- Divorciado\n2- Viudo\n3- Casado");

    fflush(stdin);
    scanf("%i", &opcion);
    switch (opcion)
    {
    case 0: // soltero
        strcpy(u->estadoCivil, "Soltero");
        break;
    case 1: // divorciado
        strcpy(u->estadoCivil, "Divorciado");
        break;
    case 2: // viudo
        strcpy(u->estadoCivil, "Viudo");
        break;
    case 3: // casado
        strcpy(u->estadoCivil, "Casado");
        break;
    default:
        break;
    }

    printf("\nIngrese g%cnero del usuario (m = masculino , f = femenino, o = otros) = ", 130);
    fflush(stdin);
    scanf("%c", &u->genero);

    printf("\nIngrese cantidad de hijos = ");
    fflush(stdin);
    scanf("%i", &u->hijos);

    printf("\nIngrese n%cmero de tel%cfono = ", 163, 130);
    fflush(stdin);
    gets(u->telefono);

    printf("\nIngrese tipo de usuario (huesped: 0, empleado: 1, administrador: 2) = ");
    fflush(stdin);
    scanf("%i", &u->tipo);

    u->totalconsumo = 0;
}

/** \fn int cambiarDNIUsuario(int id, char nuevoDNI[])
 * \brief Modifica el valor "u.DNI" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevoDNI este valor es un string y sera el nuevo DNI
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarDNIUsuario(int id, char nuevoDNI[])
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id)
            {
                memset(usuario.DNI, 0, 10);
                strcpy(usuario.DNI, nuevoDNI);
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&usuario, sizeof(stUsuario), 1, archi);
                return 1;
                break;
            }
        }
        fclose(archi);
        return 0;
    }
    else
    {
        return -1;
    }
}

/** \fn int cambiarEstadoCivilUsuario(int id, char nuevoEstadoCivil[])
 * \brief Modifica el valor "u.estadoCivil" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevoEstadoCivil este valor es un string y sera el nuevo estado civil
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarEstadoCivilUsuario(int id, char nuevoEstadoCivil[])
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id)
            {
                memset(usuario.estadoCivil, 0, 20);
                strcpy(usuario.estadoCivil, nuevoEstadoCivil);
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&usuario, sizeof(stUsuario), 1, archi);
                return 1;
                break;
            }
        }
        fclose(archi);
        return 0;
    }
    else
    {
        return -1;
    }
}

/** \fn int cambiarGeneroUsuario(int id, char nuevoGenero)
 * \brief Modifica el valor "u.genero" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevoGenero este valor es un string y sera el nuevo genero
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarGeneroUsuario(int id, char nuevoGenero)
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id)
            {
                usuario.genero = nuevoGenero;
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&usuario, sizeof(stUsuario), 1, archi);
                return 1;
                break;
            }
        }
        fclose(archi);
        return 0;
    }
    else
    {
        return -1;
    }
}

/** \fn int cambiarTelefonoUsuario(int id, char nuevoTelefono[])
 * \brief Modifica el valor "u.telefono" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevoTelefono este valor es un string y sera el nuevo telefono
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarTelefonoUsuario(int id, char nuevoTelefono[])
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id)
            {
                memset(usuario.telefono, 0, 20);
                strcpy(usuario.telefono, nuevoTelefono);
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&usuario, sizeof(stUsuario), 1, archi);
                return 1;
                break;
            }
        }
        fclose(archi);
        return 0;
    }
    else
    {
        return -1;
    }
}

/** \fn int cambiarHijosUsuario(int id, int nuevaCantHijos)
 * \brief Modifica el valor "u.hijos" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevaCantHijos este valor es un int y sera la nueva cantidad de hijos
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarHijosUsuario(int id, int nuevaCantHijos)
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id)
            {
                usuario.hijos = nuevaCantHijos;
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&usuario, sizeof(stUsuario), 1, archi);
                return 1;
                break;
            }
        }
        fclose(archi);
        return 0;
    }
    else
    {
        return -1;
    }
}

/** \fn int cambiarTipoUsuario(int id, int nuevoTipo)
 * \brief Modifica el valor "u.hijos" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevoTipo este valor es un int y sera el nuevo tipo de usuario
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarTipoUsuario(int id, int nuevoTipo)
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id)
            {
                usuario.tipo = nuevoTipo;
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&usuario, sizeof(stUsuario), 1, archi);
                return 1;
                break;
            }
        }
        fclose(archi);
        return 0;
    }
    else
    {
        return -1;
    }
}

//-----------FUNCION GENERAL
/** \fn int cambiarDatosDeUsuario(int selector, int id)
 * \brief Modifica el dato seleccionado y pide al usuario el nuevo valor
 * \param selector
 * "0" Nombre.
 * "1" Apellido.
 * "2" DNI.
 * "3" Estado civil.
 * "4" Genero.
 * "5" Telefono.
 * "6" Cantidad de hijos.
 * "7" Tipo de usuario.
 * "8" Contraseña.
 * "9" Consumo.
 * \param id valor con el que se accede al usuario
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarDatosDeUsuario(int selector, int id)
{
    char nuevoDatoString[50];
    char nuevoDatoChar;
    int nuevoDatoInt;
    float nuevoDatoFloat;
    switch (selector)
    {
    case 0:
        printf("\nNuevo nombre: ");
        fflush(stdin);
        gets(nuevoDatoString);
        return cambiarNombreUsuario(id, nuevoDatoString);
        break;

    case 1:
        printf("\nNuevo apellido: ");
        fflush(stdin);
        gets(nuevoDatoString);
        return cambiarApellidoUsuario(id, nuevoDatoString);
        break;

    case 2:
        printf("\nNuevo DNI: ");
        fflush(stdin);
        gets(nuevoDatoString);
        return cambiarDNIUsuario(id, nuevoDatoString);
        break;

    case 3:
        printf("\nNuevo estado civil: ");
        fflush(stdin);
        gets(nuevoDatoString);
        return cambiarEstadoCivilUsuario(id, nuevoDatoString);
        break;

    case 4:
        printf("\nNuevo g%cnero: ", 130);
        fflush(stdin);
        scanf("%c", &nuevoDatoChar);
        return cambiarGeneroUsuario(id, nuevoDatoChar);
        break;

    case 5:
        printf("\nNuevo tel%cfono: ", 130);
        fflush(stdin);
        gets(nuevoDatoString);
        return cambiarTelefonoUsuario(id, nuevoDatoString);
        break;

    case 6:
        printf("\nNueva cantidad de hijos: ");
        fflush(stdin);
        scanf("%i", &nuevoDatoInt);
        return cambiarHijosUsuario(id, nuevoDatoInt);
        break;

    case 7:
        printf("\nNuevo tipo de usuario: ");
        fflush(stdin);
        scanf("%i", &nuevoDatoInt);
        return cambiarTipoUsuario(id, nuevoDatoInt);
        break;

    case 8:
        printf("\nNueva contrase%ca: ", 164);
        fflush(stdin);
        gets(nuevoDatoString);
        return cambiarContrasenaUsuario(id, nuevoDatoString);
        break;

    case 9:
        printf("\nConsumo usuario ( + / - ): ");
        fflush(stdin);
        scanf("%f", &nuevoDatoFloat);
        cambiarConsumoUsuario(id, nuevoDatoFloat);
        break;

    case 10:
        cambiarBorradoUsuario(id);
        break;

    default:
        printf("Dato Incorrecto");
        break;
    }
}
//-----------FUNCION GENERAL

//-------------------| MODIFICAR USUARIO |-------------------

/** \fn void mostrarUsuario(stConsumibles c)
 * \brief muestra la estructura stUsuario, recibida por parametro
 * \param u estructura stUsuario con datos
 */
void mostrarUsuario(stUsuario u)
{
    puts("------------------------------------------------");
    printf("     ID              : %i\n", u.id);
    printf("     Nombre          : %s\n", u.nombre);
    printf("     Apellido        : %s\n", u.apellido);
    printf("     Contrase%ca      : %s\n", 164, u.contrasena);
    printf("     Documento       : %s\n", u.DNI);
    printf("     Edad            : %i\n", u.edad);
    printf("     Estado Civil    : %s\n", u.estadoCivil);
    printf("     G%cnero          : %c\n", 130, u.genero);
    printf("     Hijos           : %i\n", u.hijos);
    printf("     Tel%cfono        : %s\n", 130, u.telefono);
    printf("     Tipo            : %i\n", u.tipo);
    printf("     Total Consumo   : %f\n", u.totalconsumo);
    puts("------------------------------------------------");
}

/** \fn void mostrarUsuarios()
 * \brief muestra las estructuras stUsuario, almacenadas en el archivo
 */
void mostrarUsuarios() // muestra todos los tipos
{
    stUsuario aux;
    FILE *archi = fopen(aUsuarios, "rb"); // abrir archivo binario para leer, no lo crea
    if (archi == NULL)                    // si el puntero devuelve NULL es que no se pudo abrir
    {
        printf("No existe el archivo");
    }
    system("clear || cls");
    while (!feof(archi))
    {
        fread(&aux, sizeof(stUsuario), 1, archi);
        if (!feof(archi))
        {
            mostrarUsuario(aux);
        }
    }
    fclose(archi); // cierra el archivo.
    system("PAUSE");
}

/** \fn stUsuario iniciarSesion()
 * \brief Pide al usuario su DNI y contraseña, hasta que estos no sean correctos no corta
 */
stUsuario iniciarSesion()
{
    int flag = 0;
    stUsuario u;
    do
    {
        system("clear || cls");
        printf("Ingrese su documento: ");
        fflush(stdin);
        gets(u.DNI);
        printf("\nIngrese su contrase%ca: ", 164);
        fflush(stdin);
        gets(u.contrasena);
        flag = verificarContrasena(buscarUsuarioDocumento(u.DNI), u.contrasena);
    } while (flag == 0);
    return u;
}

/** \fn int obtenerTipoUsuario(int id)
 * \brief Accede al archivo y compara el id enviado y devuelve el tipo de usuario
 * \param id valor con el que se busca al usuario a modificar
 * \return Devuelve 0 si es huesped, 1 empleado, 2 administrador, -1 erronea.
 */
int obtenerTipoUsuario(int id)
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "rb");
    int tipo;
    if (archi != NULL)
    {
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id)
            {
                tipo = usuario.tipo;
                break;
            }
        }
        fclose(archi);
        return tipo;
    }
    else
    {
        return -1; // No se pudo abrir el archivo.
    }
}

/** \fn float extraerUsuario (int id)
 * \brief Obtiene una estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a obtener
 * \return Devuelve la estructura de usuario
 */
stUsuario extraerUsuario(int id)
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "rb");
    if (archi != NULL)
    {
        int encontrado = 0;
        float consumo;
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id)
            {
                return usuario;
                break;
            }
        }
        if (!encontrado)
        {
            printf("Usuario no encontrado.\n");
        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}

Pila buscarUsuarioTipo(int tipo)
{
    Pila ids;
    inicpila(&ids);
    FILE *archi = fopen(aUsuarios, "rb");
    stUsuario u;
    while (fread(&u, sizeof(stUsuario), 1, archi))
    {
        if (u.tipo == tipo)
        {
            apilar(&ids, u.id);
        }
    }
    return ids;
}

void mostrarUsuariosTipo(Pila p)
{
    while (!pilavacia(&p))
    {
        mostrarUsuario(extraerUsuario(tope(&p)));
        desapilar(&p);
    }
}

/** \fn int verificarContrasena(int id, char contrasena[])
 * \brief Accede al archivo y compara la contraseña enviada con la almacenada.
 * \param id valor con el que se busca al usuario a modificar
 * \param contrasena contraseña escrita por el usuario
 * \return Devuelve 1 si son iguales, 0 erronea
 */
int verificarContrasena(int id, char contrasena[])
{
    stUsuario usuario;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&usuario, sizeof(stUsuario), 1, archi))
        {
            if (id == usuario.id && strcmp(contrasena, usuario.contrasena) == 0)
            {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado)
        {
            printf("Usuario no encontrado.\n");
        }
        fclose(archi);
        return encontrado;
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}

/** \fn int borrarUsuario(int id)
 * \brief Accede al archivo y elimina los valores del usuario selecionado por id (id no se borra).
 * \param id valor con el que se busca al usuario a modificar
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra
 */
int borrarUsuario(int id)
{
    stUsuario u;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&u, sizeof(stUsuario), 1, archi))
        {
            if (id == u.id)
            {
                borraDatosUsuario(&u);
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&u, sizeof(stUsuario), 1, archi);
                encontrado = 1;
                break;
            }
        }
        fclose(archi);
        return encontrado;
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}

/** \fn borraDatosUsuario(stUsuario *u)
 * \brief Recibe una estructura y coloca sus valores en 0, menos el id
 * \param *u estructura usuario
 */
void borraDatosUsuario(stUsuario *u)
{
    if (u->totalconsumo == 0)
    {
        memset(u->tipo, 0, 0);
        memset(u->nombre, 0, 50);
        memset(u->apellido, 0, 50);
        memset(u->DNI, 0, 10);
        memset(u->contrasena, 0, 20);
        memset(u->edad, 0, 0);
        memset(u->telefono, 0, 20);
        memset(u->genero, 0, 0);
        memset(u->hijos, 0, 0);
        memset(u->estadoCivil, 0, 20);
    }
    else
    {
        printf("El saldo debe ser 0\n");
    }
}

void mostrarReserva(stUsuario u)
{
    puts("------------------------------------------------");
    printf(" ID: %i | Nombre: %s | Apellido: %s | DNI: %s\n", u.id, u.nombre, u.apellido, u.DNI);
    printf(" D%ca de Entrada     : %i\n", 161, u.reserva.diaEntrada);
    printf(" Mes de Entrada     : %i\n", u.reserva.mesEntrada);
    printf(" A%co de Entrada     : %i\n", 164, u.reserva.anioEntrada);
    printf(" D%ca de Salida      : %i\n", 161, u.reserva.diaSalida);
    printf(" Mes de Sal%cda      : %i\n", 161, u.reserva.mesSalida);
    printf(" A%co de Salida      : %i\n", 164, u.reserva.anioSalida);
    printf(" Tipo de Habitaci%cn : %s\n", 162, u.reserva.habitacion.tipo);
    puts("------------------------------------------------");
}

void mostrarReservaEnArchivo() // muestra todos los tipos
{
    stUsuario aux;
    stReserva vacio;
    FILE *archi = fopen(aUsuarios, "rb"); // abrir archivo binario para leer, no lo crea
    if (archi == NULL)                    // si el puntero devuelve NULL es que no se pudo abrir
    {
        printf("No existe el archivo");
    }
    else
    {
        system("clear || cls");
        while (!feof(archi))
        {
            fread(&aux, sizeof(stUsuario), 1, archi);
            if (!feof(archi) && (strcmp(aux.reserva.habitacion.tipo, vacio.habitacion.tipo) > 0))
            {
                mostrarReserva(aux);
                Sleep(500);
            }
        }
        fclose(archi); // cierra el archivo.
    }
}

/** \fn int crearReserva(int id)
 * \brief Agrega al archivo de usuario los datos de la reserva
 * \param documento dato con el que se busca al usuario
 * \return -1 No se pudo abrir el archivo.
 * \return 0 Reserva creada.
 */
int crearReserva(int id)
{
    stReserva r;

    int opcion = 0;
    system("clear || cls");
    printf("Cual es el tipo de habitacion?\n");
    printf("0 - Basica\n1 - Deluxe\n2 - Suite\n3 - Suite Premium\n");
    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%i", &opcion);
    switch (opcion)
    {
    case 0:
        strcpy(r.habitacion.tipo, "Basica");
        break;
    case 1:
        strcpy(r.habitacion.tipo, "Deluxe");
        break;
    case 2:
        strcpy(r.habitacion.tipo, "Suite");
        break;
    case 3:
        strcpy(r.habitacion.tipo, "Suite premium");
        break;
    }

    do
    {
        printf("\nDia de entrada: ");
        fflush(stdin);
        scanf("%i", &r.diaEntrada);

        printf("\nMes de entrada: ");
        fflush(stdin);
        scanf("%i", &r.mesEntrada);

        printf("\nA%co de entrada: ", 164);
        fflush(stdin);
        scanf("%i", &r.anioEntrada);

    } while (esFechaPosterior(r.diaEntrada, r.mesEntrada, r.anioEntrada) != 0);

    do
    {
        printf("\nD%ca de salida: ", 161);
        fflush(stdin);
        scanf("%i", &r.diaSalida);

        printf("\nMes de salida: ");
        fflush(stdin);
        scanf("%i", &r.mesSalida);

        printf("\nA%co de salida: ", 164);
        fflush(stdin);
        scanf("%i", &r.anioSalida);
    } while (esFechaPosteriorA(r.diaEntrada, r.mesEntrada, r.anioEntrada, r.diaSalida, r.mesSalida, r.anioSalida) != 0);

    FILE *archi = fopen(aUsuarios, "r+b");
    stUsuario uArchivo;
    if (archi != NULL)
    {
        while (!feof(archi) && fread(&uArchivo, sizeof(stUsuario), 1, archi))
        {
            if (id == uArchivo.id)
            {
                uArchivo.reserva = r;
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&uArchivo, sizeof(stUsuario), 1, archi);
                break;
            }
        }
        fclose(archi);
        return 0; // se agrego la reserva
    }
    else
    {
        return -1; // No se pudo abrir el archivo.
    }
}

/** \fn int borrarReserva(char documento[])
 * \brief Agrega al archivo de usuario los datos de la reserva
 * \param documento dato con el que se busca al usuario
 * \return -1 No se pudo abrir el archivo.
 * \return 0 Reserva Borrada.
 */
int borrarReserva(char documento[])
{
    stUsuario u;

    int id = buscarUsuarioDocumento(documento);

    int opcion = 0;

    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        while (!feof(archi) && fread(&u, sizeof(stUsuario), 1, archi))
        {
            if (id == u.id)
            {
                borraDatosReserva(&u.reserva);
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&u, sizeof(stUsuario), 1, archi);
                break;
            }
        }
        fclose(archi);
        return 0; // se agrego la reserva
    }
    else
    {
        return -1; // No se pudo abrir el archivo.
    }
}

/** \fn void cambiarBorradoReserva(int id)
 * \brief Modifica el valor "u.reserva.borrado" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 */
void cambiarBorradoReserva(int id)
{
    stUsuario u;
    FILE *archi = fopen(aUsuarios, "r+b");
    if (archi != NULL)
    {
        while (!feof(archi) && fread(&u, sizeof(stUsuario), 1, archi))
        {
            if (id == u.id)
            {
                switch (u.reserva.borrado)
                {
                case 1:
                    u.reserva.borrado = 0;
                    break;

                case 0:
                    u.reserva.borrado = 1;
                    break;
                }
                fseek(archi, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&u, sizeof(stUsuario), 1, archi);
                break;
            }
            fclose(archi);
        }
    }
}
