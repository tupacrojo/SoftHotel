#include "utils.h"
#define maxL 100

// busco el menor en el arreglo funcion auxiliar
int posicionMenor(char palabra1[][maxL], int pos, int validosF)
{
    int posmenor = pos;
    char palabraMenor[maxL];
    strcpy(palabraMenor, palabra1[pos]);
    int i;
    for (i = pos + 1; i < validosF; i++)
    {
        if (strcmpi(palabraMenor, palabra1[i]) > 0)
        {
            strcpy(palabraMenor, palabra1);
            posmenor = i;
        }
    }
    return posmenor;
}

void intercambioDePalabra(char palabra1[][maxL], int posMen, int indF)
{
    char aux[maxL]; // arreglo que sirve para el intercambio
    strcpy(aux, palabra1[posMen]);
    strcpy(palabra1[posMen], palabra1[indF]);
    strcpy(palabra1[indF], aux);
}

void ordenandoPorSeleccion(char palabra1[][maxL], int validosF)
{
    int posMen;
    int indF;

    for (indF = 0; indF < validosF - 1; indF++)
    {
        posMen = posicionMenor(palabra1, indF, validosF);
        intercambioDePalabra(palabra1, posMen, indF);
    }
}

stUtils crearMatrizConsumibles()
{
    stUtils ut;
    stConsumibles c;
    int i = 0, j = 0, contador = 0;
    FILE *archi = fopen(aConsumibles, "rb");
    if (archi != NULL)
    {
        while (!feof(archi))
        {
            fread(&c, sizeof(stConsumibles), 1, archi);
            ut.idPrecio[i][j] = (float)c.id;
            i++;
            ut.idPrecio[i][j] = c.precio;
            i = 0;
            j++;
            contador++;
        }
        ut.cantidad = contador - 1;
        fclose(archi);
        return ut;
    }
}

stUtils crearArregloDePalabraConsumibles()
{
    stUtils ut;
    stConsumibles c;
    int i = 0;
    FILE *archi = fopen(aConsumibles, "rb");
    if (archi != NULL)
    {
        while (!feof(archi))
        {
            fread(&c, sizeof(stConsumibles), 1, archi);
            strcpy(ut.arrayCategoria[i], c.categoria);
            strcpy(ut.arrayNombre[i], c.nombre);
            ut.arrayID[i] = c.id;
            i++;
        }
        ut.cantidad = i - 1;
        fclose(archi);
        return ut;
    }
}

void ordenarPorInsercionMatriz(float matriz[][100], int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 1; j < columnas; j++)
        {
            float valorActual = matriz[i][j];
            int k = j - 1;
            while (k >= 0 && matriz[i][k] > valorActual)
            {
                matriz[i][k + 1] = matriz[i][k];
                k--;
            }
            matriz[i][k + 1] = valorActual;
        }
    }
}

void ordenarPorInsercionMatrizFilaFija(float matriz[][100], int fila, int columnas)
{
    for (int j = 1; j < columnas; j++)
    {
        float valorActual = matriz[fila][j];
        float valorActualId = matriz[fila - 1][j];
        int k = j - 1;

        while (k >= 0 && matriz[fila][k] > valorActual)
        {

            matriz[fila - 1][k + 1] = matriz[fila - 1][k];
            matriz[fila][k + 1] = matriz[fila][k];
            k--;
        }
        matriz[fila - 1][k + 1] = valorActualId;
        matriz[fila][k + 1] = valorActual;
    }
}

void imprimirMatrizConNombres(float matriz[][100], int columnas)
{
    stConsumibles c;
    int i = 0;
    int j = 0;
    while (j < columnas)
    {
        c = extraerConsumible(matriz[i][j]);
        printf("%.f  %.2f  %s \n", matriz[i][j], matriz[i + 1][j], c.nombre);
        j++;
    }
}

void imprimirMatriz(float matriz[][100], int columnas)
{
    int i = 0;
    int j = 0;
    while (j < columnas)
    {
        printf("%.f  %.2f \n", matriz[i][j], matriz[i + 1][j]);
        j++;
    }
}

void mostrarUtilsPar(stUtils ut)
{
    for (int i = 0; i < ut.cantidad; i++)
    {
        printf("ID : %i\n", ut.arrayID[i]);
        puts(ut.arrayCategoria[i]);
        puts(ut.arrayNombre[i]);
    }
}

void ordenarPorInsercionUsuario(stUsuario usuarios[], int totalUsuarios)
{
    int i, j;
    stUsuario temp;

    for (i = 1; i < totalUsuarios; i++)
    {
        temp = usuarios[i];
        j = i - 1;

        // Comparar los nombres y realizar el desplazamiento
        while (j >= 0 && strcmp(usuarios[j].nombre, temp.nombre) > 0)
        {
            usuarios[j + 1] = usuarios[j];
            j--;
        }

        usuarios[j + 1] = temp;
    }
}

