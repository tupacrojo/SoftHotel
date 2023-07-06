#pragma once
#include <stdio.h>
#include <time.h>
#include "habitacion.h"

typedef struct ///  "stReserva" reserva
{
    stHabitacion habitacion;
    int borrado;
    // entrada
    int diaEntrada;
    int mesEntrada;
    int anioEntrada;
    // salida
    int diaSalida;
    int mesSalida;
    int anioSalida;
}stReserva;

int esFechaValida(int dia, int mes, int anio);
int esFechaPosterior(int dia, int mes, int anio);
int esFechaPosteriorA(int diaAn, int mesAn, int anioAn, int diaPos, int mesPos, int anioPos);
