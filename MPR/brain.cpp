//g++ -Wall -std=c++11 brain.cpp -o brain.exe
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include <thread>  
#include <chrono>    
#include <fstream>
#include "macros.h"

#define NUM_MOVIMIENTOS 3

using namespace std;

typedef struct {
	int entidad;
	int biologico;
	int cultural;
	int emocional;
	
	void imprimir() { 
		cout << "entidad: " << entidad << endl;
		cout << "biologico: " << biologico << endl;
		cout << "cultural: " << cultural << endl; 
		cout << "emocional: " << emocional << endl << endl; 
	}
}Estado;

int calcular_termometro();
int calcular_entidad(); 
void escribir_memoria_inicial( Estado ); // escribe la los primeros 4
void escribir_memoria( Estado, Estado ); // escribe en los 4 siguientes 
void leer_historial( Estado & );
void moverLinea(ifstream &archivo, int linea);
void cambiarLinea(string nombreArchivo, int lineaBuscada, int remplazar);




int main() {
	// se escribe en la memoria de instruccion
	//se lee desde historial 
	
	
	srand(time(NULL));
	Estado estadoActual;
	Estado estadoEntidad;
	
	estadoActual.entidad = 0;
	estadoActual.biologico = calcular_termometro();
	estadoActual.cultural = calcular_termometro();
	estadoActual.emocional = calcular_termometro();


	escribir_memoria_inicial( estadoActual ); // escribe el estado inicial en el que empieza el brain
	cout << "el estado inicial es: " << endl;
	estadoActual.imprimir();
	
	for(int i = 0; i < NUM_MOVIMIENTOS; i++ ) {
		do{
		
			estadoEntidad.entidad = calcular_entidad();
			
		}while(estadoEntidad.entidad == estadoActual.entidad);
		
		estadoEntidad.biologico = calcular_termometro();
		estadoEntidad.cultural = calcular_termometro();
		estadoEntidad.emocional = calcular_termometro();
	
		escribir_memoria( estadoActual, estadoEntidad );
		

		std::this_thread::sleep_for (std::chrono::seconds(NUM_INSTRUCTIONS / NUM_MOVIMIENTOS));
		
		
		leer_historial( estadoActual );
		cout << "el estado actual es" << endl;
		estadoActual.imprimir();
	}
	

	return 0;
}


int calcular_termometro() { //numero entre 1 y 3
	
	int num;	
	num=1+rand()%(4-1);
	return num;
	
}

int calcular_entidad() { // numero entre 0 y 7

	return 0 + rand() % (9-1);
}


void escribir_memoria_inicial( Estado inicial ) { // escribe la los primeros 4
	
	cambiarLinea("memoriaPrincipal.txt", 0, inicial.entidad);
	cambiarLinea("memoriaPrincipal.txt", 1, inicial.biologico);
	cambiarLinea("memoriaPrincipal.txt", 2, inicial.cultural);
	cambiarLinea("memoriaPrincipal.txt", 3, inicial.emocional);
	
	ofstream hist("../historial.txt");

	

	hist << inicial.entidad;
	hist << endl << inicial.biologico;
	hist << endl << inicial.cultural;
	hist << endl << inicial.emocional;

	hist.close();
}


void escribir_memoria( Estado actual, Estado entidad) {// escribe en los 4 siguientes 

	int b = 0, c = 0, e = 0;

	
	
	if( entidad.biologico > actual.biologico ) {
		b = 1;
	} 
	else if( entidad.biologico < actual.biologico ){
		b = -1;
	}

	if( entidad.cultural > actual.cultural ) {
		c = 1;
	} 
	else if( entidad.cultural < actual.cultural ){
		c = -1;
	}
	
	if( entidad.emocional > actual.emocional ) {
		e = 1;
	} 
	else if( entidad.emocional < actual.emocional ){
		e = -1;
	}
	//log
	cout << "al estado actual " << endl;
	actual.imprimir();
	cout << "se escribiran los datos " << entidad.entidad << " " << b << " " << c  << " " << e << endl;
	

	cambiarLinea("memoriaPrincipal.txt", 4, entidad.entidad);
	cambiarLinea("memoriaPrincipal.txt", 5, b);
	cambiarLinea("memoriaPrincipal.txt", 6, c);
	cambiarLinea("memoriaPrincipal.txt", 7, e);
}

void leer_historial( Estado &actual) { // despues de computado el estado actual lo lee
	static int ultima = 3;
	
	ifstream historial("../historial.txt");
	
	if( !historial ) {
		cout << "no se pudo abrir el archivo de historial.txt" << endl;
		exit(1);
	}
	
	moverLinea(historial, ++ultima);	
	historial >> actual.entidad; 
	
	moverLinea(historial, ++ultima);	
	historial >> actual.biologico; 
	
	moverLinea(historial, ++ultima);	
	historial >> actual.cultural; 
	
	moverLinea(historial, ++ultima);	
	historial >> actual.emocional; 
	
}


void moverLinea(ifstream &archivo, int linea) {
	archivo.seekg(0);
	int cont = 0;
	char aux = ' ';
	
	if(linea == 0) {
		return;
	}
	
	while( !archivo.eof() && aux != '\0') {
		aux = archivo.get();
		if(aux == '\n') {
			cont++;
		}
		if(cont == linea) {
			return;
		}
		
	}
	
}

void cambiarLinea(string nombreArchivo, int lineaBuscada, int remplazar) {
	
	ofstream temp("temp.txt");
	ifstream archivo(nombreArchivo);
	const int TAM = 16; // un txt de 16 lineas
	int contenido, i;
	
	if(!temp || !archivo) {
		cout << "en cambiar linea no se pudo abrir el archivo " << nombreArchivo <<  endl;
		exit(1);
	}

	archivo.seekg(0);
	
	for(i = 0; i < TAM && !archivo.eof(); i++) {
	
		moverLinea(archivo, i);
		archivo >> contenido;
		
		if(i != lineaBuscada) {
			temp << contenido ;
			if(i != TAM-1) {
				temp << endl;
			}
			
		}
		else {
			temp << remplazar ;
			if(i != TAM-1) {
				temp << endl;
			}
			
		}
		
	}

	archivo.close();
	temp.close();
	remove( nombreArchivo.c_str() );
	rename("temp.txt", nombreArchivo.c_str() );
	
	
}

