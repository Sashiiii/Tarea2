#include "Map.h"
#include "pokemones.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int existencia;
void menu_opciones(int opcion,Map* pokemones_por_id, Map* pokemones_por_nombre, List** pokemones_por_tipo, Map* pokedex_por_nombre, Map* pokedex_por_numero, Map* pokemones_por_PC){
  Pokemon_pokedex *p;
  Pokemon_guardado *k;
  char nombre[20];
  //se muestra el menu por pantalla
  while(opcion != 10){
    printf("\n|======================|\n");
    printf("|        Pokemon       |\n");
    printf("|======================|\n");
    printf("1 - Importar desde un archivo\n");
    printf("2 - Agregar pokemon atrapado\n");
    printf("3 - Evolucionar pokemon\n");
    printf("4 - Buscar entre mis pokemon por tipo\n");
    printf("5 - Buscar entre mis pokemon por nombre\n");
    printf("6 - Buscar pokemon por nombre en la pokedex\n");
    printf("7 - Mostrar todos los pokemon en la pokedex\n");
    printf("8 - Mostrar pokemones encontrados ordenados por PC\n");
    printf("9 - Liberar pokemon\n");
    printf("10 - Salir\n");
    printf("~Ingrese el numero de la operacion que desee realizar: ");
    scanf("%d", &opcion);
    //switch para que el programa realice lo que pide el usuario
    switch (opcion){
    case 1:
     //pokemon p se situa al principio de la pokedex para poder recorrer el mapa y poser calcular cuantos pokemones hay almacenados en la variable
     //"existencia"
        p=firstMap(pokedex_por_numero);
        existencia = 0;
        while(p!=NULL){
         existencia=existencia+p->existencia;
         p=nextMap(pokedex_por_numero); 
        }
     //si la existencia es menor que 100 (que es la capacidad maxima) se podra agregar un pokemon
        if(existencia<100){
          leer_archivo(pokemones_por_id, pokemones_por_nombre,pokemones_por_tipo, pokedex_por_nombre, pokedex_por_numero, pokemones_por_PC);
          //se vuelve a contar la cantidad de pokemones despues de agregar
          p=firstMap(pokedex_por_numero);
          existencia = 0;
          while(p!=NULL){
            existencia=existencia+p->existencia;
          p=nextMap(pokedex_por_numero); 
          }
        }else{
          printf("usted ya posee el limite de pokemons en el inventario %d/100\n");
        }
        printf("Usted posee %d/100 pokemones\n", existencia);
        break;
    case 2:
      //se verifica que hayan menos de 100 pokemones
        p=firstMap(pokedex_por_numero);
        existencia = 0;
        while(p!=NULL){
         existencia = existencia+p->existencia;
         p=nextMap(pokedex_por_numero); 
        }
        if(existencia<100){
          agregar_pokemon(pokemones_por_id, pokemones_por_nombre, pokemones_por_tipo, pokedex_por_nombre, pokedex_por_numero, pokemones_por_PC);
        }else{
          printf("usted ya posee el limite de pokemones en el inventario %d/100\n");
        }
        printf("Usted posee %d/100 pokemones\n", existencia);
        if(existencia==100){
          printf("usted ya posee el limite de pokemones en el inventario %d/100\n", existencia);
          break;
        }     
        printf("Usted posee %d pokemones\n", existencia);
        break;
    case 3:
        evolucionar_pokemon(pokemones_por_id, pokemones_por_nombre,pokemones_por_tipo, pokedex_por_nombre,pokedex_por_numero);
        break;
    case 4:
        buscar_por_tipo(pokemones_por_tipo);
        break;
    case 5:
        buscar_pokemon_por_nombre(pokemones_por_nombre);
        break;
    case 6:
        printf("~Ingrese el nombre del pokemon: ");
        scanf("%s", &nombre);
        p=searchMap(pokedex_por_nombre, &nombre);
        printf("Nombre: %s\nExistencia: %d\nTipo/s: %s\nEvolucion previa: %s\nEvolucion Posterior: %s\nNumero Pokedex: %d\nRegion: %s\n",p->nombre, p->existencia, p->tipos, p->ev_prev, p->ev_post,p->numero_pokedex,p->region);
        printf("\n");
        break;
    case 7:
        p=firstMap(pokedex_por_numero);
        printf("Nombre, Existencia, Tipo, Evolucion previa, Evolucion Posterior, Numero Pokedex, Region\n");
        while(p){
            printf("%s, %d, %s, %s, %s, %d, %s \n",p->nombre, p->existencia, p->tipos, p->ev_prev, p->ev_post,p->numero_pokedex,p->region);
            printf("\n");
            p=nextMap(pokedex_por_numero);
        }
        break;
    case 8:
        k=firstMap(pokemones_por_PC);
        printf("Pokemons ordenados por PC\nID -- NOMBRE -- PC -- PS -- SEXO\n");
        while (k){
          printf("%d %s %d %d %s", k->id, k->nombre, k->PC, k->PS, k->sexo);
          printf("\n");
          k=nextMap(pokemones_por_PC);
        }
        break;
    case 9:
        liberar_pokemon(pokemones_por_id, pokemones_por_nombre, pokemones_por_tipo, pokedex_por_nombre);
        p=firstMap(pokedex_por_numero);
        existencia = 0;
        while(p!=NULL){
         existencia=existencia+p->existencia;
         p=nextMap(pokedex_por_numero); 
        }
        printf("Usted posee %d pokemons\n", existencia);
        break;
    case 10:
        printf("Adios!\n");
        break;
    }
  }
  return;
}

