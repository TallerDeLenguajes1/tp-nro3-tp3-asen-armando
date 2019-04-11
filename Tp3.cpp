#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

enum TRaza{Hechicero, Caballero, Lobizon, Caminante, Nemesis};
char* Nombres[]={"Romualdo","Alex","Roger","Antonio","Carlito","Jacinto",NULL}; //probando arreglo de punteros //global //volver a cadena[i][j]
char* Apellidos[]={"Martinez","Perez","Paez","Fernandez","Gutierrez",NULL};

typedef struct TDatos{
	TRaza Raza;
	char* ApellidoNombre;
	int edad;
	double Salud;
}T_Datos;

typedef struct TCaracteristicas{
	int velocidad;
	int destreza;
	int fuerza;
	int Nivel;
	int Armadura;
}T_Caracteristicas;

typedef struct TPersonaje{
	TDatos* DatosPersonales; 
	TCaracteristicas* Caracteristicas;
}T_Personaje;

int creaPers(T_Personaje** ppuntpers);
void cargaDatos(T_Personaje* puntpers);
void cargaCarac(T_Personaje* puntpers);
void mostrarDatos(T_Personaje* puntpers);
void mostrarCarac(T_Personaje* puntpers); 
void visorPers(T_Personaje* puntpers, int cantpers);
void pelea(T_Personaje* puntpers, int cantpers);
void dibupers(T_Personaje* puntpers);

//MAIN------------------------------------------------------------------------------------------------------
void main(){
	T_Personaje* ptrpersonaje=NULL; 
	int cant, opcion;
	srand(time(NULL)); /*Para que genere las semillas de nuevos numeros aleatorios rand() al ejecutar de nuevo el programa*/
	
	do{
		printf("--INGRESE UN NUMERO COMO OPCION--\n");
		printf("-1: Crear N Personajes nuevos\n-2: Visor de un Personaje\n-3: Pelea entre dos personajes\n-4: Salir\n");
		scanf("%d",&opcion);
		printf("\n");
		switch(opcion){
			case 1:
				cant=creaPers(&ptrpersonaje); 
				break;
			case 2:
				if(ptrpersonaje==NULL) printf("DENEGADO: no ha creado ningun personaje todavia!\n\n");
				else{system("cls"); visorPers(ptrpersonaje, cant);}    
				break;
			case 3:
				if(ptrpersonaje==NULL) printf("DENEGADO: no ha creado ningun personaje todavia!\n\n");
				else{system("cls"); pelea(ptrpersonaje, cant);}
				break;
		}
	}while(opcion!=4);
}

//FUNCIONES CREADAS:
//para crear personajes 
int creaPers(T_Personaje** ppuntpers){ //recibo la direccion del puntero a cargar (puntero a puntero), pasaje variable por referencia, no el valor 
	int i, cant;
	
	if((*ppuntpers)!=NULL){
		free(*ppuntpers); //libero memoria por si a estaba ocupada y estoy por crear nuevos personajes (funcionaria igual sin esto pero es para desocupar memoria anterior)
	}

	printf("**INGRESE LA CANTIDAD DE PERSONAJES A CREAR: ");
	scanf("%d", &cant); printf("\n");
	
	*ppuntpers=(T_Personaje*)malloc(sizeof(T_Personaje)*cant); //reservo memo para tal cantidad de personajes
	
	printf("**Creando personajes**\n\n");
	for(i=0;i<cant;i++){
		/*Llamo a las funciones para cargar datos y caracteristicas de cada personaje y mostrarlas*/
		cargaDatos(*ppuntpers+i);
		cargaCarac(*ppuntpers+i); 
		
		printf("--PERSONAJE NUM %d--\n", i+1);
		mostrarDatos(*ppuntpers+i);
		mostrarCarac(*ppuntpers+i);
		printf("\n");
	}
	printf("**%d Personajes fueron creados con exito**\n--------------------------------------------\n\n", cant);

	return cant;
}

