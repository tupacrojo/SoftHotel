#include "menu.h"

void menuHuesped(stUsuario a)
{
    int selector = 0;
    do
    {
        mostrarSubmenuHuesped();
        scanf("%i", &selector);
        switch (selector)
        {
        case 1:
        {
            if (crearReserva(a.id) == 0)
            {
                printf("reserva creada exitosamente");
                selector = 1;
                break;
            }
        }

        case 2:
        {
            mostrarReserva(extraerUsuario(a.id));
            // system("PAUSE");
        }

        case 3:
        {
            borrarReserva(a.DNI);
            system("PAUSE");
            break;
        }
        case 4:
        {
            checkIn(extraerUsuario(a.id));
            system("PAUSE");
            break;
        }
        case 5:
        {
            stUsuario u = extraerUsuario(a.id);
            checkOut(u);
            system("PAUSE");
            break;
        }
        case 6:
        {
            mostrarHabitacionUsuario(extraerUsuario(a.id));
            system("PAUSE");
            break;
        }
        case 7:
        {
            printf("Ingrese su nueva contrase%ca: ", 164);
            char contrasena[20];
            fflush(stdin);
            gets(contrasena);
            cambiarContrasenaUsuario(a.id, contrasena);
            system("PAUSE");
            break;
        }
        case 0:
        {
            atras("Cerrando sesion");
            break;
        }

        default:
        {
            printf("Opcion invalida");
            break;
        }
        }
    } while (selector != 0);
}

void menuEmpleado(stUsuario a)
{
    int selector;
    do
    {
        mostrarSubmenuEmpleado();
        scanf("%i", &selector);
        switch (selector)
        {
        case 1:
        {
            printf("Ingrese documento del usuario: ");
            char documento[10];
            fflush(stdin);
            gets(documento);
            int id = buscarUsuarioDocumento(documento);

            if (crearReserva(id) == 0)
            {
                printf("reserva creada exitosamente");
            }
            break;
        }
        case 2:
        {
            printf("Ingrese documento del usuario: ");
            char documento[10];
            fflush(stdin);
            gets(documento);
            borrarReserva(documento);
            system("PAUSE");
            break;
        }
        case 3:
        {
            printf("Ingrese documento del usuario: ");
            char documento[10];
            fflush(stdin);
            gets(documento);
            int id = buscarUsuarioDocumento(documento);
            mostrarReserva(extraerUsuario(id));
            system("PAUSE");
            break;
        }

        case 4:
        {
            mostrarReservaEnArchivo();
            system("PAUSE");
            break;
        }

        case 5: // Mostrar Huespedes
        {
            mostrarUsuariosTipo(buscarUsuarioTipo(0));
            system("PAUSE");
            break;
        }

        case 6:
        {
            printf("Ingrese documento del usuario: ");
            char documento[10];
            fflush(stdin);
            gets(documento);
            int id = buscarUsuarioDocumento(documento);
            cambiarDatosDeUsuario(9, id);
            system("PAUSE");
            break;
        }

        case 7:
        {
            printf("Ingrese su nueva contrase%ca: ", 164);
            char contrasena[20];
            fflush(stdin);
            gets(contrasena);
            cambiarContrasenaUsuario(a.id, contrasena);
            system("PAUSE");
            selector = 0;
            break;
        }

        case 8:
        {
            printf("Ingrese documento del usuario: ");
            char documento[10];
            fflush(stdin);
            gets(documento);
            int id = buscarUsuarioDocumento(documento);
            checkIn(extraerUsuario(id));
            system("PAUSE");
            break;
        }

        case 9:
        {
            printf("Ingrese documento del usuario: ");
            char documento[10];
            fflush(stdin);
            gets(documento);
            int id = buscarUsuarioDocumento(documento);
            stUsuario u = extraerUsuario(id);
            checkOut(u);
            system("PAUSE");
            break;
        }

        case 10:
        {

            break;
        }

        case 0:
            atras("Cerrando sesion");
            break;

        default:
            printf("Opcion invalida");
            break;
        }
    } while (selector != 0);
}