void evolucionar_pokemon(Map* pokemones_por_id, Map* pokemones_por_nombre, List** pokemones_por_tipo, Map* pokedex_por_nombre, Map* pokedex_por_numero){
  Pokemon_guardado* pg;
  Pokemon_pokedex* pp, *pp2;
  char linea[50];
  int id;
  printf("~ingrese el id del pokemon que desea evolucionar: ");
  scanf("%d", &id);
  //mensaje en caso de que el pokemon con el id ingresado no exista
  if(searchMap(pokemones_por_id, &id) == NULL){
    printf("El pokemon asociado al id ingresado no existe\n");
    return;
  }else{
    pg = searchMap(pokemones_por_id, &id);
    pp = searchMap(pokedex_por_nombre, &pg->nombre);
    pp2 = (Pokemon_pokedex*)malloc(sizeof(Pokemon_pokedex));
    if(stricmp(pp->ev_post, "no tiene")==0){
      printf("El pokemon asociado al id ingresado no posee evolucion posterior a la actual\n");
      return;
    }else{
      pp->existencia--;
      eraseMap(pokedex_por_nombre, &pg->nombre);
      insertMap(pokedex_por_nombre, &pp->nombre, pp);
      eraseMap(pokemones_por_id, &pg->id);
      eraseMap(pokemones_por_nombre, &pg->nombre);
      strncpy(pp2->ev_prev,pp->nombre,20);
      strncpy(pg->nombre,pp->ev_post,20);
      strncpy(pp2->nombre,pp->ev_post,20);
      pg->PC = pg->PC + (pg->PC/2);
      pg->PS = pg->PS + (pg->PS/4);
  
      printf("~ingrese el numero en la pokedex del nuevo pokemon: ");
      scanf("%d",&pp2->numero_pokedex);
      fgetc(stdin);
      if(searchMap(pokedex_por_nombre, pp2->nombre)!=NULL){
        pp2 = searchMap(pokedex_por_nombre, &pp2->nombre);
        eraseMap(pokedex_por_nombre,&pp2->nombre);
        insertMap(pokedex_por_nombre, &pp2->nombre, pp2);
        eraseMap(pokedex_por_numero,&pp2->numero_pokedex);
        insertMap(pokedex_por_numero, &pp2->numero_pokedex, pp2);
      }else{
      pp2->existencia=1;
      strncpy(pp2->region,pp->region,20);
      printf("~ingrese el nombre de la evolucion siguiente de %s: ", pg->nombre);
      fgets(pp2->ev_post, 20, stdin);
      pp2->ev_post[strcspn(pp2->ev_post, "\n")] = 0;
      printf("~Ingrese los tipos separados por un espacio\nPor ej: tipo1 tipo2 tipo3...\n");
      fgets(linea, 49, stdin);
      linea[strcspn(linea, "\n")] = 0;
      strncpy(pp2->tipos, linea, 50);
      pp2->ev_post[strcspn(pp2->ev_post, "\n")] = 0;
      insertMap(pokemones_por_id, &pg->id, pg);
      insertMap(pokemones_por_nombre, &pg->nombre, pg);
      insertMap(pokedex_por_nombre, &pp2->nombre, pp2);
      insertMap(pokedex_por_numero, &pp2->numero_pokedex, pp2);
      }
    }
  }
}

