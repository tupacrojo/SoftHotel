#include "consumible.h"
#include "../config/files.h"

void pasarDeArchivoArregloPalabras(char array[][50])
{
    stConsumibles c;
    int contador = 0;
    FILE *archi = fopen(aConsumibles, "rb");
    if (archi != NULL)
    {
        while (!feof(archi))
        {
            fread(&c, sizeof(stConsumibles), 1, archi);
            strcpy(array[contador], c.nombre);
            contador++;
        }
        fclose(archi);
    }
}

/** \fn int obtenerUltimoIdConsumibles()
 * \brief Accede al archivo, obtine el ultimo id consumible y lo retorna
 * \return Devuelve el ultimo id consumible
 */
int obtenerUltimoIdConsumibles()
{
    FILE *archi = fopen(aConsumibles, "rb");
    int ultId = 0;
    stConsumibles consumible;

    if (archi == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return -1;
    }

    fseek(archi, -sizeof(stConsumibles), SEEK_END); // Posiciona el cursor al final del archivo con el - del size of leo patriky

    if (fread(&consumible, sizeof(stConsumibles), 1, archi))
    {
        ultId = consumible.id;
    }

    fclose(archi);
    return ultId;
}

/** \fn void agregarConsumible(stConsumibles *c)
 * \brief recibe por parametro la estructura consumibles, y pide al usuario que ingrese los datos
 * \param c estructura stConsumibles
 */
void agregarConsumible(stConsumibles *c)
{
    c->id = obtenerUltimoIdConsumibles() + 1;
    printf("Consumible n%cmero = %i\n", 163, c->id);
    int opcion = 0;
    printf("\nCu%cl es la categor%ca del producto?\n ", 160, 161);
    printf("0- Bebible\n1- Comestible\n2- ??\n3- Otros");
    fflush(stdin);
    scanf("%i", &opcion);
    switch (opcion)
    {
    case 0:
        strcpy(c->categoria, "Bebible");
        break;
    case 1:
        strcpy(c->categoria, "Comestible");
        break;
    case 2:
        strcpy(c->categoria, "??");
        break;
    case 3:
        strcpy(c->categoria, "Otros");
        break;
    }
    printf("\nNombre del producto: ");
    fflush(stdin);
    gets(c->nombre);
    c->borrado = 0;

    printf("\nPrecio: ");
    fflush(stdin);
    scanf("%f", &c->precio);
}

/** \fn stConsumibles agregarConsumiblePorParametro(int id, char nombre[], char categoria[], float precio)
 * \brief recibe por parametro los datos de la estructura stConsumibles
 * \param id id
 * \param nombre nombre de consumible
 * \param categoria "Bebible, Comestible, Otros"
 * \param precio precio de consumible
 * \return devuelvo una estructura stConsumibles con los datos cargados.
 */
stConsumibles agregarConsumiblePorParametro(int id, int borrado, char nombre[], char categoria[], float precio)
{

    stConsumibles c;
    c.id = id;
    c.borrado = borrado;
    strcpy(c.nombre, nombre);
    strcpy(c.categoria, categoria);
    c.precio = precio;

    return c;
}

/** \fn void agregarConsumibleArchivo()
 * \brief Abre el archivo al final y pide al usuario cargar los datos de la estructura stConsumibles en el archivo.
 */
void agregarConsumibleArchivo()
{
    FILE *archi = fopen(aConsumibles, "ab");
    stConsumibles c;
    agregarConsumible(&c);
    fwrite(&c, sizeof(stConsumibles), 1, archi);
    fclose(archi);
}

/** \fn void agregarConsumibleArchivo2()
 * \brief Abre el archivo al final y carga los datos de la estructura stConsumibles en el archivo.
 * \param c estructura stConsumible con datos
 */
void agregarConsumibleArchivo2(stConsumibles c)
{
    FILE *archi = fopen(aConsumibles, "ab");
    fwrite(&c, sizeof(stConsumibles), 1, archi);
    fclose(archi);
}

/** \fn void mostrarConsumible(stConsumibles c)
 * \brief muestra la estructura stConsumibles, recibida por parametro
 * \param c estructura stConsumible con datos
 */