void ordenarPorInsercionHabitaciones(stHabitacion habitaciones[], int totalHabitaciones)
{
    int i, j;
    stHabitacion temp;

    for (i = 1; i < totalHabitaciones; i++)
    {
        temp = habitaciones[i];
        j = i - 1;

        // Comparar los nombres y realizar el desplazamiento
        while (j >= 0 && strcmp(habitaciones[j].tipo, temp.tipo) > 0)
        {
            habitaciones[j + 1] = habitaciones[j];
            j--;
        }
        habitaciones[j + 1] = temp;
    }
}

void ordenarPorSeleccion(stUsuario usuarios[], int totalUsuarios)
{
    int i, j, minIndex;
    stUsuario temp;

    for (i = 0; i < totalUsuarios - 1; i++)
    {
        minIndex = i;

        // Encontrar el índice del nombre mínimo en el resto del arreglo
        for (j = i + 1; j < totalUsuarios; j++)
        {
            if (strcmp(usuarios[j].nombre, usuarios[minIndex].nombre) < 0)
            {
                minIndex = j;
            }
        }

        // Intercambiar el elemento mínimo con el actual
        if (minIndex != i)
        {
            temp = usuarios[i];
            usuarios[i] = usuarios[minIndex];
            usuarios[minIndex] = temp;
        }
    }
}

void ordenarPorSeleccionHabitacion(stHabitacion habitaciones[], int totalHabitaciones)
{
    int i, j, posMenor;
    stHabitacion temp;

    for (i = 0; i < totalHabitaciones - 1; i++)
    {
        posMenor = i;

        // Encontrar el índice del nombre mínimo en el resto del arreglo
        for (j = i + 1; j < totalHabitaciones; j++)
        {
            if (strcmp(habitaciones[j].tipo, habitaciones[posMenor].tipo) < 0)
            {
                posMenor = j;
            }
        }

        // Intercambiar el elemento mínimo con el actual
        if (posMenor != i)
        {
            temp = habitaciones[i];
            habitaciones[i] = habitaciones[posMenor];
            habitaciones[posMenor] = temp;
        }
    }
}

/** \fn int existeArchivo(char archivo[])
 * \brief Verifica que exista un archivo enviado por parametro
 * \param archivo string que indica la ruta de acceso del archivo
 * \return Devuelve -1 si se creo el archivo, 0 si el archivo ya existe
 */
int existeArchivo(char archivo[])
{
    int flag = 0;
    FILE *archi = fopen(archivo, "r+b"); // si el archivo existe lo abre y devuelve 0
    if (archi == NULL)
    {
        fopen(archivo, "wb");
        flag = -1; // si el archivo no existe lo crea, abre y devuelve -1
    }
    fclose(archi); // cerramos el archivo
    return flag;
}

/** \fn int backupArchivos(char nombre_original[],char nombre_copia[])
 * \brief Recibe dos archivos, uno con datos y el otro vacio o a formatear, pasa los datos del original al nuevo
 * \param nombre_original archivo con datos a copiar
 * \param nombre_copia archivo donde van a ser copiados los datos
 * \return -1 No se pudo abrir el archivo original.
 * \return 0 No se pudo crear el archivo de copia.
 * \return 1 copia creada
 */
int backupArchivos(char nombre_original[], char nombre_copia[])
{
    existeArchivo(nombre_original);
    existeArchivo(nombre_copia);
    FILE *archivo_original, *archivo_copia;
    char buffer[1024];
    size_t bytes_leidos;

    archivo_original = fopen(nombre_original, "rb");
    if (archivo_original == NULL)
    {
        return -1;
    }

    archivo_copia = fopen(nombre_copia, "wb");
    if (archivo_copia == NULL)
    {
        fclose(archivo_original);
        return 0;
    }

    while ((bytes_leidos = fread(buffer, 1, sizeof(buffer), archivo_original)) > 0)
    {
        fwrite(buffer, 1, bytes_leidos, archivo_copia);
    }

    fclose(archivo_original);
    fclose(archivo_copia);

    return 1;
}

/** \fn void registro()
 * \brief Si ninguno de los tres archivos esta creado, los crea y los rellena con datos iniciales
 */