void liberar_pokemon(Map* pokemones_por_id, Map* pokemones_por_nombre, List** pokemones_por_tipo, Map* pokedex_por_nombre){
  int id;
  Pokemon_guardado* pg;
  Pokemon_pokedex* pp;
  printf("~ingrese el id del pokemon que desea eliminar: ");
  scanf("%d", &id);
  if(searchMap(pokemones_por_id, &id) != NULL){
    pg = searchMap(pokemones_por_id, &id);
    eraseMap(pokemones_por_id, &id);
    eraseMap(pokemones_por_nombre, &pg->nombre);
    pp = searchMap(pokedex_por_nombre, &pg->nombre);
    pp->existencia = pp->existencia-1;
    eraseMap(pokedex_por_nombre, &pg->nombre);
    insertMap(pokedex_por_nombre,&pp->nombre,pp);
    printf("El pokemon ha sido liberado!\n");
    //borrar de por tipo
  }else{
    printf("El pokemon que se busca eliminar no existe\n");
  }
}


void agregar_pokemon(Map* pokemones_por_id, Map* pokemones_por_nombre, List** pokemones_por_tipo, Map* pokedex_por_nombre, Map* pokedex_por_numero, Map* pokemones_por_PC){
  int id;
  Pokemon_guardado* pg;
  Pokemon_pokedex* pp;
  pg = (Pokemon_guardado *)malloc(sizeof(Pokemon_guardado));
  pp = (Pokemon_pokedex *)malloc(sizeof(Pokemon_pokedex));
  char linea[50];
  printf("~Ingrese el nombre del pokemon: ");
  scanf("%s", &pg->nombre);
  strncpy(pp->nombre, pg->nombre, 20);
  printf("~Ingrese el id del pokemon: ");
  scanf("%d", &id);
  //verificar que no exista pokemon guardado con ese id
  pg->id=id;
  fgetc(stdin);
  printf("~Ingrese los tipos separados por una coma y un espacio\nPor ej: tipo1, tipo2, tipo3...\n");
  fgets(linea, 49, stdin);
  linea[strcspn(linea, "\n")] = 0;
  strncpy(pp->tipos, linea, 50);
  if(searchMap(pokedex_por_nombre, pp->nombre)==NULL){
    printf("~Ingrese la evolucion previa del pokemon: ");
    fgets(pp->ev_prev, 20, stdin);
    pp->ev_prev[strcspn(pp->ev_prev, "\n")] = 0;
    printf("~Ingrese la evolucion posterior del pokemon: ");
    fgets(pp->ev_post, 20, stdin);
    pp->ev_post[strcspn(pp->ev_post, "\n")] = 0;
    printf("~Ingrese la region del pokemon: ");
    scanf("%s", &pp->region);
    printf("~Ingrese el numero del pokemon en la pokedex: ");
    scanf("%d", &pp->numero_pokedex);
    pp->existencia=0;
  }else{
    pp = searchMap(pokedex_por_nombre, &pp->nombre);
  }
  printf("~Ingrese el sexo del pokemon: ");
  scanf("%s", &pg->sexo);
  printf("~Ingrese PC del pokemon: ");
  scanf("%d", &pg->PC);
  printf("~Ingrese PS del pokemon: ");
  scanf("%d", &pg->PS); 
  pp->existencia++;
  insertMap(pokemones_por_id, &pg->id, pg);
  insertMap(pokemones_por_nombre, &pg->nombre, pg);
  insertMap(pokedex_por_nombre, &pg->nombre, pp);
  insertMap(pokedex_por_numero, &pp->numero_pokedex, pp);
  insertMap(pokemones_por_PC,&pg->PC,pg);
/*Se insertan los pokemones por tipo en la estructura correspondiente*/  
  insertar_por_tipos(pokemones_por_tipo, pp);
  //agregar por tipo
  printf("El archivo se ha leido correctamente!\n");
  return;
}

