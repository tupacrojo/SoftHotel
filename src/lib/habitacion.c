#include "habitacion.h"
#include "../config/files.h"

/** \fn int obtenerUltimoIdHabitaciones()
 * \brief Accede al archivo, obtine el ultimo id habitacion y lo retorna
 * \return Devuelve el ultimo id habitacion
 */
int obtenerUltimoIdHabitaciones()
{
    FILE *archi = fopen(aHabitaciones, "rb");
    int ultId = 0;
    stHabitacion habitacion;

    if (archi == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return -1;
    }

    fseek(archi, -sizeof(stHabitacion), SEEK_END); // Posiciona el cursor al final del archivo con el - del size of leo patriky

    if (fread(&habitacion, sizeof(stHabitacion), 1, archi))
    {
        ultId = habitacion.id;
    }

    fclose(archi);
    return ultId;
}

/** \fn Pila buscarHabitacionTipo(char tipo[])
 * \brief Accede al archivo, lo lee y compara si el tipo es igual al ingresado, en caso de ser asi lo copia en la pila, y lo devuelve
 * \param tipo "Basica, Deluxe, Suite, Suite Premium"
 * \return Devuelve la pila cargada de ids
 */
Pila buscarHabitacionTipo(char tipo[])
{
    Pila ids;
    inicpila(&ids);
    FILE *archi = fopen(aHabitaciones, "rb");
    stHabitacion a;
    while (fread(&a, sizeof(stHabitacion), 1, archi))
    {
        if (strcmp(a.tipo, tipo) == 0)
        {
            apilar(&ids, a.id);
        }
    }
    return ids;
}

stHabitacion extraerHabitacion(int id)
{
    stHabitacion a;
    FILE *archi = fopen(aHabitaciones, "rb");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&a, sizeof(stHabitacion), 1, archi))
        {
            if (id == a.id)
            {
                return a;
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

void mostrarHabitacionTipo(Pila p)
{
    if(!pilavacia)
    {
        mostrarHabitacion(extraerHabitacion(tope(&p)));
        desapilar(&p);
    }
}

/** \fn void agregarHabitacion(stUsuario *a)
 * \brief recibe por parametro la estructura habitacion, y pide al usuario que ingrese los datos
 * \param a estructura stHabitacion
 */
void agregarHabitacion(stHabitacion *a)
{
    int opcion = 0;
    a->id = obtenerUltimoIdHabitaciones() + 1;
    a->estado = 0;
    printf("\nEn que piso esta la habitacion? ");
    fflush(stdin);
    scanf("%i", &a->piso);

    opcion = 0;
    printf("\nCual es el tipo de habitacion? ");
    printf("0- Basica\n1- Deluxe\n2- Suite\n3- Suite Premium");
    scanf("%i", &opcion);
    switch (opcion)
    {
    case 0:
        strcpy(a->tipo, "Basica");
        break;
    case 1:
        strcpy(a->tipo, "Deluxe");
        break;
    case 2:
        strcpy(a->tipo, "Suite");
        break;
    case 3:
        strcpy(a->tipo, "Suite premium");
        break;
    }
    system("clear || cls");
    printf("Agregado exitosamente\n");
}

/** \fn void agregarHabitacionArchivo()
 * \brief Abre el archivo al final y pide al usuario cargar los datos de la estructura stHabitacion en el archivo.
 */
void agregarHabitacionArchivo()
{
    FILE *archi = fopen(aHabitaciones, "ab");
    stHabitacion a;
    agregarHabitacion(&a);
    fwrite(&a, sizeof(stHabitacion), 1, archi);
    fclose(archi);
}

/** \fn void agregarHabitacionArchivo2(stUsuario a)
 * \brief Abre el archivo al final y carga los datos de la estructura stHabitacion en el archivo.
 * \param a estructura stUsuario con datos
 */
void agregarHabitacionArchivo2(stHabitacion a)
{
    FILE *archi = fopen(aHabitaciones, "ab");
    fwrite(&a, sizeof(stHabitacion), 1, archi);
    fclose(archi);
}

/** \fn stHabitacion agregarHabitacionPorParametro(int id, int piso, int tipo)
 * \brief recibe por parametro los datos de la estructura stHabitacion
 * \param id id
 * \param piso  numero del piso
 * \param tipo "0 Basica, 1 Deluxe, 2 Suite, 3 Suite Premium"
 * \return Devuelvo una estructura stHabitacion con los datos cargados.
 */
stHabitacion agregarHabitacionPorParametro(int id, int piso, int tipo)
{
    stHabitacion a;
    a.id = id;
    a.borrado = 0;
    a.estado = 0;
    a.piso = piso;
    switch (tipo)
    {
    case 0:
        strcpy(a.tipo, "Basica");
        break;
    case 1:
        strcpy(a.tipo, "Deluxe");
        break;
    case 2:
        strcpy(a.tipo, "Suite");
        break;
    case 3:
        strcpy(a.tipo, "Suite premium");
        break;
    default:
        strcpy(a.tipo, "Basica");
        break;
    }
    return a;
}

/** \fn int borrarHabitacion(int id)
 * \brief Accede al archivo y elimina los valores de la habitacion selecionado por id (id no se borra).
 * \param id valor con el que se busca la habitacion a modificar
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se pudo abrir el archivo
 */
int borrarHabitacion(int id)
{
    stHabitacion a;
    FILE *archi = fopen(aHabitaciones, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&a, sizeof(stHabitacion), 1, archi))
        {
            if (id == a.id)
            {
                borraDatosHabitacion(&a);
                fseek(archi, -sizeof(stHabitacion), SEEK_CUR);
                fwrite(&a, sizeof(stHabitacion), 1, archi);
                encontrado = 1;
                break;
            }
        }
        fclose(archi);
        return encontrado;
    }
    else
    {
        return -1;
    }
}

