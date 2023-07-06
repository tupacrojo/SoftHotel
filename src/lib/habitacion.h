
#pragma once
#include <stdio.h>
#include "pila.h"

typedef struct ///  "stHabitacion" habitacion
{
    int id;
    int borrado;
    int estado;    // 0 libre; 1 Ocupado;
    int piso;      // pisos
    char tipo[50]; // "Basica, Deluxe, Suite, Suite Premium"
}stHabitacion;

int obtenerUltimoIdHabitaciones();
stHabitacion extraerHabitacion(int id);
Pila buscarHabitacionTipo(char tipo[]);

void agregarHabitacion(stHabitacion *a);
void agregarHabitacionArchivo();
void agregarHabitacionArchivo2(stHabitacion a);
stHabitacion agregarHabitacionPorParametro(int id, int piso, int tipo);

int borrarHabitacion(int id);
void borraDatosHabitacion(stHabitacion *a);

void mostrarHabitacionTipo(Pila p);
void mostrarHabitacion(stHabitacion a);
void mostrarHabitaciones();

int cambiarDatosDeHabitacion(int selector, int id);
void cambiarBorradoHabitacion(int id);
int cambiarTipoHabitacion(int id, char nuevoTipo[]);
int cambiarEstadoHabitacion(int id, int nuevoEstado);
int cambiarPisoHabitacion(int id, int nuevoPiso);