void registro()
{
    if (existeArchivo(aUsuarios) == -1 &&
        existeArchivo(aConsumibles) == -1 &&
        existeArchivo(aHabitaciones) == -1)
    {
        system("mkdir data");
        /* Datos iniciales, que ahora se comentan por la funcion pedida por mail
        agregarConsumibleArchivo2(agregarConsumiblePorParametro(0, "Agua", "Bebible", 0));
        agregarHabitacionArchivo2(agregarHabitacionPorParametro(0, 0, 0));
        agregarUsuarioArchivo2(agregarUsuarioPorParametro(0, 2, "Admin", "Admin", "admin", "1234", 0, "0", 'o', 0, "0"));
        */
        cargaDeDatosDePrueba();
    }
}

void cargaDeDatosDePrueba() // Funcion pedida por mail
{
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(0, 0, "Agua", "Bebible", 300));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(1, 0, "Coca Cola", "Bebible", 570));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(2, 0, "Sprite", "Bebible", 570));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(3, 0, "Fanta", "Bebible", 570));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(4, 0, "Aquarius", "Bebible", 570));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(5, 0, "Papas Fritas", "Comestible", 460));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(6, 0, "Ensalada", "Comestible", 670));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(7, 0, "Mani", "Comestible", 245));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(8, 0, "Fideos", "Comestible", 789.99));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(9, 0, "Chocolate", "Comestible", 450));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(10, 0, "Vino Tinto Estancia Mendoza Malbec", "Bebible", 1250.00));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(11, 0, "Johnnie Walker Blue Label", "Bebible", 109000.00));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(12, 0, "Gomitas Mogul", "Comestible", 500));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(13, 0, "Speed", "Bebible", 350));
    agregarConsumibleArchivo2(agregarConsumiblePorParametro(14, 0, "Laundry Service", "Otros", 2500));

    agregarHabitacionArchivo2(agregarHabitacionPorParametro(0, 0, 0));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(1, 0, 0));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(2, 0, 0));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(3, 1, 2));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(4, 1, 1));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(5, 1, 1));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(6, 1, 2));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(7, 2, 2));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(8, 2, 1));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(9, 2, 0));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(10, 3, 3));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(11, 3, 3));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(12, 3, 3));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(13, 3, 3));
    agregarHabitacionArchivo2(agregarHabitacionPorParametro(14, 3, 3));

    agregarUsuarioArchivo2(agregarUsuarioPorParametro(0, 2, "Admin", "Admin", "admin", "1234", 0, "0", 'o', 0, "0"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(1, 2, "Tupac", "Rodriguez", "44860125", "44860125", 20, "2233030664", 'm', 0, "Soltero"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(2, 1, "Zoe", "Arozamena", "43851970", "43851970", 21, "2234496290", 'f', 0, "Casado"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(3, 1, "Laureano", "Falcon", "45000000", "45000000", 19, "2914397804", 'm', 0, "Casado"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(4, 0, "Ruben Alberto", "Naccarati", "8704594", "8704594", 74, "2235443331", 'm', 2, "Casado"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(5, 0, "Nelida Ester", "Giaginto", "7450231", "7450231", 76, "2235443330", 'f', 2, "Casado"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(6, 0, "Jose Julian", "Rodriguez", "2155189", "21155189", 53, "2235995007", 'm', 2, "Divorciado"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(7, 0, "Laura Lorena", "Naccarati", "23478350", "23478350", 49, "2233030653", 'f', 2, "Divorciado"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(8, 0, "Luz", "Rodriguez", "48872811", "48872811", 14, "2235994402", 'f', 0, "Soltero"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(9, 0, "Tomas", "Viceconte", "42000000", "42000000", 23, "2235447457", 'm', 0, "Soltero"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(10, 0, "Maximo", "Gimenez", "44125346", "44125346", 21, "2235759899", 'm', 0, "Casado"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(11, 0, "Lucas", "Escobar", "44562187", "44562187", 20, "2235488084", 'm', 0, "Viudo"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(12, 0, "Valentin", "de Luis", "44521784", "44521784", 20, "2236888511", 'm', 0, "Soltero"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(13, 0, "Juan Manuel", "Gratz", "44785124", "44785124", 20, "2236513980", 'm', 0, "Casado"));
    agregarUsuarioArchivo2(agregarUsuarioPorParametro(14, 0, "Zoe", "Elizondo", "44567859", "44567859", 20, "2236928931", 'f', 0, "Casado"));
}

char pedirDocumento()
{
    printf("Ingrese documento del usuario: ");
    char documento[10];
    fflush(stdin);
    gets(documento);
    return documento;
}

char pedirCelular()
{
    printf("Ingrese celular del usuario: ");
    char celular[20];
    fflush(stdin);
    gets(celular);
    return celular;
}

void atras(char texto[])
{
    system("clear || cls");
    printf("%s", texto);
    Sleep(300);
    printf(".");
    Sleep(300);
    printf(".");
    Sleep(300);
    printf(".");
}

int pedirID()
{
    printf("Ingrese id: ");
    int id;
    scanf("%i", &id);
    return id;
}

void crearBackup()
{
    backupArchivos(aUsuarios, aUsuarios_Bak);
    backupArchivos(aHabitaciones, aHabitaciones_Bak);
    backupArchivos(aConsumibles, aConsumibles_Bak);
    printf("BackUp Realizado\n");
}

void restaurarBackup()
{
    backupArchivos(aUsuarios_Bak, aUsuarios);
    backupArchivos(aHabitaciones_Bak, aHabitaciones);
    backupArchivos(aConsumibles_Bak, aConsumibles);
    printf("Archivos restaurados\n");
}

void checkIn(stUsuario u)
{
    stHabitacion a;
    FILE *archi = fopen(aHabitaciones, "r+b");
    if (archi != NULL)
    {
        while (!feof(archi) && fread(&a, sizeof(stHabitacion), 1, archi))
        {
            fread(&a, sizeof(stHabitacion), 1, archi);
            if (strcmp(u.reserva.habitacion.tipo, a.tipo) == 0 && a.estado == 0)
            {
                u.reserva.habitacion.piso = a.piso;
                u.reserva.habitacion.id = a.id;
                a.estado = 1;
                fseek(archi, -sizeof(stHabitacion), SEEK_CUR);
                fwrite(&a, sizeof(stHabitacion), 1, archi);
                break;
            }
        }
        printf("Su habitacion es la del ID: %i en el piso: %i\n", u.reserva.habitacion.id, u.reserva.habitacion.piso);
        fclose(archi);
    }
}

void checkOut(stUsuario u)
{
    cambiarEstadoHabitacion(u.reserva.habitacion.id, 0);
    borrarReserva(u.DNI);
}

void mostrarHabitacionUsuario(stUsuario u)
{
    printf("Su habitacion se encuentra en el piso: %i\n", u.reserva.habitacion.piso);
    printf("El tipo de habitacion es: %s", u.reserva.habitacion.tipo);
}

void ordenarPorNombreUsuario(char filtro[]) // Opcional: Filtrar por nombre (ejemplo: filtrar por usuarios cuyo nombre comienza con 'A')
{
    FILE *archi;
    stUsuario usuarios[100];
    int totalUsuarios = 0;
    archi = fopen(aUsuarios, "rb");
    if (archi == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    while (fread(&usuarios[totalUsuarios], sizeof(stUsuario), 1, archi) == 1)
    {
        totalUsuarios++;
    }

    fclose(archi);

    ordenarPorInsercionUsuario(usuarios, totalUsuarios);

    stUsuario usuariosFiltrados[100];
    int totalUsuariosFiltrados = 0;

    for (int i = 0; i < totalUsuarios; i++)
    {
        if (strncmp(usuarios[i].nombre, filtro, strlen(filtro)) == 0)
        {
            usuariosFiltrados[totalUsuariosFiltrados] = usuarios[i];
            totalUsuariosFiltrados++;
        }
    }

    ordenarPorSeleccion(usuariosFiltrados, totalUsuariosFiltrados);

    for (int i = 0; i < totalUsuariosFiltrados; i++)
    {
        printf("ID %d: %s\n", usuariosFiltrados[i].id, usuariosFiltrados[i].nombre);
    }
}

void ordenarPorTipoHabitacion(char filtro[]) // Opcional: Filtrar por nombre (ejemplo: filtrar por usuarios cuyo nombre comienza con 'A')
{
    FILE *archi;
    stHabitacion habitaciones[100];
    int totalHabitaciones = 0;
    archi = fopen(aHabitaciones, "rb");
    if (archi != NULL)
    {

        while (fread(&habitaciones[totalHabitaciones], sizeof(stHabitacion), 1, archi) == 1)
        {
            totalHabitaciones++;
        }
        fclose(archi);
    }

    ordenarPorInsercionHabitaciones(habitaciones, totalHabitaciones);

    stHabitacion habitacionesFiltradas[100];
    int totalHabitacionesFiltradas = 0;

    for (int i = 0; i < totalHabitacionesFiltradas; i++)
    {
        if (strncmp(habitaciones[i].tipo, filtro, strlen(filtro)) == 0)
        {
            habitacionesFiltradas[totalHabitacionesFiltradas] = habitaciones[i];
            totalHabitacionesFiltradas++;
        }
    }

    ordenarPorSeleccion(habitacionesFiltradas, totalHabitacionesFiltradas);

    for (int i = 0; i < totalHabitacionesFiltradas; i++)
    {
        printf("ID %d: %s\n", habitacionesFiltradas[i].id, habitacionesFiltradas[i].tipo);
    }
}