/** \fn void borraDatosHabitacion(stHabitacion *a)
 * \brief Recibe una estructura y coloca sus valores en 0, menos el id
 * \param *a estructura Habitacion
 */
void borraDatosHabitacion(stHabitacion *a)
{
    a->estado = 0;
    a->piso = 0;
    memset(a->tipo, 0, 50);
}

/** \fn void mostrarHabitacion(stHabitacion a)
 * \brief muestra la estructura stHabitacion, recibida por parametro
 * \param a estructura stHabitacion con datos
 */
void mostrarHabitacion(stHabitacion a)
{
    puts("------------------------------------------------");
    printf("     ID          : %i\n", a.id);
    printf("     Estado      : %i\n", a.estado);
    printf("     Piso        : %i\n", a.piso);
    printf("     Tipo        : %s\n", a.tipo);
    puts("------------------------------------------------");
}

/** \fn void mostrarHabitacion()
 * \brief muestra las estructuras stHabitacion, almacenadas en el archivo
 */
void mostrarHabitaciones()
{
    stHabitacion aux;
    FILE *archi = fopen(aHabitaciones, "rb"); // abrir archivo binario para leer, no lo crea
    if (archi == NULL)                        // si el puntero devuelve NULL es que no se pudo abrir
    {
        printf("no existe el archivo");
    }
    while (!feof(archi))
    {
        fread(&aux, sizeof(stHabitacion), 1, archi);
        if (!feof(archi))
        {
            mostrarHabitacion(aux);
        }
    }
    fclose(archi); // cierra el archivo.
}

//-------------------| MODIFICAR Habitacion |-------------------

void cambiarBorradoHabitacion(int id)
{
    stHabitacion a;
    FILE *archi = fopen(aHabitaciones, "r+b");
    if(archi != NULL)
    {
        while(!feof(archi) && fread(&a,sizeof(stHabitacion),1,archi))
        {
            if(id == a.id)
            {
             switch (a.borrado)
                {
                case 1:
                    a.borrado = 0;
                    break;

                case 0:
                    a.borrado = 1;
                    break;
                }
                fseek(archi, -sizeof(stHabitacion), SEEK_CUR);
                fwrite(&a, sizeof(stHabitacion), 1, archi);
                break;
            }
            fclose(archi);
        }
    }
}