void mostrarConsumible(stConsumibles c)
{
    puts("------------------------------------------------");
    printf("     ID          : %i\n", c.id);
    printf("     Nombre      : %s\n", c.nombre);
    printf("     Borrado     : %i\n", c.borrado);
    printf("     Categor%ca   : %s\n", 161, c.categoria);
    printf("     Precio      : %f\n", c.precio);
    puts("------------------------------------------------");
}

/** \fn void mostrarConsumibles()
 * \brief muestra las estructuras stConsumibles, almacenadas en el archivo
 */
void mostrarConsumibles()
{
    stConsumibles aux;
    FILE *archi = fopen(aConsumibles, "rb"); // abrir archivo binario para leer, no lo crea
    if (archi == NULL)                       // si el puntero devuelve NULL es que no se pudo abrir
    {
        printf("No existe el archivo");
    }
    while (!feof(archi))
    {
        fread(&aux, sizeof(stConsumibles), 1, archi);
        if (!feof(archi))
        {
            mostrarConsumible(aux);
        }
    }
    fclose(archi); // cierra el archivo.
}

/** \fn int borrarConsumbible(int id)
 * \brief Accede al archivo y elimina los valores del consumible selecionado por id (id no se borra).
 * \param id valor con el que se busca el consumible a modificar
 * \return Devuelve 0 si el valor fue modificado correctamente, -1 si no se encuentra
 */
int borrarConsumbible(int id)
{
    stConsumibles c;
    FILE *archi = fopen(aConsumibles, "r+b");
    if (archi != NULL)
    {
        while (!feof(archi) && fread(&c, sizeof(stConsumibles), 1, archi))
        {
            if (id == c.id)
            {
                borraDatosConsumible(&c);
                fseek(archi, -sizeof(stConsumibles), SEEK_CUR);
                fwrite(&c, sizeof(stConsumibles), 1, archi);
                break;
            }
        }
        fclose(archi);
        return 0; // borrado
    }
    else
    {
        return -1; // No se pudo abrir el archivo.
    }
}

/** \fn void borraDatosConsumible(stConsumibles *c)
 * \brief Recibe una estructura y coloca sus valores en 0, menos el id
 * \param *c estructura consumible
 */
void borraDatosConsumible(stConsumibles *c)
{
    memset(c->nombre, 0, 50);
    c->borrado = 0;
    c->precio = 0;
    memset(c->categoria, 0, 50);
}

/** \fn Pila buscarConsumiblePorCategoria(char categoria[])
 * \brief Accede al archivo, lo lee y compara si la categoria es igual a la ingresada, en caso de ser asi lo copia en la pila, y lo devuelve
 * \param categoria "Bebible, Consumible, Otros"
 * \return Devuelve la pila cargada de ids
 */
Pila buscarConsumiblePorCategoria(char categoria[])
{
    Pila ids;
    inicpila(&ids);
    FILE *archi = fopen(aConsumibles, "rb");
    stConsumibles c;
    while (fread(&c, sizeof(stConsumibles), 1, archi))
    {
        if (strcmp(c.categoria, categoria) == 0)
        {
            apilar(&ids, c.id);
        }
    }
    return ids;
}

//-------------------| MODIFICAR CONSUMIBLE |-------------------

/** \fn void cambiarBorradoConsumible(int id)
 * \brief Modifica el valor "c.borrado" de la estructura consumible almacenada en el archivo
 * \param id valor con el que se busca al consumible a modificar
 */
void cambiarBorradoConsumible(int id)
{
    stConsumibles c;
    FILE *archi = fopen(aConsumibles, "r+b");
    if (archi != NULL)
    {
        while (!feof(archi) && fread(&c, sizeof(stConsumibles), 1, archi))
        {
            if (id == c.id)
            {
                switch (c.borrado)
                {
                case 1:
                    c.borrado = 0;
                    break;

                case 0:
                    c.borrado = 1;
                    break;
                }
                fseek(archi, -sizeof(stConsumibles), SEEK_CUR);
                fwrite(&c, sizeof(stConsumibles), 1, archi);
                break;
            }
            fclose(archi);
        }
    }
}

