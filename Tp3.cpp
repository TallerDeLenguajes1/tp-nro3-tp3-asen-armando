#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

enum TRaza{Asesino, Tanque, Luchador, Mago, Apoyo};

//typedef enum{Asesino, Tanque, Luchador, Mago, Apoyo}TRaza;

char Nombres[10][20]={"TORTA ", "ACELGA ", "GALLETA ", "EMPANADA ", "SOPA ", "PIZAA ", "TORTILLA "};
char Apellidos[10][20]={"FURIOSA", "ENOJADA","ASESINA", "DESTRIPADORA", "DEL MAL", "ESQUIZOFRENICA", "PERONISTA"};


/***********************ESTRUCTURAS***********************/

typedef struct{
	TRaza raza;
	char *ApellidoNombre;
	int edad;
	double salud;
}Datos;


typedef struct{
	int velocidad;
	int destreza;
	int fuerza;
	int nivel;
	int armadura;
}Caracteristicas;


typedef struct nodo{
	Datos *DatosPersonales;
	Caracteristicas *Caract;
	int aux;
	nodo * siguiente;
}Personaje;


/***********************DECLARACION FUNCIONES***********************/
void MostrarPersonajes(Personaje * pj, int cant);
void CargarDatos(Personaje * pj, int i);
void CargarCarcteristicas(Personaje * pj, int i);
void MostrarDatos(Personaje * pj, int i);
void MostrarCarcteristicas(Personaje * pj, int i);
void Batalla(Personaje pj1, Personaje pj2);
void VisorPersonaje(Personaje * pj, int i);
void Versus();
void Ataque(int pj1, int pj2);

/***********************PROGRAMA PRINCIPAL***********************/

void main(){
	highvideo();
	srand(time(NULL));

	Personaje* pj;
	int cant, pj1, pj2;

	printf("*Ingrese la cantidad de personajes aleatorios a crear: ");
	scanf("%i",&cant);
	pj = (Personaje*)malloc(sizeof(Personaje)*cant);

	printf("\n\n*Personajes disponibles: \n");
	MostrarPersonajes(pj,cant);

	printf("\n\n* Eliga 2 personajes para luchar entre si\n");
	printf("\tIngrese el numero del primer personaje: ");
	scanf("%i",&pj1);
	printf("\tIngrese el numero del segundo personaje: ");
	scanf("%i",&pj2);


	printf("\n\n* Personajes Elegidos: \n");
	VisorPersonaje(pj,pj1-1);
	Versus();
	VisorPersonaje(pj,pj2-1);
	printf("\n\n");
	Batalla(pj[pj1-1],pj[pj2-1]);
}


/***********************FUNCIONES***********************/

void CargarDatos(Personaje * pj, int i){
	//srand(time(NULL));
	Datos *data;
	int rand_raza, rand_nombre, rand_apellido, rand_edad;

	rand_raza=random(5);
	rand_nombre=random(7);
	rand_apellido=random(7);
	rand_edad=random(300);

	pj[i].DatosPersonales = (Datos*)malloc(sizeof(Datos));
	data=pj[i].DatosPersonales;
	data->edad=rand_edad;
	data->raza= rand_raza;
	data->salud=100;
	data->ApellidoNombre= (char*)malloc( (sizeof(char)*strlen(Nombres[rand_nombre])) + (sizeof(char)*strlen(Apellidos[rand_apellido])) + 1);
	data->ApellidoNombre = strcat (strcpy (data->ApellidoNombre,Nombres[rand_nombre]),Apellidos[rand_apellido]);

	return;
}

void CargarCarcteristicas(Personaje * pj, int i){
	//srand(time(NULL));
	Caracteristicas *crt;
	int rand_speed, rand_dexterity, rand_force, rand_level, rand_armor;

	rand_speed=1+random(10);
	rand_dexterity=1+random(5);
	rand_force=1+random(10);
	rand_level=1+random(10);
	rand_armor=1+random(10);

	pj[i].Caract = (Caracteristicas*)malloc(sizeof(Caracteristicas));
	crt=pj[i].Caract;
	crt->velocidad=rand_speed;
	crt->destreza=rand_dexterity;
	crt->fuerza=rand_force;
	crt->nivel=rand_level;
	crt->armadura=rand_armor;

	return;
}

void MostrarDatos(Personaje * pj, int i){
	
	printf("\n%i-%s\n", i+1,pj[i].DatosPersonales->ApellidoNombre);
	switch(pj[i].DatosPersonales->raza){
		case 0: printf("\tRaza: Asesino\n"); break;
		case 1: printf("\tRaza: Tanque\n"); break;
		case 2: printf("\tRaza: Luchador\n"); break;
		case 3: printf("\tRaza: Mago\n"); break;
		case 4: printf("\tRaza: Apoyo\n"); break;
	}
	printf("\tEdad: %i\n", pj[i].DatosPersonales->edad);
	printf("\tSalud: %.2f\n", pj[i].DatosPersonales->salud);

	return;
}

void MostrarCarcteristicas(Personaje * pj, int i){

	printf("\tVelocidad: %i\n", pj[i].Caract->velocidad);
	printf("\tDestreza: %i\n", pj[i].Caract->destreza);
	printf("\tFuerza: %i\n", pj[i].Caract->fuerza);
	printf("\tNivel: %i\n", pj[i].Caract->nivel);
	printf("\tArmadura: %i\n", pj[i].Caract->armadura);

	return;
}