void buscar_pokemon_por_nombre(Map* pokemones_por_nombre){
  char nombre[20];
  Pokemon_guardado* pg;
  //pg = (Pokemon_guardado *)malloc(sizeof(Pokemon_guardado));
  printf("~ingrese el nombre del pokemon a buscar!\n");
  scanf("%s", &nombre);
  pg = searchMap(pokemones_por_nombre,&nombre);
  if(pg != NULL){
    printf("\n~%s~:\n", pg->nombre);
    printf("ID: %d\n", pg->id);
    printf("sexo: %s\n", pg->sexo);
    printf("PC: %d\n", pg->PC);
    printf("PS: %d\n", pg->PS);
  }else{
    printf("No se ha encontrado al pokemon :c\n");
  }
}

/* Funcion para leer el archivo que se desea. */
void leer_archivo(Map*pokemones_por_id, Map *pokemones_por_nombre,List **pokemones_por_tipo, Map *pokedex_por_nombre, Map *pokedex_por_numero, Map *pokemones_por_PC){

  /* Se abre el archivo correspondiente. */
  char archivo[20];
  printf("~Por favor ingrese el archivo que se desea leer: ");
  scanf("%s", archivo);
  FILE *archivoEntrada = fopen(archivo, "r");

  /* Si hubo algun problema con abrir el archivo imprime el siguiente mensaje. */
  if (archivoEntrada == NULL)
  {
    printf("El archivo no se pudo abrir en modo lectura");
    return;
  }

  /* Aqui se almacenaran el archivo por linea. */
  char linea[1024];


  char *datospokemon;  

  /* Se define las variables 'pokemonI' tipo 'pokemonInv' y 'pokemonD' tipo 'PokemonDex', con el fin de almacenar todos los datos de los pokemon del archivo
   * en sus estructuras correspondientes.
   */
   Pokemon_guardado *pokemonI;
   Pokemon_pokedex *pokemonD; 
   Pokemon_pokedex *Pauxiliar;

  while (fscanf(archivoEntrada, "%[^\n]s", linea) != EOF){
    fgetc(archivoEntrada);
    char caux=linea[0];
    const char comilla[2]={'"'};
    int len, g=0, flag=0;
    len=strlen(linea);
    Pokemon_pokedex *p=firstMap(pokedex_por_numero);
    int existencia = 0;
    while(p!=NULL){
    existencia=existencia+p->existencia;
    p=nextMap(pokedex_por_numero); 
    }     
    while(g<len){
      if(caux==comilla[0]){
        flag=1;
        break;
      }
      g++;    
      caux=linea[g];
    }

    pokemonI = (Pokemon_guardado *)malloc(sizeof(Pokemon_guardado));
    pokemonD = (Pokemon_pokedex*)malloc(sizeof(Pokemon_pokedex));
    Pauxiliar = (Pokemon_pokedex*)malloc(sizeof(Pokemon_pokedex));

   /*Se inserta la id*/
    datospokemon = strtok(linea, ",");
    pokemonI->id=atoi(datospokemon);
    existencia++;
    
   /*Se inserta el nombre en el inventario y en la pokedex*/ 
    datospokemon = strtok(NULL, ",");
    strcpy(pokemonI->nombre, datospokemon);
    strcpy(pokemonD->nombre,datospokemon);
    
   /*Se inserta el tipo en la pokedex*/ 
    if(flag==0){ 
      datospokemon = strtok(NULL, ",");
      strcpy(pokemonD->tipos,datospokemon);
    }
    if(flag!=0){
      datospokemon = strtok(NULL, comilla);
      strcpy(pokemonD->tipos,datospokemon);
    }

  /*Se inserta los puntos de combate en el mapa del inventario*/  
    datospokemon = strtok(NULL, ",");                
    pokemonI->PC=atoi(datospokemon);
    
  /*Se insertan los puntos de salud al pokemon en el mapa del inventario*/  
    datospokemon = strtok(NULL, ",");               
    pokemonI->PS=atoi(datospokemon);
    
  /*Se añade el sexo del pokemon al mapa del inventario*/  
    datospokemon = strtok(NULL, ",");
    strcpy(pokemonI->sexo,datospokemon);

  /*Se añade la evolucion previa del pokemon en el mapa de la pokedex*/  
    datospokemon = strtok(NULL, ",");                
    strcpy(pokemonD->ev_prev,datospokemon);
    
    datospokemon = strtok(NULL, ",");              
    strcpy(pokemonD->ev_post,datospokemon);
    
    datospokemon = strtok(NULL, ",");               
    pokemonD->numero_pokedex=atoi(datospokemon);                   
  
    datospokemon = strtok(NULL, ",");
    strcpy(pokemonD->region,datospokemon);                    
    
    if(searchMap(pokedex_por_nombre, pokemonD->nombre)==NULL){
      pokemonD->existencia = 1;
    }else{
      Pauxiliar = searchMap(pokedex_por_nombre, pokemonD->nombre);
      pokemonD->existencia = Pauxiliar->existencia + 1;
      eraseMap(pokedex_por_nombre,&pokemonD->nombre);
      eraseMap(pokedex_por_numero,&pokemonD->numero_pokedex);
    }
   
    if(stricmp(pokemonD->nombre, "Nombre")!=0){
      insertMap(pokedex_por_nombre,&pokemonD->nombre,pokemonD);
      insertMap(pokedex_por_numero,&pokemonD->numero_pokedex,pokemonD);
      insertMap(pokemones_por_nombre,&pokemonD->nombre,pokemonI);
      insertMap(pokemones_por_id,&pokemonI->id,pokemonI);
      insertMap(pokemones_por_PC,&pokemonI->PC,pokemonI);
        if(pokemonD->existencia==1){
          insertar_por_tipos(pokemones_por_tipo, pokemonD);
        }
    }
    if (existencia>=100){
     printf("se llego a 100 pokemones antes de terminar de leer el archivo\n");
     return;
    }
    
   /*Se insertan los pokemones por tipo en la estructura correspondiente*/ 
  }
  /* Se cierra el archivo. */
  if (fclose(archivoEntrada) == EOF){
    /* Si hubo algun problema con cerrar el archivo se imprime el siguiente mensaje. */
    printf("El archivo no se pudo cerrar correctamente");
  }
}