/** \fn int cambiarTipoHabitacion(int id, char nuevoTipo[])
 * \brief Modifica el valor "u.tipo" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevoTipo nuevo tipo de habitacion  "Basica, Deluxe, Suite, Suite Premium"
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarTipoHabitacion(int id, char nuevoTipo[])
{
    stHabitacion habitacion;
    FILE *archi = fopen(aHabitaciones, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&habitacion, sizeof(stHabitacion), 1, archi))
        {
            if (id == habitacion.id)
            {
                strcpy(habitacion.tipo, nuevoTipo);
                fseek(archi, -sizeof(stHabitacion), SEEK_CUR);
                fwrite(&habitacion, sizeof(stHabitacion), 1, archi);
                encontrado = 1;
                break;
            }
        }
        fclose(archi);
        return encontrado;
    }
    else
    {
        return -1;
    }
}

/** \fn int cambiarEstadoHabitacion(int id, int nuevoEstado)
 * \brief Modifica el valor "a.estado" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevoEstado estado 0 libre; 1 Ocupado;
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarEstadoHabitacion(int id, int nuevoEstado)
{
    stHabitacion habitacion;
    FILE *archi = fopen(aHabitaciones, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&habitacion, sizeof(stHabitacion), 1, archi))
        {
            if (id == habitacion.id)
            {
                habitacion.estado = nuevoEstado;
                fseek(archi, -sizeof(stHabitacion), SEEK_CUR);
                fwrite(&habitacion, sizeof(stHabitacion), 1, archi);
                encontrado = 1;
                break;
            }
        }
        fclose(archi);
        return encontrado;
    }
    else
    {
        return -1;
    }
}

/** \fn int cambiarEstadoHabitacion(int id, int nuevoPiso)
 * \brief Modifica el valor "a.piso" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevoPiso int del piso
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarPisoHabitacion(int id, int nuevoPiso)
{
    stHabitacion habitacion;
    FILE *archi = fopen(aHabitaciones, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&habitacion, sizeof(stHabitacion), 1, archi))
        {
            if (id == habitacion.id)
            {
                habitacion.piso = nuevoPiso;
                fseek(archi, -sizeof(stHabitacion), SEEK_CUR);
                fwrite(&habitacion, sizeof(stHabitacion), 1, archi);
                encontrado = 1;
                break;
            }
        }
        fclose(archi);
        return encontrado;
    }
    else
    {
        return -1;
    }
}

//-----------FUNCION GENERAL
/** \fn int cambiarDatosDeHabitacion(int selector, int id)
 * \brief Modifica el dato seleccionado y pide al usuario el nuevo valor
 * \param selector
 * "0" Tipo.
 * "1" Estado.
 * "2" Piso.
 * \param id valor con el que se accede al usuario
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarDatosDeHabitacion(int selector, int id)
{
    char nuevoDatoString[50];
    int nuevoDatoInt;
    switch (selector)
    {
    case 0:
        printf("\nNuevo tipo: ");
        fflush(stdin);
        gets(nuevoDatoString);
        return cambiarTipoHabitacion(id, nuevoDatoString);
        break;

    case 1:
        printf("\nNuevo estado: ");
        fflush(stdin);
        scanf("%i", &nuevoDatoInt);
        return cambiarEstadoHabitacion(id, nuevoDatoInt);
        break;

    case 2:
        printf("\nNuevo piso: ");
        fflush(stdin);
        scanf("%i", &nuevoDatoInt);
        return cambiarPisoHabitacion(id, nuevoDatoInt);
        break;

    case 3:
        cambiarBorradoHabitacion(id);
    break;

    default:
        break;
    }
}
//-----------FUNCION GENERAL

//-------------------| MODIFICAR Habitacion |-------------------
