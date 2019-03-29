//Comentario de prueba grupo1

enum TRaza{Orco, Humano, Mago, Enano, Elfo};
char Nombres[6][10]={"ale", "b", "c", "d", "e"};
char Apellidos[6][10]={"f", "g", "hormiga", "i", "j"};

typedef struct{
	TRaza Raza; //nota 1
	char *ApellidoNombre; //nota 2
	int edad; //entre 0 a 300
	double Salud;//100
} TDatos;

typedef struct {
	int velocidad;// 1 a 10
	int destreza; //1 a 5
	int fuerza;//1 a 10
	int Nivel; //1 a 10
	int Armadura; //1 a 10
}TCaracteristicas;

typedef struct  {
	TDatos * DatosPersonales;
	TCaracteristicas * Caracteristicas;
}TPersonaje;

#include<stdio.h>
#include<stdlib.h>

TDatos cargar_datos();

int main(){
	printf("Ingrese candidad de personajes a introducir: ");
	scanf("%d",&cantp);
	//int cantper;
	//TPersonaje* personajes=(TPersonaje*)malloc(sizeof(TPersonaje)*cantper);
	TPersonaje* personaje1;
	personaje1->DatosPersonales = cargar_datos();
	//personaje1.Raza = Mago;

	return 0;
}

TDatos cargar_datos(){
	DatosPersonales = (TDatos*)malloc(sizeof(TDatos));
	DatosPersonales->Raza= Mago;
	DatosPersonales->ApellidoNombre="asd";
	DatosPersonales->edad=10;
	DatosPersonales->Salud=100.50;

	return personaje;

}