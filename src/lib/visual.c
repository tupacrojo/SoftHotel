#include "visual.h"

void mostrarMenuPrincipal()
{
    system("clear || cls");
    printf("=== Men%c Principal ===\n", 163);
    printf("1. Iniciar sesi%cn\n", 162);
    printf("2. Salir\n");
    printf("Ingrese una opci%cn: ", 162);
}

void mostrarSubmenuHuesped()
{
    system("clear || cls");
    printf("=== Hu%csped ===\n", 130);
    printf("1. Crear reserva\n");
    printf("2. Ver reserva\n");
    printf("3. Eliminar reserva\n");
    printf("4. Check In\n");
    printf("5. Check Out\n");
    printf("6. Consultar Habitaci%cn\n", 162);
    printf("7. Cambiar contrase%ca\n", 164);
    printf("0. Cerrar sesi%cn\n", 162);
    printf("Ingrese una opci%cn: ", 162);
}

void mostrarSubmenuEmpleado()
{
    system("clear || cls");
    printf("=== Empleado ===\n");
    printf("1. Crear reserva\n");
    printf("2. Eliminar reserva\n");
    printf("3. Mostrar reserva\n");
    printf("4. Mostrar TODAS las reservas\n");
    printf("5. Mostrar Hu%cspedes\n", 130);
    printf("6. Agregar consumo Hu%csped\n", 130);
    printf("7. Cambiar contrase%ca\n", 164);
    printf("8. Check In\n");
    printf("9. Check Out\n");
    printf("0. Cerrar sesi%cn\n", 162);
    printf("Ingrese una opci%cn: ", 162);
}

void mostrarSubmenuAdministrador()
{
    system("clear || cls");
    printf("=== Administrador ===\n");

    printf("1 - Reservas\n");
    printf("2 - Usuarios\n");
    printf("3 - Habitaciones\n");
    printf("4 - Consumibles\n");

    printf("5 - Crear backup\n");
    printf("6 - Restaurar backup\n");

    printf("0 - Cerrar Sesi%cn\n", 162);
    printf("Ingrese una opci%cn: ", 162);
}

void reservaAdmin()
{
    system("clear || cls");
    printf("1 - Crear reserva\n");
    printf("2 - Eliminar reserva\n");
    printf("3 - Mostrar reserva\n");
    printf("4 - Mostrar TODAS las reservas\n");
    printf("0 - Volver\n");
    printf("Ingrese una opci%cn: ", 162);
}

void usuarioAdmin()
{
    system("clear || cls");
    printf("1 - Buscar Usuario\n");
    printf("2 - Mostrar usuario por tipo\n");
    printf("3 - Agregar usuario\n");
    printf("4 - Editar usuario\n");
    printf("5 - Eliminar usuario\n");
    printf("6 - Baja logica\n");
    printf("7 - Ordenar por Tipo\n");

    printf("8 - Check In\n");
    printf("9 - Check Out\n");
    
    printf("0 - Volver\n");
    printf("Ingrese una opci%cn: ", 162);
}

void habitacionAdmin()
{
    system("clear || cls");
    printf("1 - Mostrar Habitaci%cnes\n", 162);
    printf("2 - Agregar Habitaci%cn\n", 162);
    printf("3 - Editar Habitaci%cn\n", 162);
    printf("4 - Eliminar Habitaci%cn\n", 162);
    printf("5 - Baja logica Habitaci%cn\n", 162);

    printf("0 - Volver\n");
    printf("Ingrese una opci%cn: ", 162);
}

void consumibleAdmin()
{
    system("clear || cls");
    printf("1 - Mostrar Consumible\n");
    printf("2 - Agregar Consumible\n");
    printf("3 - Editar Consumible\n");
    printf("4 - Eliminar Consumible\n");
    printf("5 - Baja Logica\n");
    printf("6 - Mostrar Consumibles por precio\n");

    printf("0 - Volver\n");
    printf("Ingrese una opci%cn: ", 162);
}