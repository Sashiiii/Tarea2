#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "pokemones.h"
#include "list.h"

int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

//  función para comparar claves de tipo string
//  retorna 1 si son key1<key2

int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

//  función para comparar claves de tipo int
//  retorna 1 si son iguales

int is_equal_int(void * key1, void * key2) {
    if(*(int*)key1 == *(int*)key2) return 1;
    return 0;
}

//  función para comparar claves de tipo int
//  retorna 1 si son key1<key2

int lower_than_int(void * key1, void * key2) {
    if(*(int*)key1 < *(int*)key2) return 1;
    return 0;
}

int higher_than_int(void * key1, void * key2) {
    if(*(int*)key1 > *(int*)key2) return 1;
    return 0;
}
int main() {
    //Mapa de pokemones segun que se ingresara para buscar
    Map* pokemones_por_id = createMap(is_equal_int);
    Map* pokemones_por_nombre = createMap(is_equal_string);
    Map* pokemones_por_PC = createMap(is_equal_int);
    Map* pokedex_por_nombre = createMap(is_equal_string);
    Map* pokedex_por_numero = createMap(is_equal_int);
    setSortFunction(pokedex_por_numero,lower_than_int);
    setSortFunction(pokemones_por_PC,higher_than_int);
    List* pokemones_por_tipo[18];
    for(int i = 0; i < 18 ; i++){
        pokemones_por_tipo[i] = create_list();
    }
    //List* fuego, *agua, *veneno, *fantasma, *acero, *normal, *electrico, *psiquico, *planta;
    //List* bicho, *tierra, *lucha, *roca, *hielo, *hada, *siniestro, *volador, *dragon;
    /*
    [0]fuego
    [1]agua 
    [2]veneno
    [3]fantasma
    [4]acero
    [5]normal
    [6]electrico
    [7]psiquico
    [8]planta
    [9]bicho
    [10]tierra
    [11]lucha
    [12]roca
    [13]hielo
    [14]hada
    [15]siniestro
    [16]volador
    [17]dragon
    */

    int opcion = -1;
    menu_opciones(opcion, pokemones_por_id, pokemones_por_nombre, pokemones_por_tipo, pokedex_por_nombre, pokedex_por_numero, pokemones_por_PC);
    return 0;
}
