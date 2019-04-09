#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

enum TRaza{Asesino, Tanque, Luchador, Mago, Apoyo};
char Nombres[10][20]={"GALLETA ", "EMPANADA ", "SOPA ", "PIZAA ", "TORTILLA "};
char Apellidos[10][20]={"ASESINA", "DESTRIPADORA", "DEL MAL", "ESQUIZOFRENICA", "PERONISTA"};


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


typedef struct{
	Datos *DatosPersonales;
	Caracteristicas *Caract;
	int aux;
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

/***********************PROGRAMA PRINCIPAL***********************/

void main(){
	highvideo();

	Personaje* pj;
	int cant, pj1, pj2;

	printf("*Ingrese la cantidad de personajes: ");
	scanf("%i",&cant);
	pj = (Personaje*)malloc(sizeof(Personaje)*cant);

	printf("\n*Personajes disponibles: \n");
	MostrarPersonajes(pj,cant);

	printf("\nEliga 2 personajes para luchar entre si\n");
	printf("\tIngrese el numero del primer personaje: ");
	scanf("%i",&pj1);
	printf("\tIngrese el numero del segundo personaje: ");
	scanf("%i",&pj2);


	printf("\r\n* %s VS %s\n\n", pj[pj1-1].DatosPersonales->ApellidoNombre, pj[pj2-1].DatosPersonales->ApellidoNombre);
	VisorPersonaje(pj,pj1-1);
	Versus();
	VisorPersonaje(pj,pj2-1);

	printf("\n* Presione una tecla para ver el resultado de la batalla\n");
	getch();
	Batalla(pj[pj1-1],pj[pj2-1]);



	// return 0;
}


/***********************FUNCIONES***********************/

void CargarDatos(Personaje * pj, int i){
	Datos *data;
	int rand_raza, rand_nombre, rand_apellido, rand_edad;

	rand_raza=rand()%5;
	rand_nombre=rand()%5;
	rand_apellido=rand()%5;
	rand_edad=rand()%300;

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
	Caracteristicas *crt;
	int rand_speed, rand_dexterity, rand_force, rand_level, rand_armor;

	rand_speed=1+rand()%11;
	rand_dexterity=1+rand()%6;
	rand_force=1+rand()%10;
	rand_level=1+rand()%10;
	rand_armor=1+rand()%10;

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
	
	cprintf("\r\n%i-%s\n", i+1,pj[i].DatosPersonales->ApellidoNombre);
	switch(pj[i].DatosPersonales->raza){
		case 0: cprintf("\r   Raza: Asesino\n"); break;
		case 1: cprintf("\r   Raza: Tanque\n"); break;
		case 2: cprintf("\r   Raza: Luchador\n"); break;
		case 3: cprintf("\r   Raza: Mago\n"); break;
		case 4: cprintf("\r   Raza: Apoyo\n"); break;
	}
	cprintf("\r   Edad: %i\n", pj[i].DatosPersonales->edad);
	cprintf("\r   Salud: %.2f\n", pj[i].DatosPersonales->salud);

	return;
}

void MostrarCarcteristicas(Personaje * pj, int i){

	cprintf("\r   Velocidad: %i\n", pj[i].Caract->velocidad);
	cprintf("\r   Destreza: %i\n", pj[i].Caract->destreza);
	cprintf("\r   Fuerza: %i\n", pj[i].Caract->fuerza);
	cprintf("\r   Nivel: %i\n", pj[i].Caract->nivel);
	cprintf("\r   Armadura: %i\n", pj[i].Caract->armadura);

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
	for (int i = 0; i < 3; ++i)
	{
		PD = pj1.Caract->destreza*pj1.Caract->fuerza*pj1.Caract->nivel;
		PDEF = pj2.Caract->armadura*pj2.Caract->velocidad;
		ED = (float)(1+rand()%(101-1))/100;
		VA = PD * ED;
		dmg = ((VA-PDEF)/MDP)*100;
		if (dmg<0){dmg=0;}
		s2 = s2-dmg;
		printf("\nPj1-Turno %i: Dmg=%.2f - Salud Pj2=%.2f", i+1, dmg, s2);
	}

	s1=100;
	printf("\n");

	for (int i = 0; i < 3; ++i)
	{
		PD = pj2.Caract->destreza*pj2.Caract->fuerza*pj2.Caract->nivel;
		PDEF = pj1.Caract->armadura*pj1.Caract->velocidad;
		ED = (float)(1+rand()%(101-1))/100;
		VA = PD * ED;
		dmg = ((VA-PDEF)/MDP)*100;
		if (dmg<0){dmg=0;}
		s1 = s1-dmg;
		printf("\nPj2-Turno %i: Dmg=%.2f - Salud Pj1=%.2f", i+1, dmg, s1);
	}

	if (s1>s2){
		printf("\n\nGANA EL JUGADOR 1\n");
	}else if(s2>s1){
		printf("\n\nGANA EL JUGADOR 2\n");
	}else{
		printf("\n\nHUBO UN EMPATE\n");
	}
}


void VisorPersonaje(Personaje * pj, int i){

	printf("\n \t\t ================================\n");
	printf("\r\n\t\t |\t%s \t\t\n",pj[i].DatosPersonales->ApellidoNombre);
	switch(pj[i].DatosPersonales->raza){
		case 0: printf("\r\t\t |\tRaza: Asesino \t\t|\n"); break;
		case 1: printf("\r\t\t |\tRaza: Tanque \t\t|\n"); break;
		case 2: printf("\r\t\t |\tRaza: Luchador \t\t|\n"); break;
		case 3: printf("\r\t\t |\tRaza: Mago \t\t|\n"); break;
		case 4: printf("\r\t\t |\tRaza: Apoyo \t\t|\n"); break;
	}
	printf("\r\t\t |\tEdad: %i \t\t|\n", pj[i].DatosPersonales->edad);
	printf("\r\t\t |\tSalud: %.2f \t\t|\n", pj[i].DatosPersonales->salud);
	printf("\r\t\t |\tVelocidad: %i \t\t|\n", pj[i].Caract->velocidad);
	printf("\r\t\t |\tDestreza: %i \t\t|\n", pj[i].Caract->destreza);
	printf("\r\t\t |\tFuerza: %i \t\t|\n", pj[i].Caract->fuerza);
	printf("\r\t\t |\tNivel: %i \t\t|\n", pj[i].Caract->nivel);
	printf("\r\t\t |\tArmadura: %i \t\t|\n", pj[i].Caract->armadura);
	printf("\n\t\t ================================\n\n");

	return;
}

void Versus(){

	printf("\n\n\r\t\t     ||        ||        ====            \n");
		printf("\r\t\t     ||        ||      //    \\\\       \n");
		printf("\r\t\t     ||        ||     //      \\\\    \n");
		printf("\r\t\t     ||        ||     \\\\           \n");
		printf("\r\t\t     ||        ||      \\\\         \n");
		printf("\r\t\t     ||        ||       \\\\       \n");
		printf("\r\t\t      \\\\      //          \\\\     \n");
		printf("\r\t\t       \\\\    //            \\\\   \n");
		printf("\r\t\t        \\\\  //              // \n");
		printf("\r\t\t         \\\\//       \\\\     //\n");
		printf("\r\t\t          \\/          =====\n");
		printf("\n\n");

	
	

	return;
}