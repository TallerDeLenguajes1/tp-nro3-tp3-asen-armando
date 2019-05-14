#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define indef -999;

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
void QuitarNodoDeUnaPosicion(Tnodo **l, int posicion);
void EliminarNodo(Tnodo *nodo);
Tnodo* BuscarNodo(Tnodo *l, int buscado);
char* Buffear(Tnodo **l, int posicion);
int PersonajesDisponibles(Tnodo **l);


Datos * CargarDatos(Datos * DP);
Caracteristicas * CargarCarcteristicas(Caracteristicas * CP);
void MostrarDatos(Tnodo * l);
void MostrarCarcteristicas(Tnodo * l);
void Mostrar_lista(Tnodo * l);
void Mostrar_Nodo(Tnodo * l);
void VisorPersonaje(Tnodo * l, int buscado);
void Versus();
void Batalla(Tnodo * l, int pj1, int pj2, int resultado[2]);
void Ataque(int pj1, int pj2);

/***********************PROGRAMA PRINCIPAL***********************/

void main(){
	highvideo();
	srand(time(NULL));
	int cant, pj1, pj2,buscar,resultado[2];

	Tnodo * l;
	l=Crear_lista();


	//***************** CREAR LISTA CON cant PERSONAJES *********************//
	printf("\n\n\t_\\|/_\t OLIMPIADAS ALIMENTICIAS 2019\t_\\|/_");
	printf("\n\t /|\\\t\t\t\t\t /|\\\n\n");
	printf("\n Ingrese la cantidad de personajes que participaran en el torneo: ");
	scanf("%i",&cant);

	for(int i=0;i<cant;i++){
		InsertarNodo(&l,i);
	}
	
	//************* MOSTRAR LISTA CON PERSONAJES ****************//
	Mostrar_lista(l);

	while(PersonajesDisponibles(&l)>=2){

		if(PersonajesDisponibles(&l)==2 && resultado[0]!=-999){
			printf("\n\n\t\t\t**** GRAN FINAL ENTRE PJ%i Y PJ%i ***\n", l->nro_pj, (l->next)->nro_pj);

			//***************** VISOR DE PERSONAJES ********************//
			VisorPersonaje(l,l->nro_pj);
			Versus();
			VisorPersonaje(l,(l->next)->nro_pj);
			printf("\n\n");

			//********************** BATALLA **************************//
			Batalla(l,l->nro_pj,(l->next)->nro_pj,resultado);
			
			if(resultado[0]!=-999){
				printf("\n\n\t\t\t_\\|/_\t GANA EL TORNEO EL PJ%i\t_\\|/_", resultado[0]);
				printf("\n\t\t\t /|\\\t\t\t\t /|\\\n\n");
				QuitarNodoDeUnaPosicion(&l,resultado[1]);
			}else{
				printf("\n\nHUBO UN EMPATE\n");
			}
		}else{

			//********** ELEGIR DOS PERSONAJES PARA PELEAR **************//
			printf("\n\n Eliga 2 personajes para luchar entre si\n\n");
			printf("\tIngrese el numero del primer personaje: ");
			scanf("%i",&pj1);
			printf("\n");
			printf("\tIngrese el numero del segundo personaje: ");
			scanf("%i",&pj2);

			//***************** VISOR DE PERSONAJES ********************//
			printf("\n\n Personajes Elegidos: \n");
			VisorPersonaje(l,pj1);
			Versus();
			VisorPersonaje(l,pj2);
			printf("\n\n");

			//********************** BATALLA **************************//
			Batalla(l,pj1,pj2,resultado);
			char* to_buff=Buffear(&l,resultado[0]);
			if(resultado[0]!=-999){
				printf("\n\n Recibe mejoras el pj %i (Buf de %s)",resultado[0],to_buff);
				printf("\n Elminado del torneo el pj %i\n\n",resultado[1]);
				QuitarNodoDeUnaPosicion(&l,resultado[1]);
			}else{
				printf("\n\nNo hay buffs ni eliminaciones que hacer\n");
			}

			//LIMPIAR PANTALLA
			printf("\nPresiona una tecla para avanzar a la siguiente fase del torneo\n");
			getch();
			system("@cls||clear");

			Mostrar_lista(l);

		}

		
		

		
	}
	
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
	Tnodo * nuevo=CrearNodo(nro_pj+1);
	nuevo->next=*l;
	*l=nuevo;
}

void QuitarNodoDeUnaPosicion(Tnodo **l, int posicion){

	Tnodo* ANT = NULL;
	Tnodo* AUX = *l;

	while( AUX != NULL ){
		if( AUX->nro_pj == posicion ){
			if ( ANT == NULL ){
				*l = AUX->next;
			}else{
				ANT->next = AUX->next;
			}
			EliminarNodo(AUX);
			AUX = ANT->next;
			break;
		}else{
			ANT = AUX;
			AUX = AUX->next;
		}
	}
}

void EliminarNodo(Tnodo *nodo){
	if (!nodo){
		free(nodo);
	}
}


Tnodo* BuscarNodo(Tnodo *l, int buscado){
	Tnodo* AUX = l;

	while(AUX->nro_pj!=buscado && AUX){
		AUX = AUX->next;
	}

	return AUX;
}

