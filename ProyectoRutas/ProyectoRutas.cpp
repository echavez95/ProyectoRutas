// ProyectoRutas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include "ClassConfigManager.h"

using namespace std;

int main()
{
	cout << "Leer archivo y guardarlo en una lista de rutas" << endl;
	ConfigManager fmHandler;
	fmHandler.leerArchivo();
	fmHandler.listaRutas.imprimirListaRutas();

	cout << endl;
	cout << "Imprmir la lista de ciudades" << endl;
	listaCiudades.imprimirListaCiudades();
	/*
	Ciudad sanPedro("San Pedro Sula");
	sanPedro.pilaPaquetesCiudad.Push(1);
	sanPedro.pilaPaquetesCiudad.Push(2);
	sanPedro.pilaPaquetesCiudad.Push(3);
	sanPedro.pilaPaquetesCiudad.Push(4);
	sanPedro.pilaPaquetesCiudad.Push(5);
	cout << endl;
	cout << "Ver la pila de Ciudad SPS" << endl;
	sanPedro.pilaPaquetesCiudad.VerPila();
	cout << endl;
	cout << "Retorna sacar paqute: " << endl;
	cout << sanPedro.sacarPaquete(5) << endl;
	cout << endl;
	cout << "Ver la pila de Ciudad SPS despues de sacar paquete" << endl;
	sanPedro.pilaPaquetesCiudad.VerPila();*/

	system("pause");
	return 0;
}