void insertar_por_tipos(List** pokemones_por_tipo, Pokemon_pokedex* pokemonD){
  char aux1[512];
  //se copia linea
  strcpy(aux1, pokemonD->tipos);
  //se quitan ","
    
  int i, l, j;
	l = strlen(aux1);
  	for(i = 0; i < l; i++){
		if(aux1[i] == ','){
			for(j = i; j < l; j++)
			{
				aux1[j] = aux1[j + 1];
			}
			l--;
			i--;	
		} 
	}
  //se consigue primer token
    char * token = strtok(aux1, " ");
  //se compara e ingresa primer token
    if(stricmp(token, "fuego")==0){
      push_back(pokemones_por_tipo[0], pokemonD);
    }else if(stricmp(token, "agua")==0){
      push_back(pokemones_por_tipo[1], pokemonD);
    }else if(stricmp(token, "veneno")==0){
      push_back(pokemones_por_tipo[2], pokemonD);
    }else if(stricmp(token, "fantasma")==0){
      push_back(pokemones_por_tipo[3], pokemonD);
    }else if(stricmp(token, "acero")==0){
      push_back(pokemones_por_tipo[4], pokemonD);
    }else if(stricmp(token, "normal")==0){
      push_back(pokemones_por_tipo[5], pokemonD);
    }else if(stricmp(token, "electrico")==0){
      push_back(pokemones_por_tipo[6], pokemonD);
    }else if(stricmp(token, "psiquico")==0){
      push_back(pokemones_por_tipo[7], pokemonD);
    }else if(stricmp(token, "planta")==0){
      push_back(pokemones_por_tipo[8], pokemonD);
    }else if(stricmp(token, "bicho")==0){
      push_back(pokemones_por_tipo[9], pokemonD);
    }else if(stricmp(token, "tierra")==0){
      push_back(pokemones_por_tipo[10], pokemonD);
    }else if(stricmp(token, "lucha")==0){
      push_back(pokemones_por_tipo[11], pokemonD);
    }else if(stricmp(token, "roca")==0){
      push_back(pokemones_por_tipo[12], pokemonD);
    }else if(stricmp(token, "hielo")==0){
      push_back(pokemones_por_tipo[13], pokemonD);
    }else if(stricmp(token, "hada")==0){
      push_back(pokemones_por_tipo[14], pokemonD);
    }else if(stricmp(token, "siniestro")==0){
      push_back(pokemones_por_tipo[15], pokemonD);
    }else if(stricmp(token, "volador")==0){
      push_back(pokemones_por_tipo[16], pokemonD);
    }else if(stricmp(token, "dragon")==0){
      push_back(pokemones_por_tipo[17], pokemonD);
    }

    while( token != NULL ) {
      token = strtok(NULL, " ");
      if(stricmp(token, "fuego")==0){
        push_back(pokemones_por_tipo[0], pokemonD);
      }else if(stricmp(token, "agua")==0){
        push_back(pokemones_por_tipo[1], pokemonD);
      }else if(stricmp(token, "veneno")==0){
        push_back(pokemones_por_tipo[2], pokemonD);
      }else if(stricmp(token, "fantasma")==0){
        push_back(pokemones_por_tipo[3], pokemonD);
      }else if(stricmp(token, "acero")==0){
        push_back(pokemones_por_tipo[4], pokemonD);
      }else if(stricmp(token, "normal")==0){
        push_back(pokemones_por_tipo[5], pokemonD);
      }else if(stricmp(token, "electrico")==0){
        push_back(pokemones_por_tipo[6], pokemonD);
      }else if(stricmp(token, "psiquico")==0){
        push_back(pokemones_por_tipo[7], pokemonD);
      }else if(stricmp(token, "planta")==0){
        push_back(pokemones_por_tipo[8], pokemonD);
      }else if(stricmp(token, "bicho")==0){
        push_back(pokemones_por_tipo[9], pokemonD);
      }else if(stricmp(token, "tierra")==0){
        push_back(pokemones_por_tipo[10], pokemonD);
      }else if(stricmp(token, "lucha")==0){
        push_back(pokemones_por_tipo[11], pokemonD);
      }else if(stricmp(token, "roca")==0){
        push_back(pokemones_por_tipo[12], pokemonD);
      }else if(stricmp(token, "hielo")==0){
        push_back(pokemones_por_tipo[13], pokemonD);
      }else if(stricmp(token, "hada")==0){
        push_back(pokemones_por_tipo[14], pokemonD);
      }else if(stricmp(token, "siniestro")==0){
        push_back(pokemones_por_tipo[15], pokemonD);
      }else if(stricmp(token, "volador")==0){
        push_back(pokemones_por_tipo[16], pokemonD);
      }else if(stricmp(token, "dragon")==0){
        push_back(pokemones_por_tipo[17], pokemonD);
      }
    }
}

