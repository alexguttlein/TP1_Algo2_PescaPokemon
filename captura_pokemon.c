#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "evento_pesca.h"


void censar(arrecife_t* arrecife){
	void (*mostrar_pokemon)(pokemon_t*) = mostrar_pokemon;
	censar_arrecife(arrecife, mostrar_pokemon);
}


bool es_rosa(pokemon_t* pokemon){
	if(strcmp(pokemon->color, "rosa") == 0){
		return true;
	}
	return false;
}


bool es_muy_rapido(pokemon_t* pokemon){
	if(pokemon->velocidad > 35){
		return true;
	}
	return false;
}


bool azul_liviano(pokemon_t* pokemon){
	if(pokemon->peso < 10 && strcmp(pokemon->color, "azul")== 0){
		return true;
	}
	return false;
}


bool seel_gordito(pokemon_t* pokemon){
	if( (strcmp(pokemon->especie, "seel") == 0) && ( pokemon->peso > 150) ) {
		return true;
	}
	return false;
}


bool es_magikarp_shinny(pokemon_t* pokemon){
	if( (strcmp(pokemon->especie, "magikarp") == 0) && (strcmp(pokemon->color, "dorado") == 0)){
		return true;
	}
	return false;
}


void realizar_traslado(arrecife_t* arrecife, acuario_t* acuario){
	int opcion;
	int cant_seleccion;

	do{
		printf("Elija pokemons a trasladar:\n");
		printf("(1) Pokemons de color rosa\n");
		printf("(2) Pokemons con velocidad mayor a 35\n");
		printf("(3) Pokemons azules de menos de 10kg\n");
		printf("(4) Pokemons de especie Seel con mas de 150 kg\n");
		printf("(5) Pokemons de especie Magikarp que sea dorado\n");
		printf("Seleccionar opcion: ");
		scanf("%i",&opcion);
	}while(opcion<1 || opcion>5 );

	printf("Elegir cantidad a trasladar: ");
	scanf("%i",&cant_seleccion);

	bool(*seleccionar_pokemon)(pokemon_t*);
	switch(opcion){
		case 1:{
			seleccionar_pokemon = es_rosa;
		}break;
		
		case 2:{
			seleccionar_pokemon = es_muy_rapido;
		}break;

		case 3:{
			seleccionar_pokemon = azul_liviano;
		}break;

		case 4:{
			seleccionar_pokemon = seel_gordito;
		}break;

		case 5:{
			seleccionar_pokemon = es_magikarp_shinny;
		}break;
	}

	
	int trasladar = trasladar_pokemon(arrecife, acuario, seleccionar_pokemon, cant_seleccion);
	if(trasladar == 0) 
		printf("el traslado fue exitoso\n");
	else printf("no se pudo trasladar\n");
}


int main(){
	arrecife_t* arrecife;
	acuario_t* acuario;
	
	arrecife = crear_arrecife("arrecife_con_1_poke.txt");
	acuario = crear_acuario();

	int cantidad, i;
	printf("Elegir cantidad de traslados a realizar: ");
	scanf("%i",&cantidad);

	for(i = 0; i < cantidad; i++){
		censar(arrecife);
		realizar_traslado(arrecife, acuario);
	}

	censar(arrecife);
	
	int guardar_acuario = guardar_datos_acuario(acuario, "acuario.txt");
	if(guardar_acuario == 0)
		printf("El acuario se guardo de forma exitosa\n");
	else printf("El acuario no pudo guardarse\n");

	liberar_acuario(acuario);
	liberar_arrecife(arrecife);

	return 0;
}