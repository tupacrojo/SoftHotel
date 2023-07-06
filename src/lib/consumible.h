#pragma once
#include "pila.h"

typedef struct ///  "stConsumibles" elementos disponibles para consumo
{
    int id;
    int borrado;
    char nombre[50];
    char categoria[50]; // Bebible, Comestible
    float precio;
}stConsumibles;


int obtenerUltimoIdConsumibles();
void agregarConsumible(stConsumibles *c);
void agregarConsumibleArchivo();
void agregarConsumibleArchivo2(stConsumibles c);

void mostrarConsumible(stConsumibles c);
void mostrarConsumibles();

stConsumibles agregarConsumiblePorParametro(int id, int borrado,  char nombre[], char categoria[], float precio);
int borrarConsumbible(int id);
void borraDatosConsumible(stConsumibles *c);

stConsumibles extraerConsumible(int id);
Pila buscarConsumiblePorCategoria(char categoria[]);

void cambiarBorradoConsumible(int id);
int cambiarNombreConsumible(int id, char nuevoNombre[]);
int cambiarCategoriaConsumible(int id, char nuevaCategoria[]);
int cambiarPrecioConsumible(int id, float nuevoPrecio);
int cambiarDatosDeConsumible(int selector, int id);
