#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum TRaza{Orco, Humano, Mago, Enano, Elfo};
char Nombres[6][10]={"ale","b","c","d","e"};
char Apellidos[6][10]={"f","g","hormiga","i","j"};

//Estructuras
struct TDatos{
	TRaza Raza;
	char* ApellidoNombre;
	int edad;
	double Salud;
};

struct TCaracteristicas{
	int velocidad;
	int destreza;
	int fuerza;
	int Nivel;
	int Armadura;
};

struct TPersonaje{
	TDatos* DatosPersonales; /*punteros ocupan solo su tamaño en la memo dinamica (X cantidad de bytes de punteros) para guardar la direccion, por eso luego se hace una reserva (a parte) para la estructura TDatos y TCaracteristicas*/
	TCaracteristicas* Caracteristicas;
};

//Declarando Funciones creadas
void cargaCarac(struct TPersonaje* ptrpers);
void mostrarCarac(struct TPersonaje* ptrpers);


//MAIN----------------------------------------------------------------------------------------------
void main(){
	struct TPersonaje* ptrpersonaje; 
	int cant,i,nump;
	
	srand(time(NULL)); /*Para que genere las semillas de nuevos numeros aleatorios rand() al ejecutar de nuevo el programa*/

	printf("INGRESE LA CANTIDAD DE PERSONAJES A CREAR: ");
	scanf("%d", &cant); printf("\n");
	/*Luego reservo memoria dinamica para tantos "cant" personajes*/
	ptrpersonaje=(struct TPersonaje*)malloc(sizeof(struct TPersonaje)*cant); //sizeof() multiplico por cant 
	
	
	for(i=0;i<cant;i++){
		/*
			Puede ir el codigo para cargar los DatosPersonales 

		*/

		/*reservo memoria dinamica (a parte) para TCaracteristicas de cada personaje*/
		(ptrpersonaje+i)->Caracteristicas=(struct TCaracteristicas*)malloc(sizeof(struct TCaracteristicas));
		
		/*Llamo a las funciones para cargar caracteristicas de cada personaje y mostrarlas*/
		cargaCarac(ptrpersonaje+i); 
		printf("Caracteristicas del personaje num %d:\n", i+1); //caracteristicas de todos los personajes (BORRAR si se hace un visor luego para el que uno escoja)
		mostrarCarac(ptrpersonaje+i);
	}
	
	
	printf("___________________________________________________\n\n");
	

	
	
	do{  
		printf("Elija un num del personaje a mostrar (del 1 al %d): ", cant); /*Parte del Visor??? preguntar como debe ser el visor*/
		scanf("%d",&nump); 
	}while(nump<0 || nump>cant); 
		
	printf("\nCaracteristicas del personaje num %d:\n", nump);
	mostrarCarac(ptrpersonaje+(nump-1));


}


//FUNCIONES CREADAS:
/*para cargar caracteristicas*/
void cargaCarac(struct TPersonaje* ptrpers){
	
	ptrpers->Caracteristicas->velocidad=rand()%10+1; 
	ptrpers->Caracteristicas->destreza=rand()%5+1;
	ptrpers->Caracteristicas->fuerza=rand()%10+1;
	ptrpers->Caracteristicas->Nivel=rand()%10+1;
	ptrpers->Caracteristicas->Armadura=rand()%10+1;

}

/*para cargar caracteristicas*/
void mostrarCarac(struct TPersonaje* ptrpers){
	
	printf("-Velocidad: %d\n",ptrpers->Caracteristicas->velocidad);	
	printf("-Destreza: %d\n",ptrpers->Caracteristicas->destreza);
	printf("-Fuerza: %d\n",ptrpers->Caracteristicas->fuerza);
	printf("-Nivel: %d\n",ptrpers->Caracteristicas->Nivel);
	printf("-Armadura: %d\n",ptrpers->Caracteristicas->Armadura);
	printf("\n");
	
}

/*Notacion solo para tener en cuenta (*(ptrpers+i)) es (ptrpers+i)-> */