void menuAdministrador()
{
    int selector = 0;
    do
    {
        mostrarSubmenuAdministrador();
        scanf("%i", &selector);
        switch (selector)
        {
        case 1: // reservas
        {
            int casos = 0;
            do
            {
                reservaAdmin();
                scanf("%i", &casos);
                switch (casos)
                {
                case 1: // Crear Reserva
                {
                    printf("Ingrese documento del usuario: ");
                    char documento[10];
                    fflush(stdin);
                    gets(documento);
                    int id = buscarUsuarioDocumento(documento);

                    if (crearReserva(id) == 0)
                    {
                        printf("reserva creada exitosamente");
                    }
                    break;
                }

                case 2: // Eliminar reserva
                {
                    printf("Ingrese documento del usuario: ");
                    char documento[10];
                    fflush(stdin);
                    gets(documento);
                    borrarReserva(documento);
                    system("PAUSE");

                    break;
                }

                case 3: // Mostrar Reserva
                {
                    printf("Ingrese documento del usuario: ");
                    char documento[10];
                    fflush(stdin);
                    gets(documento);
                    int id = buscarUsuarioDocumento(documento);
                    mostrarReserva(extraerUsuario(id));
                    system("PAUSE");
                    break;
                }

                case 4: // mostrar todas las reservas
                {
                    mostrarReservaEnArchivo();
                    system("PAUSE");
                    break;
                }

                case 0: // volver
                {
                    atras("Volviendo");
                    break;
                }

                default:
                {
                    printf("Opcion invalida");
                    break;
                }
                }
            } while (casos != 0);
            break;
        }

        case 2: // usuarios
        {
            int casos = 0;
            do
            {
                usuarioAdmin();
                scanf("%i", &casos);
                switch (casos)
                {
                case 1: // Crear Reserva
                {
                    int seleccion = 0;
                    do
                    {
                        system("clear || cls");
                        printf("Con que dato desea buscar al usuario?\n- 1 Celular.\n- 2 Documento.\n- 3 Nombre. \n- 0 Volver.\n");
                        printf("Ingrese una opcion: ");
                        scanf("%i", &seleccion);
                        switch (seleccion)
                        {
                        case 1:
                        {
                            printf("Ingrese celular del usuario: ");
                            char celular[20];
                            fflush(stdin);
                            gets(celular);
                            int id = buscarUsuarioCelular(celular);
                            mostrarUsuario(extraerUsuario(id));
                            system("PAUSE");
                            break;
                        }

                        case 2:
                        {
                            printf("Ingrese documento del usuario: ");
                            char documento[10];
                            fflush(stdin);
                            gets(documento);
                            int id = buscarUsuarioDocumento(documento);
                            mostrarUsuario(extraerUsuario(id));
                            system("PAUSE");
                            break;
                        }

                        case 3:
                        {
                            printf("Ingrese Nombre o Letra para filtrar: ");
                            char dato[50];
                            fflush(stdin);
                            gets(dato);
                            ordenarPorNombreUsuario(dato);
                            system("PAUSE");
                            break;
                        }

                        case 0:
                            atras("Volviendo");
                            break;
                        default:
                            printf("opcion invalida");
                            break;
                        }
                    } while (seleccion != 0);
                    break;
                }

                case 2: // Mostrar usuarios por tipo
                {
                    int seleccion = 0;
                    do
                    {
                        system("clear || cls");
                        printf("Que tipo de usuario busca?\n- 1 Huesped.\n- 2 Empleado.\n- 3 Administador.\n- 4 Todos.\n- 0 Volver.\n");
                        printf("Ingrese una opcion: ");
                        scanf("%i", &seleccion);

                        switch (seleccion)
                        {
                        case 1: // Huesped
                            mostrarUsuariosTipo(buscarUsuarioTipo(0));
                            system("PAUSE");
                            break;

                        case 2: // Empleado
                            mostrarUsuariosTipo(buscarUsuarioTipo(1));
                            system("PAUSE");
                            break;

                        case 3: // Administrador
                            mostrarUsuariosTipo(buscarUsuarioTipo(2));
                            system("PAUSE");
                            break;

                        case 4: // Todos
                            mostrarUsuarios();
                            // mostrar huespedes mostrar por tipo, usamos la que filtra por tipo y devuelve pila y hacer funcion que reciba una pila y muestre todos los ids
                            break;

                        case 0:
                            atras("Volviendo");
                            break;

                        default:
                            printf("opcion invalida");
                            break;
                        }
                    } while (seleccion != 0);
                    break;
                }

                case 3: // Agregar Usuario
                {
                    agregarUsuarioArchivo();
                    system("PAUSE");
                    break;
                }

                case 4: // Editar Usuario
                {
                    printf("Ingrese documento del usuario: ");
                    char documento[10];
                    fflush(stdin);
                    gets(documento);
                    mostrarUsuario(extraerUsuario(buscarUsuarioDocumento(documento)));
                    printf("Que dato desea modificar?\n- 0 Nombre. \n- 1 Apellido.\n- 2 DNI. \n- 3 Estado civil. \n- 4 Genero. \n- 5 Telefono. \n- 6 Cantidad de hijos. \n- 7 Tipo de usuario. \n- 8 Contrase%ca.\n- 9 Consumo.\n", 164);
                    printf("Ingrese una opcion: ");
                    int opcion = 0;
                    scanf("%i", &opcion);
                    cambiarDatosDeUsuario(opcion, buscarUsuarioDocumento(documento));
                    system("PAUSE");
                    break;
                }

                case 5: // eliminar usuario
                {
                    printf("Ingrese documento del usuario: ");
                    char documento[10];
                    fflush(stdin);
                    gets(documento);
                    borrarUsuario(buscarUsuarioDocumento(documento));
                    system("PAUSE");
                    break;
                }

                case 6: // baja logica
                {
                    cambiarBorradoUsuario(pedirID());
                    break;
                }

                case 7:
                {
                    char nombre[50];
                    printf("Ingrese letra con la que filtra: ");
                    fflush(stdin);
                    gets(nombre);
                    ordenarPorNombreUsuario(nombre);
                    break;
                }

                case 8: // check In
                {
                    printf("Ingrese documento del usuario: ");
                    char documento[10];
                    fflush(stdin);
                    gets(documento);
                    int id = buscarUsuarioDocumento(documento);
                    checkIn(extraerUsuario(id));
                    printf("Bienvenido\n");
                    system("PAUSE");
                    break;
                }

                case 9: // check Out
                {
                    printf("Ingrese documento del usuario: ");
                    char documento[10];
                    fflush(stdin);
                    gets(documento);
                    int id = buscarUsuarioDocumento(documento);
                    stUsuario u = extraerUsuario(id);
                    checkOut(u);
                    printf("Hasta luego\n");
                    system("PAUSE");
                    break;
                }

                case 0:
                {
                    atras("Volviendo");
                    break;
                }

                default:
                {
                    printf("Opcion invalida");
                    break;
                }
                }
            } while (casos != 0);
            break;
        }

        case 3: // habitaciones
        {
            int casos = 0;
            do
            {
                habitacionAdmin();
                scanf("%i", &casos);
                switch (casos)
                {
                case 1: // Mostrar Habitaciones
                {
                    mostrarHabitaciones();
                    system("PAUSE");
                    break;
                }

                case 2: // Agregar Habitacion
                {
                    agregarHabitacionArchivo();
                    system("PAUSE");
                    break;
                }

                case 3: // Editar Habitacion
                {
                    printf("Que dato desea modificar?\n- 0 Tipo.\n- 1 Estado.\n- 2 Piso.\n");
                    printf("Ingrese una opcion: ");
                    int seleccion = 0;
                    scanf("%i", &seleccion);

                    printf("Ingrese ID de habitacion: ");
                    int id = 0;
                    scanf("%i", &id);
                    cambiarDatosDeHabitacion(seleccion, id);
                    system("PAUSE");
                    break;
                }

                case 4: // Eliminar Habitacion
                {
                    borrarHabitacion(pedirID());
                    system("PAUSE");
                    break;
                }

                case 5: // baja logica habitacion
                {
                    cambiarBorradoHabitacion(pedirID());
                    break;
                }

                case 6:
                {
                    char dato[50];
                    printf("Que tipo de habitacion buscas?\n");
                    fflush(stdin);
                    gets(dato);
                    ordenarPorTipoHabitacion(dato);
                    break;
                }

                case 0:
                {
                    atras("Volviendo");
                    break;
                }

                default:
                {
                    printf("Opcion invalida");
                    break;
                }
                }
            } while (casos != 0);
            break;
        }

        case 4: // consumibles
        {
            int casos = 0;
            do
            {
                consumibleAdmin();
                scanf("%i", &casos);
                switch (casos)
                {
                case 1: // Mostrar consumible
                {
                    mostrarConsumibles();
                    system("PAUSE");
                    break;
                }
                case 2: // Agregar Consumible
                {
                    agregarConsumibleArchivo();
                    system("PAUSE");
                    break;
                }
                case 3: // Editar Consumible
                {
                    printf("Que dato desea modificar?\n- 0 Nombre.\n- 1 Categoria.\n- 2 Precio.\n");
                    printf("Ingrese una opcion: ");
                    int opcion = 0;
                    scanf("%i", &opcion);
                    cambiarDatosDeConsumible(opcion, pedirID());
                    system("PAUSE");
                    break;
                }
                case 4: // Eliminar Consumible
                {
                    if (borrarConsumbible(pedirID()) == 0)
                    {
                        printf("Consumible borrado");
                    }
                    else
                    {
                        printf("No se encuentra el consumible");
                    }
                    system("PAUSE");
                    break;
                }
                case 5: // baja Logica
                {
                    cambiarBorradoConsumible(pedirID);
                    break;
                }
                case 6: //Mostrar Consumibles por precio
                {
                    stUtils u = crearMatrizConsumibles();
                    ordenarPorInsercionMatrizFilaFija(u.idPrecio, 1, u.cantidad);
                    imprimirMatrizConNombres(u.idPrecio, u.cantidad);
                    system("PAUSE");
                    break;
                }
                case 0:
                {
                    atras("Volviendo");
                    break;
                }
                default:
                {
                    printf("Opcion invalida");
                    break;
                }
                }
            } while (casos != 0);
        }

        case 5: // Crear Backup
        {
            crearBackup();
            system("PAUSE");
            break;
        }

        case 6: // Restaurar Backup
        {
            restaurarBackup();
            system("PAUSE");
            break;
        }

        case 0: // cerrar Sesion
        {
            atras("Cerrando sesion");
            break;
        }

        default:
        {
            printf("Opcion invalida");
            break;
        }
        }
    } while (selector != 0);
}
