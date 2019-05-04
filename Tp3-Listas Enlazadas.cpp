#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

enum TRaza{Asesino, Tanque, Luchador, Mago, Apoyo};

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


typedef struct Tnodo{
	Datos *DatosPersonales;
	Caracteristicas *Caract;
	int nro_pj;
	Tnodo * next;
}Tnodo;

/***********************DECLARACION FUNCIONES***********************/
Tnodo * Crear_lista();
int Es_lista_vacia(Tnodo * l);
Tnodo * CrearNodo(int i);
void InsertarNodo(Tnodo ** l,int nro_pj);






Tnodo * EliminarNodo(Tnodo * l);
Tnodo * QuitarPersonaje(Tnodo * l,int posicion);
Tnodo * Crear_Lista_Personajes(Tnodo * l, int cant);

Tnodo * Insertar_elemento(Tnodo * l, int i);
Datos * CargarDatos(Datos * DP);
Caracteristicas * CargarCarcteristicas(Caracteristicas * CP);
void MostrarDatos(Tnodo * l);
void MostrarCarcteristicas(Tnodo * l);
void Mostrar_lista(Tnodo * l);
void VisorPersonaje(Tnodo * l, int buscado);
void Versus();
void Batalla(Tnodo * l, int pj1, int pj2);
void Ataque(int pj1, int pj2);

/***********************PROGRAMA PRINCIPAL***********************/

void main(){
	highvideo();
	srand(time(NULL));
	int cant, pj1, pj2,a_elminar;

	Tnodo * l;
	l=Crear_lista();


	//***************** CREAR LISTA CON cant PERSONAJES *********************//
	printf("*Ingrese la cantidad de personajes aleatorios a crear: ");
	scanf("%i",&cant);

	for(int i=cant;i>0;i--){
		InsertarNodo(&l,i);
	}

	//************* MOSTRAR LISTA CON PERSONAJES ****************//
	Mostrar_lista(l);

	//********** ELEGIR DOS PERSONAJES PARA PELEAR **************//
	printf("\n\n* Eliga 2 personajes para luchar entre si\n");
	do{
		printf("\tIngrese el numero del primer personaje: ");
		scanf("%i",&pj1);
	}while (pj1<=0 || pj1>cant);
	printf("\n");
	do{
		printf("\tIngrese el numero del segundo personaje: ");
		scanf("%i",&pj2);
	}while (pj2<=0 || pj2>cant);

	//***************** VISOR DE PERSONAJES ********************//
	printf("\n\n* Personajes Elegidos: \n");
	VisorPersonaje(l,pj1);
	Versus();
	VisorPersonaje(l,pj2);
	printf("\n\n");

	//********************** BATALLA **************************//
	bBatalla(l,pj1,pj2);
}


/***********************FUNCIONES***********************/

Tnodo* Crear_lista(){
	return NULL;
}

int Es_lista_vacia(Tnodo * l){
	if(l==NULL){
		return 1;
	}else{
		return 0;
	}
}

Tnodo * CrearNodo(int i){
	Datos *DP;
	Caracteristicas *CP;

	Tnodo * nuevo=(Tnodo *) malloc(sizeof(Tnodo));
	nuevo->DatosPersonales= CargarDatos(DP);
	nuevo->Caract= CargarCarcteristicas(CP);
	nuevo->nro_pj=i;
	nuevo->next=NULL;
	return nuevo;
}

void InsertarNodo(Tnodo ** l,int nro_pj){
	Tnodo * nuevo=CrearNodo(nro_pj);
	nuevo->next=*l;
	*l=nuevo;
}

void Mostrar_lista(Tnodo * l){
	printf("\n\n*Personajes disponibles: \n");
	if(Es_lista_vacia(l)!=1){
		while(Es_lista_vacia(l) != 1){
			printf("\n%i -", l->nro_pj);
			MostrarDatos(l);
			MostrarCarcteristicas(l);
			l=l->next;
		}
		printf("\n");
	}else{
		printf("\n\nLista Vacia \n");
	}
}


Datos * CargarDatos(Datos * DP){
	int rand_raza, rand_nombre, rand_apellido, rand_edad;

	rand_raza=random(5);
	rand_nombre=random(7);
	rand_apellido=random(7);
	rand_edad=random(300);

	DP = (Datos*)malloc(sizeof(Datos));
	DP->edad=rand_edad;
	DP->raza= rand_raza;
	DP->salud=100;
	DP->ApellidoNombre= (char*)malloc( (sizeof(char)*strlen(Nombres[rand_nombre])) + (sizeof(char)*strlen(Apellidos[rand_apellido])) + 1);
	DP->ApellidoNombre = strcat (strcpy (DP->ApellidoNombre,Nombres[rand_nombre]),Apellidos[rand_apellido]);

	return DP;
}

Caracteristicas * CargarCarcteristicas(Caracteristicas *CP){
	int rand_speed, rand_dexterity, rand_force, rand_level, rand_armor;

	rand_speed=1+random(10);
	rand_dexterity=1+random(5);
	rand_force=1+random(10);
	rand_level=1+random(10);
	rand_armor=1+random(10);

	CP = (Caracteristicas*)malloc(sizeof(Caracteristicas));
	CP->velocidad=rand_speed;
	CP->destreza=rand_dexterity;
	CP->fuerza=rand_force;
	CP->nivel=rand_level;
	CP->armadura=rand_armor;

	return CP;
}