//para cargar datos
void cargaDatos(T_Personaje* puntpers){
	int i,contnomb=0,contapel=0;
	char* nombre; char* apellido;
	
	puntpers->DatosPersonales=(T_Datos*)malloc(sizeof(T_Datos)); //reservo memoria dinamica (a parte) para DatosPersonales

	for(i=0;(Nombres[i])!=NULL;i++) contnomb++; //contando cantidad de nombres que hay
	for(i=0;(Apellidos[i])!=NULL;i++) contapel++; //contando cantidad de apellidos que hay
	
	nombre=Nombres[rand()%contnomb]; //cargando un nombre aleatorio (el arreglo Nombres[] es global)
	apellido=Apellidos[rand()%contapel]; //cargando un apellido aleatorio (el arreglo Apellidos[] es global)
	
	puntpers->DatosPersonales->ApellidoNombre=(char*)malloc(sizeof(char)*(strlen(nombre)+strlen(apellido)+2)); //reservo memoria dinamica para nobmre y apellido segun la longitud de cada uno
	strcpy(puntpers->DatosPersonales->ApellidoNombre,nombre); 
	strcat(strcat(puntpers->DatosPersonales->ApellidoNombre," "),apellido); //concatenando espacio y luego el apellido
	puntpers->DatosPersonales->Raza=rand()%5;
	puntpers->DatosPersonales->edad=rand()%301;
	puntpers->DatosPersonales->Salud=100;
}

//para cargar caracteristicas
void cargaCarac(T_Personaje* puntpers){
	puntpers->Caracteristicas=(T_Caracteristicas*)malloc(sizeof(T_Caracteristicas)); //reservo memoria dinamica (a parte) para Caracteristicas
	
	puntpers->Caracteristicas->velocidad=rand()%10+1; 
	puntpers->Caracteristicas->destreza=rand()%5+1;
	puntpers->Caracteristicas->fuerza=rand()%10+1;
	puntpers->Caracteristicas->Nivel=rand()%10+1;
	puntpers->Caracteristicas->Armadura=rand()%10+1;
}

//para mostrar datos
void mostrarDatos(T_Personaje* puntpers){
	switch(puntpers->DatosPersonales->Raza){
		case 0:
			printf("-Raza:Hechicero\n");  
			break;
		case 1:
			printf("-Raza:Caballero\n");
			break;
		case 2:
			printf("-Raza:Lobizon\n");
			break;
		case 3:
			printf("-Raza:Caminante\n");
			break;		 
		case 4:
			printf("-Raza:Nemesis\n");
			break;		 
	}
		
	printf("-Nombre/Apellido:%s\n",puntpers->DatosPersonales->ApellidoNombre );
	printf("-Edad:%d\n",puntpers->DatosPersonales->edad);
	printf("-Salud:%.2f\n",puntpers->DatosPersonales->Salud);
}

//para mostrar caracteristicas
void mostrarCarac(T_Personaje* puntpers){
	printf("-Velocidad:%d\n",puntpers->Caracteristicas->velocidad);	
	printf("-Destreza:%d\n",puntpers->Caracteristicas->destreza);
	printf("-Fuerza:%d\n",puntpers->Caracteristicas->fuerza);
	printf("-Nivel:%d\n",puntpers->Caracteristicas->Nivel);
	printf("-Armadura:%d\n",puntpers->Caracteristicas->Armadura);
}

//Visor de personaje
void visorPers(T_Personaje* puntpers, int cantpers){ 
	int nump;
	
	do{  
		printf("**ELIJA EL NUMERO DEL PERSONAJE A MOSTRAR (del 1 al %d): ", cantpers); 
		scanf("%d",&nump); 
	}while(nump<1 || nump>cantpers); 

	printf("\n\n--PERSONAJE NUM %d--\n\n", nump);
	dibupers(puntpers+(nump-1)); 
	printf("\nDatos del personaje\n"); mostrarDatos(puntpers+(nump-1));
	printf("\nCaracteristicas del personaje\n"); mostrarCarac(puntpers+(nump-1)); 
	printf("\n\n--------------------------------------------\n\n");
}

