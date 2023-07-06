#pragma once
#include <stdio.h>
#include <string.h>
#include "usuario.h"

#include "../config/files.h"
#include "visual.h"
#include "consumible.h"
#include "habitacion.h"
#include "pila.h"
#include "reserva.h"
#include "usuario.h"

typedef struct
{
    float idPrecio[2][100];
    int cantidad;
    char arrayCategoria[100][50];
    char arrayNombre[100][50];
    int arrayID[100];
}stUtils;

void ordenarPorInsercionMatrizFilaFija(float matriz[][100], int fila, int columnas);
void ordenarPorInsercionMatriz(float matriz[][100], int filas, int columnas);

void imprimirMatriz(float matriz[][100], int columnas);

void ordenarPorInsercionUsuario(stUsuario usuarios[], int totalUsuarios);
void ordenarPorSeleccion(stUsuario usuarios[], int totalUsuarios);
void ordenarPorNombreUsuario(char filtro[]);

void ordenarPorInsercionHabitaciones(stHabitacion habitaciones[], int totalHabitaciones);
void ordenarPorSeleccionHabitacion(stHabitacion habitaciones[], int totalHabitaciones);
void ordenarPorTipoHabitacion(char filtro[]);

void imprimirMatrizConNombres(float matriz[][100], int columnas);
stUtils crearMatrizConsumibles();
stUtils crearArregloDePalabraConsumibles();
void mostrarUtilsPar(stUtils ut);

int existeArchivo(char archivo[]);
int backupArchivos(char nombre_original[], char nombre_copia[]);
void registro();
void cargaDeDatosDePrueba();
char pedirDocumento();
char pedirCelular();
int pedirID();
void crearBackup();
void atras(char texto[]);
void mostrarHabitacionUsuario(stUsuario u);
void restaurarBackup();
void checkIn(stUsuario u);
void checkOut(stUsuario u);