void buscar_por_tipo(List** pokemones_por_tipo){
  char linea[20];
  Pokemon_pokedex *pp;
  printf("ingrese el tipo a buscar: \n~");
  scanf("%s", &linea);
  int i;
  if(stricmp(linea, "fuego")==0){
    i = 0;
  }else if(stricmp(linea, "agua")==0){
    i = 1;
  }else if(stricmp(linea, "veneno")==0){
    i = 2;
  }else if(stricmp(linea, "fantasma")==0){
    i = 3;
  }else if(stricmp(linea, "acero")==0){
    i = 4;
  }else if(stricmp(linea, "normal")==0){
    i = 5;
  }else if(stricmp(linea, "electrico")==0){
    i = 6;
  }else if(stricmp(linea, "psiquico")==0){
    i = 7;
  }else if(stricmp(linea, "planta")==0){
    i = 8;
  }else if(stricmp(linea, "bicho")==0){
    i = 9;
  }else if(stricmp(linea, "tierra")==0){
    i = 10;
  }else if(stricmp(linea, "lucha")==0){
    i = 11;
  }else if(stricmp(linea, "roca")==0){
    i = 12;
  }else if(stricmp(linea, "hielo")==0){
    i = 13;
  }else if(stricmp(linea, "hada")==0){
    i = 14;
  }else if(stricmp(linea, "siniestro")==0){
    i = 15;
  }else if(stricmp(linea, "volador")==0){
    i = 16;
  }else if(stricmp(linea, "dragon")==0){
    i = 17;
  }
  pp = first(pokemones_por_tipo[i]);
  if(pp==NULL){
    printf("No hay pokemones de ese tipo registrados actualmente"); 
    return;}
  else{
    if(pp->existencia>0){
      printf("%s\n",pp->nombre);
    }
  }
  while ((pp = next(pokemones_por_tipo[i])) != NULL){
    if(pp->existencia > 0){
      printf("%s\n",pp->nombre);
    }
  }
}