//Funcion pelea /*Tener en cuenta que la salud de cada personaje se actualiza por la direccion, por lo que si vuelvo a buscar el visor, su salud estara cambiada hasta que cree nuevos personajes
void pelea(T_Personaje* puntpers, int cantpers){
	T_Personaje* personaje[2]; //2 punteros para cada personaje 
	int nump,i,j,a,b;
	float PD[2], PDEF[2], ED[2], VA[2], danio[2];
	float rondas=3, MDP=50000;

	/*Seleccionando personajes*/
	for(i=0;i<2;i++){
		do{  
			if(i==0) printf("**Seleccione el primer personaje (del 1 al %d): ", cantpers); 
			else printf("**Seleccione el segundo personaje (del 1 al %d): ", cantpers); 
			
			scanf("%d",&nump); 
		}while(nump<1 || nump>cantpers); //control de limite de numeros a elegir

		personaje[i]=puntpers+(nump-1); //paso la direccion del personaje elegido
		 
		/*cargo Poder de disparo y Poder de defensa de cada uno de los dos personajes*/
		PD[i]=(personaje[i]->Caracteristicas->destreza)*(personaje[i]->Caracteristicas->fuerza)*(personaje[i]->Caracteristicas->Nivel);
		PDEF[i]=(personaje[i]->Caracteristicas->Armadura)*(personaje[i]->Caracteristicas->velocidad);
		printf("\nP%d\n", i+1);
		dibupers(personaje[i]); printf("\n"); 
		mostrarDatos(personaje[i]); printf("-PD:%.2f/PDEF:%.2f\n", PD[i], PDEF[i]); 
		printf("\n\n");
	}
	printf("--Presione Enter para comenzar las rondas "); getch(); system("cls");

	/*3 rondas*/
	for(j=0;j<rondas;j++){
		printf("-------------------\n----RONDA NRO %d----\n-------------------\n",j+1); 

		a=0; b=1;
		for(i=0;i<2;i++){  //repite 2 veces (para P1 y para P2)
			if(i==1){a=1; b=0;} //para cambiar en algunos casos P1 o P2
			printf("\nP%d ataca --> P%d defiende", a+1, b+1); getch();
		    printf("\n========================>\n"); 
			
			ED[i]=(float)((rand()%100)+1)/100; /*cargo random en Efectividad del disparo de personaje A y B*/
			VA[i]=PD[i]*ED[i]; /*Valor de ataque de cada personaje*/
			printf("P%d efectividad de disparo:%.0f%% de %.2f = %.2f\n", i+1, (ED[i]*100), PD[i], VA[i]);
			
			danio[b]=((VA[a]-PDEF[b])/MDP)*100;  
			personaje[b]->DatosPersonales->Salud=(personaje[b]->DatosPersonales->Salud)-danio[b];
			printf("P%d def:%.2f recibio un danio de %.2f / Salud P%d:%.2f\n", b+1, PDEF[b], danio[b],  b+1, personaje[b]->DatosPersonales->Salud);
		} //FALTA REVISAR VALORES 
		
		if(j<(rondas-1)) printf("\n\n--Presione Enter para siguiente ronda");
		getch(); printf("\n\n"); 
	}
	
	system("cls"); printf("--RESULTADO FINAL--\n");
	printf("Salud P1:%f\nSalud P2:%f\n\n", personaje[0]->DatosPersonales->Salud, personaje[1]->DatosPersonales->Salud); 

	if((personaje[0]->DatosPersonales->Salud)>(personaje[1]->DatosPersonales->Salud)){ 
		printf("------------------------\n--GANADOR JUGADOR No 1--\n------------------------\n");
		dibupers(personaje[0]);
	}	
	else if((personaje[0]->DatosPersonales->Salud)<(personaje[1]->DatosPersonales->Salud)){ 
		printf("------------------------\n--GANADOR JUGADOR No 2--\n------------------------\n");
		dibupers(personaje[1]);
	}
	else                             
		printf("-------------\n--EMPATARON--\n-------------\n");
	printf("\n\n");
}									 

void dibupers(T_Personaje* puntpers){
	switch(puntpers->DatosPersonales->Raza){
		case 0:
			printf("    _^_\n   (- -)\n   /(_)\\\n"); 
			break;
		case 1:
			printf("    ...\n   (---) |\n  o*(_)*o+\n");
			break;
		case 2:
			printf("   (\\_/)\n   (> <)\n  *o(=)o*\n");
			break;
		case 3:
			printf("   \\|||/\n   (o o) /\n  oo(_)o/\n");
			break;		 
		case 4:
			printf("    ___\n   ( H*)\n  o=(_)Oo\n");
			break;		 
	}
}