void MostrarPersonajes(Personaje * pj, int cant){
	
	for (int i = 0; i < cant; ++i){	
		CargarDatos(pj,i);
		CargarCarcteristicas(pj,i);
		MostrarDatos(pj,i);
		MostrarCarcteristicas(pj,i);
	}

	return;
}

void Batalla(Personaje pj1, Personaje pj2){
	float dmg, s2, s1;
	float PD,ED,VA,PDEF,MDP=5000;

	s2=100;
	for (int i = 0; i < 6; ++i){
		if (i%2==0){
			PD = pj1.Caract->destreza*pj1.Caract->fuerza*pj1.Caract->nivel;
			PDEF = pj2.Caract->armadura*pj2.Caract->velocidad;
			ED = (float)(1+random(100))/100;
			VA = PD * ED;
			dmg = ((VA-PDEF)/MDP)*100;
			if (dmg<0){dmg=0;}
			s2 = s2-dmg;
			printf("\nJUGADOR 1,presiones una tecla para atacar\n");
			getch();
			Ataque(1,2);
			printf("\n\t\t\tDa%co=%.2f  -  Salud Pj2=%.2f\n",164, dmg, s2);
		}else{
			s1=100;
			PD = pj2.Caract->destreza*pj2.Caract->fuerza*pj2.Caract->nivel;
			PDEF = pj1.Caract->armadura*pj1.Caract->velocidad;
			ED = (float)(1+random(100))/100;
			VA = PD * ED;
			dmg = ((VA-PDEF)/MDP)*100;
			if (dmg<0){dmg=0;}
			s1 = s1-dmg;
			printf("\nJUGADOR 2,presiones una tecla para atacar\n");
			getch();
			Ataque(2,1);
			printf("\n\t\t\tDa%co=%.2f  -  Salud Pj1=%.2f\n",164, dmg, s1);
		}
		
	}

	if (s1>s2){
		printf("\n\n\t\t\t  _____________________\n");
		printf("\t\t\t |                     |\n");
		printf("\t\t\t |  GANA EL JUGADOR 1  |");
		printf("\n\t\t\t |_____________________|\n\n\n");
	}else if(s2>s1){
		printf("\n\n\t\t\t  _____________________\n");
		printf("\t\t\t |                     |\n");
		printf("\t\t\t |  GANA EL JUGADOR 2  |");
		printf("\n\t\t\t |_____________________|\n\n\n");
	}else{
		printf("\n\n\t\t\t  _____________________\n");
		printf("\t\t\t |                     |\n");
		printf("\t\t\t |    HUBO UN EMPATE   |");
		printf("\n\t\t\t |_____________________|\n\n\n");
	}
}


void VisorPersonaje(Personaje * pj, int i){

	printf("\n \t\t\t ================================");
	printf("\n\t\t\t |\t%s \t\t\n",pj[i].DatosPersonales->ApellidoNombre);
	printf("\t\t\t |\t\t\t\t|\n", pj[i].DatosPersonales->edad);
	switch(pj[i].DatosPersonales->raza){
		case 0: printf("\t\t\t |\tRaza: Asesino \t\t|\n"); break;
		case 1: printf("\t\t\t |\tRaza: Tanque \t\t|\n"); break;
		case 2: printf("\t\t\t |\tRaza: Luchador \t\t|\n"); break;
		case 3: printf("\t\t\t |\tRaza: Mago \t\t|\n"); break;
		case 4: printf("\t\t\t |\tRaza: Apoyo \t\t|\n"); break;
	}
	printf("\t\t\t |\tEdad: %i \t\t|\n", pj[i].DatosPersonales->edad);
	printf("\t\t\t |\tSalud: %.2f \t\t|\n", pj[i].DatosPersonales->salud);
	printf("\t\t\t |\tVelocidad: %i \t\t|\n", pj[i].Caract->velocidad);
	printf("\t\t\t |\tDestreza: %i \t\t|\n", pj[i].Caract->destreza);
	printf("\t\t\t |\tFuerza: %i \t\t|\n", pj[i].Caract->fuerza);
	printf("\t\t\t |\tNivel: %i \t\t|\n", pj[i].Caract->nivel);
	printf("\t\t\t |\tArmadura: %i \t\t|\n", pj[i].Caract->armadura);
	printf("\t\t\t ================================\n");

	return;
}

void Versus(){
		printf("\t\t\t                     ___        \n");
		printf("\t\t\t        ||    ||   //   \\\\    \n");
		printf("\t\t\t        ||    ||  ||    ||      \n");
		printf("\t\t\t        ||    ||   \\\\___      \n");
		printf("\t\t\t         \\\\  //         \\\\  \n");
		printf("\t\t\t          \\\\//    ||    ||    \n");
		printf("\t\t\t           \\/      \\\\__//    \n");
	return;
}

void Ataque(int pj1, int pj2){

	printf("\n\n");
	printf("\t\t    ___                       ___      ___            ");
  printf("\t\t\t\t   (-.-)_/............  \\|/  | %i | |__(-.-)        \n",pj2);
	printf("\t\t _/|.%i.|                /|\\   \\_/     |.%i.|\\_  \n",pj1,pj2);
	printf("\t\t   _| |_                              _| |_         \n");
}