/** \fn int cambiarNombreConsumible(int id, char nuevoNombre[])
 * \brief Modifica el valor "u.contrasena" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevoNombre este valor es un string y sera el nuevo nombre
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarNombreConsumible(int id, char nuevoNombre[])
{
    stConsumibles consumible;
    FILE *archi = fopen(aConsumibles, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&consumible, sizeof(stConsumibles), 1, archi))
        {
            if (id == consumible.id)
            {
                memset(consumible.nombre, 0, 50);
                strcpy(consumible.nombre, nuevoNombre);
                fseek(archi, -sizeof(stConsumibles), SEEK_CUR);
                fwrite(&consumible, sizeof(stConsumibles), 1, archi);
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

/** \fn int cambiarCategoriaConsumible(int id, char nuevaCategoria[])
 * \brief Modifica el valor "c.categoria" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevaCategoria este valor es un string y sera la nueva categoria
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarCategoriaConsumible(int id, char nuevaCategoria[])
{
    stConsumibles consumible;
    FILE *archi = fopen(aConsumibles, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&consumible, sizeof(stConsumibles), 1, archi))
        {
            if (id == consumible.id)
            {
                memset(consumible.categoria, 0, 50);
                strcpy(consumible.categoria, nuevaCategoria);
                fseek(archi, -sizeof(stConsumibles), SEEK_CUR);
                fwrite(&consumible, sizeof(stConsumibles), 1, archi);
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

/** \fn int cambiarPrecioConsumible(int id, float nuevoPrecio)
 * \brief Modifica el valor "c.precio" de la estructura usuario almacenada en el archivo
 * \param id valor con el que se busca al usuario a modificar
 * \param nuevoPrecio este valor es un float y sera el nuevo precio
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarPrecioConsumible(int id, float nuevoPrecio)
{
    stConsumibles c;
    FILE *archi = fopen(aConsumibles, "r+b");
    if (archi != NULL)
    {
        int encontrado = 0;
        while (!feof(archi) && fread(&c, sizeof(stConsumibles), 1, archi))
        {
            if (id == c.id)
            {
                c.precio = nuevoPrecio;
                fseek(archi, -sizeof(stConsumibles), SEEK_CUR);
                fwrite(&c, sizeof(stConsumibles), 1, archi);
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

stConsumibles extraerConsumible(int id)
{
    stConsumibles c;
    FILE *archi = fopen(aConsumibles, "rb");
    if (archi != NULL)
    {
         while (!feof(archi) && fread(&c, sizeof(stConsumibles), 1, archi))
        {
            if (id == c.id)
            {
                return c;
                break;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}

//-----------FUNCION GENERAL
/** \fn int cambiarDatosDeConsumible(int selector, int id)
 * \brief Modifica el dato seleccionado y pide al usuario el nuevo valor
 * \param selector
 * "0" Nombre.
 * "1" Categoria.
 * "2" Precio.
 * \param id valor con el que se accede al usuario
 * \return Devuelve 1 si el valor fue modificado correctamente, 0 si no se encuentra, -1 no se puede abrir el archivo.
 */
int cambiarDatosDeConsumible(int selector, int id)
{
    char nuevoDatoString[50];
    float nuevoDatoFloat;
    switch (selector)
    {
    case 0:
        printf("\nNuevo nombre: ");
        gets(nuevoDatoString);
        return cambiarNombreConsumible(id, nuevoDatoString);
        break;

    case 1:
        printf("\nNueva categoria: ");
        gets(nuevoDatoString);
        return cambiarCategoriaConsumible(id, nuevoDatoString);
        break;

    case 2:
        printf("\nNuevo precio: ");
        scanf("%f", &nuevoDatoFloat);
        return cambiarPrecioConsumible(id, nuevoDatoFloat);
        break;
    case 3:
        cambiarBorradoConsumible(id);
        break;

    default:
        break;
    }
}
//-----------FUNCION GENERAL

//-------------------| MODIFICAR CONSUMIBLE |-------------------
