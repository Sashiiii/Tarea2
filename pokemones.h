#include <stdlib.h>
#include <stdio.h>
#include "Map.h"
#include "list.h"

typedef struct{
    int id;
    char nombre[20];
    int PC;
    int PS;
    char sexo[20];
}Pokemon_guardado;

typedef struct{
    char nombre[20];
    int existencia;
    char tipos[50];
    char ev_prev[20];
    char ev_post[20];
    int numero_pokedex;
    char region[20];
}Pokemon_pokedex;

void evolucionar_pokemon(Map*, Map*, List**, Map*, Map*);

/*Usa como parametros una Lista y un Tipo de dato Pokemon_Pokedex para insertar el pokemon de un tipo especifico en la lista de tipos*/
void insertar_por_tipos(List**, Pokemon_pokedex*);

void buscar_por_tipo(List**, Map*);

void liberar_pokemon(Map*, Map*, List**, Map*);

void leer_archivo(Map*, Map *,List **, Map *, Map*, Map*);

void agregar_pokemon(Map*, Map*, List**, Map*, Map*, Map*);

void menu_opciones(int, Map *, Map*, List**, Map*, Map*, Map*);

void buscar_pokemon_por_nombre(Map*, char*);