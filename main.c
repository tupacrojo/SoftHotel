// Usuario: admin | Contraseña: 1234 (ADMIN)
// Usuario: 44860125 | Contraseña: 44860125 (ADMIN)
// Usuario: 43851970 | Contraseña: 43851970 (Empleado)
// Usuario: 8704594 | Contraseña: 8704594 (Huesped)

// Rodriguez Tupac, Arozamena Zoe, Laureano Falcon

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <shlobj.h>
#include <time.h>
#include <conio.h>
#include <time.h>

#include "src/lib/visual.h"
#include "src/config/files.h"
#include "src/lib/consumible.h"
#include "src/lib/habitacion.h"
#include "src/lib/pila.h"
#include "src/lib/reserva.h"
#include "src/lib/usuario.h"
#include "src/lib/utils.h"
#include "src/lib/menu.h"

int main()
{
    int opcion = 0;
    do
    {
        opcion = 0;
        registro();
        mostrarMenuPrincipal();
        scanf("%i", &opcion);

        switch (opcion)
        {
        case 1: // Iniciar Sesion
            opcion = 0;
            stUsuario a;
            int tipoUsuario;
            a = iniciarSesion();
            int id = buscarUsuarioDocumento(a.DNI);
            tipoUsuario = obtenerTipoUsuario(id);
            switch (tipoUsuario)
            {
            case 0:
            {
                menuHuesped(a);
                break;
            }

            case 1:
            {
                menuEmpleado(a);
                break;
            }
            case 2:
            {
                menuAdministrador(a);
                break;
            }
            }
        case 2: // Salir
        {
            atras("Saliendo");
            break;
        }

        }
    } while (opcion != 2);
    return 0;
}
