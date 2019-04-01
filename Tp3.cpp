#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TRaza{Orco, Humano, Nomo, Enano, Elfo , Draenei};
char Nombres[10][20]={"Bulbasaur", "Androide", "Militar", "Fotografo", "Sayayin","Matambre","Macaco","Judio"};
char Apellidos[10][20]={" Furioso", " Sonrriente", " Malardo", " Amargado", " Salvaje"," Calvo"," Narcotraficante"," Gordo"};

typedef struct{
	TRaza Raza; //nota 1
	char *ApellidoNombre; //nota 2
	int edad; //entre 0 a 300
	double Salud;//100
}TDatos;

typedef struct{
	int velocidad;// 1 a 10
	int destreza; //1 a 5
	int fuerza;//1 a 10
	int Nivel; //1 a 10
	int Armadura; //1 a 10
}TCaracteristicas;

typedef struct{
	TDatos * DatosPersonales;
	TCaracteristicas * Caracteristicas;
}TPersonaje;


void* Reservar_Memoria (int memoria);
void Cargar_Datos(TPersonaje* personajes,int cantpj);
void Cargar_Caract (TPersonaje* personajes,int cantpj);
void Mostrar_Personajes (TPersonaje* personajes,int cantpj);
void Mostrar_Caract (TCaracteristicas* caract);

int main(){
	srand(time(NULL));
	int cantpj;
	TPersonaje* personajes;

	printf("INGRESAR LA CANTIDAD DE PERSONAJES: ");
	scanf("%d",&cantpj);
	personajes = (TPersonaje*)Reservar_Memoria(sizeof(TPersonaje)*cantpj);

	Cargar_Datos(personajes,cantpj);
	Cargar_Caract(personajes,cantpj);
	Mostrar_Personajes(personajes,cantpj);

	return 0;
}

void Cargar_Datos(TPersonaje* personajes,int cantpj){
	srand(time(NULL));
	int i,raza,nombre,apellido;
	TDatos* datos;

	for(i=0;i<cantpj;i++){
		//Reservo memoria para la estructura datos de cada personaje.
		personajes[i].DatosPersonales = (TDatos*)Reservar_Memoria(sizeof(TDatos));
		datos = personajes[i].DatosPersonales;

		//valores aleatorios para los datos.
		raza = rand()%6;
		nombre = rand()%8;
		apellido = rand()%8;

		//Asigno los datos a la estructura.
		datos->Raza = raza;
		datos->ApellidoNombre = (char*)Reservar_Memoria( (sizeof(char)*strlen(Nombres[nombre])) + (sizeof(char)*strlen(Apellidos[apellido])) + 1);
		datos->ApellidoNombre = strcat (strcpy (datos->ApellidoNombre,Nombres[nombre]),Apellidos[apellido]);
		datos->edad=rand()%301;
		datos->Salud=100.0;
	}
	return;
}

void Cargar_Caract (TPersonaje* personajes,int cantpj){
	srand(time(NULL));
	TCaracteristicas* caract;
	int i;

	for(i=0;i<cantpj;i++){
		//Reservo memoria para la estructura de caracteristicas de cada personaje.
		personajes[i].Caracteristicas = (TCaracteristicas*)Reservar_Memoria(sizeof(TCaracteristicas));
		caract = personajes[i].Caracteristicas;

		//Asigno valores aleatorios a las caracteristicas.
		caract->velocidad = 1+rand()%(11-1);
		caract->destreza = 1+rand()%(6-1);
		caract->fuerza = 1+rand()%(11-1);
		caract->Nivel = 1+rand()%(11-1);
		caract->Armadura = 1+rand()%(11-1);
	}
	return;
}

void Mostrar_Personajes(TPersonaje* personajes,int cantpj){
	int i;
	TDatos* datos;
	TCaracteristicas* caract;
	printf("PERSONAJES:\n\n");

	for(i=0;i<cantpj;i++){
		datos = personajes[i].DatosPersonales;
		caract = personajes[i].Caracteristicas;
		//Imprimo los datos de los personajes.
		printf(" %d *********************************\n\n\t     DATOS\n\n",i+1);
		switch (datos->Raza){
			case 0 : printf("  Raza: Orco\n");
					 break;
			case 1 : printf("  Raza: Humano\n");
					 break;
			case 2 : printf("  Raza: Enano\n");
					 break;
			case 3 : printf("  Raza: Elfo\n");
					 break;
			case 4 : printf("  Raza: Nomo\n");
					 break;
			case 5 : printf("  Raza: Draenei\n");
					 break;
		}
		printf("  Apellido y nombre: %s\n  Edad: %d\n  Salud: %.1lf\n\n",datos->ApellidoNombre,datos->edad,datos->Salud);
		Mostrar_Caract(caract);
	}
	return;
}

void Mostrar_Caract (TCaracteristicas* caract){
	printf("\tCARACTERISTICAS\n\n  Velocidad: %d\n  Destreza: %d\n  Fuerza: %d\n  Nivel: %d\n  Armadura: %d\n\n",caract->velocidad,caract->destreza,caract->fuerza,caract->Nivel,caract->Armadura);
	return;
}

void* Reservar_Memoria (int memoria){
	void* punt;
	punt = malloc(memoria);
	if(memoria == NULL){
		printf("No hay memoria suficiente.");
		exit(1);
	}
	return	punt;
}
