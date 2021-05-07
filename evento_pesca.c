#include "evento_pesca.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINEA 160
#define CANT_CARACTERISTICAS 4



//se lee y devuelve una linea del archivo 
int leer_archivo(FILE *archivo, pokemon_t *poke){
	int lectura = fscanf(archivo, "%[^;];%i;%i;%[^\n]\n", poke->especie, &(poke->velocidad), &(poke->peso), poke->color);
	return lectura;
}


//recive un puntero a una cadena de texto y verifica si la misma tiene una extension .txt o .csv
//devuelve true si es asi, o false si es otro tipo de extension.
bool validar_extension_archivo(const char* ruta_archivo){
	int i = 0;

	while(ruta_archivo[i] != '.'){
		i++;
	}
	
	int j;
	int k = 0;
	char extension[10]= "zzz";
	
	for(j=i+1; j<strlen(ruta_archivo); j++){
		extension[k] = ruta_archivo[j];
		k++;
	}
	
	if((strcmp(extension, "txt") != 0) && (strcmp(extension, "csv") != 0)){
		return false;
	}

	return true;
}



arrecife_t* crear_arrecife(const char* ruta_archivo){
	
	if (!validar_extension_archivo(ruta_archivo)){
		return NULL;
	}

	FILE *archivo = fopen(ruta_archivo, "r");
	if(!archivo) {
		return NULL;
	}
	
	arrecife_t* arrecife = (arrecife_t*)malloc(sizeof(arrecife_t));
	if (!arrecife) return NULL;

	arrecife->cantidad_pokemon = 0;

	//se crea el vector de punteros y se inicializa
	arrecife->pokemon = malloc(sizeof(pokemon_t));
	if(!arrecife->pokemon){
		free(arrecife);
		return NULL;
	}
	
	strcpy(arrecife->pokemon->especie, "");
	arrecife->pokemon->peso = 0;
	arrecife->pokemon->velocidad = 0;
	strcpy(arrecife->pokemon->color, "");
	
	pokemon_t* pokemon = (pokemon_t*)malloc(sizeof(pokemon_t));

	//se lee una linea del archivo
	int leer_linea = leer_archivo(archivo, pokemon);
	int posicion = 0;

	if(leer_linea != CANT_CARACTERISTICAS){
		free(pokemon);
		fclose(archivo);
		return NULL;
	}
	while(leer_linea == CANT_CARACTERISTICAS){

		arrecife->cantidad_pokemon++;
		pokemon_t* pokemon_aux = (pokemon_t*)realloc(arrecife->pokemon, (sizeof(pokemon_t)) * (long unsigned int)(arrecife->cantidad_pokemon));
		if(!pokemon_aux){
			free(pokemon);
			fclose(archivo);
			return arrecife;
		}

		arrecife->pokemon = pokemon_aux;

		strcpy(arrecife->pokemon[posicion].especie , pokemon->especie);
		arrecife->pokemon[posicion].velocidad = pokemon->velocidad;
		arrecife->pokemon[posicion].peso = pokemon->peso;
		strcpy(arrecife->pokemon[posicion].color , pokemon->color);
	
		leer_linea = leer_archivo(archivo, pokemon);
		
		posicion++;
	}

	free(pokemon);
	fclose(archivo);
	return arrecife;
}



acuario_t* crear_acuario(){
	acuario_t* acuario;
	acuario = (acuario_t*)calloc(1,sizeof(acuario_t));
	if(!acuario){
		return NULL;
	}
	return acuario;
}



void liberar_acuario(acuario_t* acuario){
	if(acuario->pokemon)
		free(acuario->pokemon);
	if(acuario)
		free(acuario);
}



void liberar_arrecife(arrecife_t* arrecife){
	if(arrecife->pokemon)
		free(arrecife->pokemon);
	if(arrecife)
		free(arrecife);
}



//elimina un pokemon del arrecife
//recibe un arrecife, su cantidad de pokemones y la posicion del vector de pokemones que se desea eliminar
//se elimina el pokemon del arrecife y se modifica su cantidad
//devuelve 0 si se elimino con exito o -1 si no se pudo eliminar
int eliminar_pokemon(pokemon_t* pokemon, int posicion, int cantidad_arrecife){
	int i;
	for(i=posicion; i<cantidad_arrecife-1; i++){
		strcpy(pokemon[i].especie ,pokemon[i+1].especie);
		pokemon[i].velocidad = pokemon[i+1].velocidad;
		pokemon[i].peso = pokemon[i+1].peso;
		strcpy(pokemon[i].color ,pokemon[i+1].color);
	}
	return 0;
}



int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){
	int i, eliminar;
	int disponibles = 0;

	if(!arrecife) return -1;

	if(!acuario) return -1;

	for (i=0; i<arrecife->cantidad_pokemon; i++){
		if(seleccionar_pokemon(arrecife->pokemon+i)){
			disponibles+=1;
		}
	}
	
	if(disponibles < cant_seleccion){
		return -1;
	}

	int trasladados = 0;

	for (i=0; (i < arrecife->cantidad_pokemon) && (trasladados < cant_seleccion); i++){

		if(seleccionar_pokemon(arrecife->pokemon+i)){
			pokemon_t* pokemon_aux = (pokemon_t*)realloc(acuario->pokemon, sizeof(pokemon_t) * (long unsigned int)(acuario->cantidad_pokemon+1));
			if(!pokemon_aux){
				return -1;
			}

			acuario->pokemon = pokemon_aux;

			strcpy(acuario->pokemon[acuario->cantidad_pokemon].especie , arrecife->pokemon[i].especie);
			acuario->pokemon[acuario->cantidad_pokemon].velocidad = arrecife->pokemon[i].velocidad;
			acuario->pokemon[acuario->cantidad_pokemon].peso = arrecife->pokemon[i].peso;
			strcpy(acuario->pokemon[acuario->cantidad_pokemon].color , arrecife->pokemon[i].color);
			acuario->cantidad_pokemon++;
			
			eliminar = eliminar_pokemon(arrecife->pokemon, i, (arrecife->cantidad_pokemon - trasladados));
			if(eliminar == 0){
				trasladados ++;
			}
		}
	}

	arrecife->cantidad_pokemon = arrecife->cantidad_pokemon - trasladados;
	arrecife->pokemon = (pokemon_t*) realloc(arrecife->pokemon, sizeof(pokemon_t) * (long unsigned int)(arrecife->cantidad_pokemon));
	return 0;
}



//recibe un puntero a un pokemon e imprime por pantalla sus variables.
void mostrar_poke(pokemon_t* pokemon){
	printf("%s, %i, %i, %s\n",pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
}



void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){ 
	int i;
	if(arrecife && arrecife->pokemon){
		mostrar_pokemon = mostrar_poke;
		
		for(i=0; i < arrecife->cantidad_pokemon; i++){
			mostrar_pokemon(arrecife->pokemon+i);
			}
		}
}



int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){
	if(!acuario) return -1;

	FILE *archivo_acuario;
	archivo_acuario = fopen(nombre_archivo,"w");
	if(!archivo_acuario){
		return -1;
	}

	int i = 0;
	while(i < acuario->cantidad_pokemon){		
		fprintf(archivo_acuario, "%s;%i;%i;%s\n", acuario->pokemon[i].especie, acuario->pokemon[i].velocidad, acuario->pokemon[i].peso, acuario->pokemon[i].color);
		i++;
	}
	fclose(archivo_acuario);
	return 0;
}