char* Buffear(Tnodo **l, int posicion){
	Tnodo* AUX = *l;
	char* modificado;

	while(AUX->nro_pj!=posicion && AUX && posicion!=-999){
		AUX = AUX->next;
	}


	int to_buff=random(6);

	if(posicion!=-999){
		AUX->DatosPersonales->ApellidoNombre = strcat (AUX->DatosPersonales->ApellidoNombre," (BUFFED)");
		switch(to_buff){
			case(0):
				modificado= "Salud";
				AUX->DatosPersonales->salud=AUX->DatosPersonales->salud+20;		
				break;
			case(1):
				modificado= "Velocidad";
				AUX->Caract->velocidad=AUX->Caract->velocidad+2;		
				break;
			case(2):
				modificado= "Destreza";
				AUX->Caract->destreza=AUX->Caract->destreza+2;		
				break;
			case(3):
				modificado= "Fuerza";
				AUX->Caract->fuerza=AUX->Caract->fuerza=3;		
				break;
			case(4):
				modificado= "Nivel";
				AUX->Caract->nivel=AUX->Caract->nivel+1;		
				break;
			case(5):
				modificado= "Armadura";
				AUX->Caract->armadura=AUX->Caract->armadura+1;		
				break;
			default:
				modificado= "Nada";
				break;
		}
	}else{
		modificado=" - ";
	}


	return modificado;
	
}

int PersonajesDisponibles(Tnodo **l){
	Tnodo* AUX = *l;
	int cont=0;

	while(AUX){
		cont++;
		AUX = AUX->next;
	}

	return cont;
}

void Mostrar_lista(Tnodo * l){
	printf("\n\n Personajes disponibles: \n\n");
	if(Es_lista_vacia(l)!=1){
		while(Es_lista_vacia(l) != 1){
			Mostrar_Nodo(l);
			printf("\n");
			l=l->next;
		}
		printf("\n");
	}else{
		printf("\n\nLista Vacia \n");
	}
}

void Mostrar_Nodo(Tnodo * l){
	if(Es_lista_vacia(l)!=1){
		printf("\t%i -", l->nro_pj);
		MostrarDatos(l);
		MostrarCarcteristicas(l);
	}else{
		printf("\n\nNodo Vacio \n");
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
	DP->ApellidoNombre= (char*)malloc( (sizeof(char)*strlen(Nombres[rand_nombre])) + (sizeof(char)*strlen(Apellidos[rand_apellido])) + 10);
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
	printf("%s\n",l->DatosPersonales->ApellidoNombre);
	switch(l->DatosPersonales->raza){
		case 0: printf("\t\tRaza: Asesino\n"); break;
		case 1: printf("\t\tRaza: Tanque\n"); break;
		case 2: printf("\t\tRaza: Luchador\n"); break;
		case 3: printf("\t\tRaza: Mago\n"); break;
		case 4: printf("\t\tRaza: Apoyo\n"); break;
	}
	printf("\t\tEdad: %i\n", l->DatosPersonales->edad);
	printf("\t\tSalud: %.2f\n", l->DatosPersonales->salud);

	return;
}

void MostrarCarcteristicas(Tnodo * l){
	printf("\t\tVelocidad: %i\n", l->Caract->velocidad);
	printf("\t\tDestreza: %i\n", l->Caract->destreza);
	printf("\t\tFuerza: %i\n", l->Caract->fuerza);
	printf("\t\tNivel: %i\n", l->Caract->nivel);
	printf("\t\tArmadura: %i\n", l->Caract->armadura);

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


void Batalla(Tnodo * l, int pj1, int pj2, int resultado[2]){
	int ganador,perdedor;
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
			printf("\nTURNO PERSONAJE %i - PRESIONA UNA TECLA PARA ATACAR\n",pj1);
			getch();
			Ataque(pj1,pj2);
			printf("\n\t\t\tDa%co=%.2f  -  Salud Pj%i=%.2f\n",164, dmg,pj2,s2);
		}else{
			PD = l2->Caract->destreza*l2->Caract->fuerza*l2->Caract->nivel;
			PDEF = l1->Caract->armadura*l1->Caract->velocidad;
			ED = (float)(1+random(100))/100;
			VA = PD * ED;
			dmg = ((VA-PDEF)/MDP)*100;
			if (dmg<0){dmg=0;}
			s1 = s1-dmg;
			//printf("\n%s ataca a %s\n",l2->DatosPersonales->ApellidoNombre, l1->DatosPersonales->ApellidoNombre);
			printf("\nTURNO PERSONAJE %i - PRESIONA UNA TECLA PARA ATACAR\n",pj2);
			getch();
			Ataque(pj2,pj1);
			printf("\n\t\t\tDa%co=%.2f  -  Salud Pj%i=%.2f\n",164,dmg,pj1,s1);
		}
		
	}

	if (s1>s2){
		ganador=pj1;
		perdedor=pj2;
		printf("\n\n\t\t\t  ______________________________\n");
		printf("\t\t\t |\t\t\t\t|\n");
		printf("\t\t\t |\tGANA EL PERSONAJE %i\t|",pj1);
		printf("\n\t\t\t |______________________________|\n\n\n");
	}else if(s2>s1){
		ganador=pj2;
		perdedor=pj1;
		printf("\n\n\t\t\t  ______________________________\n");
		printf("\t\t\t |\t\t\t\t|\n");
		printf("\t\t\t |\tGANA EL PERSONAJE %i\t|",pj2);
		printf("\n\t\t\t |______________________________|\n\n\n");
	}else{
		ganador=indef;
		perdedor=indef;
		printf("\n\n\t\t\t  _____________________\n");
		printf("\t\t\t |                     |\n");
		printf("\t\t\t |    HUBO UN EMPATE   |");
		printf("\n\t\t\t |_____________________|\n\n\n");
	}
	resultado[0]=ganador;
	resultado[1]=perdedor;
}


void Ataque(int pj1, int pj2){

	printf("\n\n");
	printf("\t\t    ___                     ___      ___            ");
  printf("\t\t\t\t   (-.-)_/............\\|/  | %i | |__(-.-)        \n",pj2);
	printf("\t\t _/|.%i.|              /|\\   \\_/     |.%i.|\\_  \n",pj1,pj2);
	printf("\t\t   _| |_                            _| |_         \n");
}


