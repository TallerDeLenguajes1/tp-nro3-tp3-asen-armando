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
void visorPers(struct TPersonaje* ptrpers, int cantpers);
void pelea(struct TPersonaje* ptrpers, int cantpers);


//MAIN------------------------------------------------------------------------------------------------------
void main(){
	struct TPersonaje* ptrpersonaje; 
	int cant,i;
	
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

	/*probando funcion visor de personaje*/
 	visorPers(ptrpersonaje, cant);	
		
 	/*probando funcion pelea personajes*/
 	pelea(ptrpersonaje, cant);

}


//FUNCIONES CREADAS:
//para cargar caracteristicas
void cargaCarac(struct TPersonaje* ptrpers){
	
	ptrpers->Caracteristicas->velocidad=rand()%10+1; 
	ptrpers->Caracteristicas->destreza=rand()%5+1;
	ptrpers->Caracteristicas->fuerza=rand()%10+1;
	ptrpers->Caracteristicas->Nivel=rand()%10+1;
	ptrpers->Caracteristicas->Armadura=rand()%10+1;

}

//para mostrar caracteristicas
void mostrarCarac(struct TPersonaje* ptrpers){
	
	printf("-Velocidad: %d\n",ptrpers->Caracteristicas->velocidad);	
	printf("-Destreza: %d\n",ptrpers->Caracteristicas->destreza);
	printf("-Fuerza: %d\n",ptrpers->Caracteristicas->fuerza);
	printf("-Nivel: %d\n",ptrpers->Caracteristicas->Nivel);
	printf("-Armadura: %d\n",ptrpers->Caracteristicas->Armadura);
	printf("\n");
	
}

//Visor de personaje?? (Preguntar como debe ser el visor)
void visorPers(struct TPersonaje* ptrpers, int cantpers){ 
	int nump;
	
	do{  
		printf("Elija un num del personaje a mostrar (del 1 al %d): ", cantpers); 
		scanf("%d",&nump); 
	}while(nump<1 || nump>cantpers); 

	/*
		Puede ir el codigo para mostrar DatosPersonales del personaje 

	*/
	printf("\nCaracteristicas del personaje num %d:\n", nump);
	mostrarCarac(ptrpers+(nump-1));
}


//Funcion pelea 
void pelea(struct TPersonaje* ptrpers, int cantpers){
	struct TPersonaje* personajeA; struct TPersonaje* personajeB;
	int PDpersA, EDpersA, VApersA, PDEFpersA, PDpersB, EDpersB, VApersB, PDEFpersB;
	int nump,i,ataques=3, MDP=50000, danioataqA, danioataqB, saludpersA=100000, saludpersB=100000;

	/*Seleccionando personajes*/
	do{  
		printf("Seleccione el personaje A (del 1 al %d): ", cantpers); 
		scanf("%d",&nump); 
	}while(nump<1 || nump>cantpers);

	personajeA=ptrpers+(nump-1);
	
	do{  
		printf("Seleccione el personaje B (del 1 al %d): ", cantpers); 
		scanf("%d",&nump); 
	}while(nump<1 || nump>cantpers);

	personajeB=ptrpers+(nump-1);
	
	/*Valores de ataque*/
	PDpersA=(personajeA->Caracteristicas->destreza)*(personajeA->Caracteristicas->fuerza)*(personajeA->Caracteristicas->Nivel);
	
	PDpersB=(personajeB->Caracteristicas->destreza)*(personajeB->Caracteristicas->fuerza)*(personajeB->Caracteristicas->Nivel);
	
	/*Valores de defensa*/
	PDEFpersA=(personajeA->Caracteristicas->Armadura)*(personajeA->Caracteristicas->velocidad);
	printf("%d\n", PDEFpersA);
	PDEFpersB=(personajeB->Caracteristicas->Armadura)*(personajeB->Caracteristicas->velocidad);
	printf("%d\n", PDEFpersB);
	
	/*Ataques realizados de cada personaje*/
	printf("___________________________________________________\n\n");
	for(i=0;i<ataques;i++){
		printf("\nAtaque nro %d\n",i+1);

		EDpersA=rand()%100+1; /*random en Efectividad del disparo personajeA*/
		VApersA=PDpersA*EDpersA;
		printf("Ataque personaje A %d\n", VApersA);

		EDpersB=rand()%100+1; /*random en Efectividad del disparo personajeB*/
		VApersB=PDpersB*EDpersB;
		printf("Ataque personaje B %d\n", VApersB);
		
		/*Falta arreglar los valores y agregar mas codigo para optimizar el tema de cuando llegue a 0 la salud etc*/
		danioataqB=(VApersB-PDEFpersA)*10; //Arreglar estos valores y agregar mas codigo para optimizar el tema de cuando llegue a 0 la salud etc
		printf("Danio del ataque de personaje B a A:%d\n", danioataqB);
		saludpersA=saludpersA-danioataqB;
		printf("Salud personaje A:%d\n", saludpersA);

		danioataqA=(VApersA-PDEFpersB)*10; //Arreglar estos valores y agregar mas codigo para optimizar el tema de cuando llegue a 0 la salud etc
		printf("Danio del ataque de personaje A a B:%d\n", danioataqA);
		saludpersB=saludpersB-danioataqA;
		printf("Salud personaje B:%d\n", saludpersB);

	}
	
	printf("\n");
	printf("Salud personaje A:%d\n", saludpersA); 
	printf("Salud personaje B:%d\n", saludpersB);
}

/*Notacion solo para tener en cuenta (*(ptrpers+i)) es (ptrpers+i)-> */