void MostrarDatos(Tnodo * l){
	printf(" %s\n",l->DatosPersonales->ApellidoNombre);
	switch(l->DatosPersonales->raza){
		case 0: printf("\tRaza: Asesino\n"); break;
		case 1: printf("\tRaza: Tanque\n"); break;
		case 2: printf("\tRaza: Luchador\n"); break;
		case 3: printf("\tRaza: Mago\n"); break;
		case 4: printf("\tRaza: Apoyo\n"); break;
	}
	printf("\tEdad: %i\n", l->DatosPersonales->edad);
	printf("\tSalud: %.2f\n", l->DatosPersonales->salud);

	return;
}

void MostrarCarcteristicas(Tnodo * l){
	printf("\tVelocidad: %i\n", l->Caract->velocidad);
	printf("\tDestreza: %i\n", l->Caract->destreza);
	printf("\tFuerza: %i\n", l->Caract->fuerza);
	printf("\tNivel: %i\n", l->Caract->nivel);
	printf("\tArmadura: %i\n", l->Caract->armadura);

	return;
}

void VisorPersonaje(Tnodo * l, int buscado){

	while(Es_lista_vacia(l) != 1){
		if (l->nro_pj==buscado){
			printf("\n \t\t\t ================================");
			printf("\n\t\t\t |\t%s \t\t\n",l->DatosPersonales->ApellidoNombre);
			printf("\t\t\t |\t\t\t\t|\n", l->DatosPersonales->edad);
			switch(l->DatosPersonales->raza){
				case 0: printf("\t\t\t |\tRaza: Asesino \t\t|\n"); break;
				case 1: printf("\t\t\t |\tRaza: Tanque \t\t|\n"); break;
				case 2: printf("\t\t\t |\tRaza: Luchador \t\t|\n"); break;
				case 3: printf("\t\t\t |\tRaza: Mago \t\t|\n"); break;
				case 4: printf("\t\t\t |\tRaza: Apoyo \t\t|\n"); break;
			}
			printf("\t\t\t |\tEdad: %i \t\t|\n", l->DatosPersonales->edad);
			printf("\t\t\t |\tSalud: %.2f \t\t|\n", l->DatosPersonales->salud);
			printf("\t\t\t |\tVelocidad: %i \t\t|\n", l->Caract->velocidad);
			printf("\t\t\t |\tDestreza: %i \t\t|\n", l->Caract->destreza);
			printf("\t\t\t |\tFuerza: %i \t\t|\n", l->Caract->fuerza);
			printf("\t\t\t |\tNivel: %i \t\t|\n", l->Caract->nivel);
			printf("\t\t\t |\tArmadura: %i \t\t|\n", l->Caract->armadura);
			printf("\t\t\t ================================\n");
		}
		l=l->next;
	}
	printf("\n");

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


void Batalla(Tnodo * l, int pj1, int pj2){
	float dmg, s2, s1;
	float PD,ED,VA,PDEF,MDP=5000;
	Tnodo *l1, *l2;

	while(Es_lista_vacia(l) != 1){
		if (l->nro_pj==pj1){
			l1=l;
		}
		if (l->nro_pj==pj2){
			l2=l;
		}
		l=l->next;
	}
	s2=100;s1=100;
	for (int i = 0; i < 6; ++i){
		if (i%2==0){
			PD = l1->Caract->destreza*l1->Caract->fuerza*l1->Caract->nivel;
			PDEF = l2->Caract->armadura*l2->Caract->velocidad;
			ED = (float)(1+random(100))/100;
			VA = PD * ED;
			dmg = ((VA-PDEF)/MDP)*100;
			if (dmg<0){dmg=0;}
			s2 = s2-dmg;
			//printf("\n%s ataca a %s\n",l1->DatosPersonales->ApellidoNombre, l2->DatosPersonales->ApellidoNombre);
			printf("\nJUGADOR 1,presiona una tecla para atacar\n");
			getch();
			Ataque(1,2);
			printf("\n\t\t\tDa%co=%.2f  -  Salud Pj2=%.2f\n",164, dmg, s2);
		}else{
			PD = l2->Caract->destreza*l2->Caract->fuerza*l2->Caract->nivel;
			PDEF = l1->Caract->armadura*l1->Caract->velocidad;
			ED = (float)(1+random(100))/100;
			VA = PD * ED;
			dmg = ((VA-PDEF)/MDP)*100;
			if (dmg<0){dmg=0;}
			s1 = s1-dmg;
			//printf("\n%s ataca a %s\n",l2->DatosPersonales->ApellidoNombre, l1->DatosPersonales->ApellidoNombre);
			printf("\nJUGADOR 2,presiona una tecla para atacar\n");
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


void Ataque(int pj1, int pj2){

	printf("\n\n");
	printf("\t\t    ___                     ___      ___            ");
  printf("\t\t\t\t   (-.-)_/............\\|/  | %i | |__(-.-)        \n",pj2);
	printf("\t\t _/|.%i.|              /|\\   \\_/     |.%i.|\\_  \n",pj1,pj2);
	printf("\t\t   _| |_                            _| |_         \n");
}