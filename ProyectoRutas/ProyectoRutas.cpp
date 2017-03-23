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
	listaRutas.imprimirListaRutas();
	cout << endl;
	cout << "Imprmir la lista de ciudades" << endl;
	listaCiudades.imprimirListaCiudades();
	/*
	Grafo grafoRutas;
	cout << "Imprmir la matriz" << endl;
	grafoRutas.inicializarMatriz();
	grafoRutas.imprimirMatriz();

	cout << "Buscar Puerto Cortes" << endl;
	cout << listaCiudades.getNombreCiudad(0) << endl;
	*/

	Ciudad sanPedro("San Pedro Sula",1);
	Paquete nuevo1(1,"eliezer","abraham",0,1);
	sanPedro.pilaPaquetesCiudad.Push(nuevo1);

	Paquete nuevo2(2, "eliezer", "carolina", 3, 1);
	sanPedro.pilaPaquetesCiudad.Push(nuevo2);

	Paquete nuevo3(3, "laura", "abraham", 2, 1);
	sanPedro.pilaPaquetesCiudad.Push(nuevo3);

	Paquete nuevo4(4, "samuel", "carlos", 5, 1);
	sanPedro.pilaPaquetesCiudad.Push(nuevo4);

	Paquete nuevo5(5, "eliezer", "samuel", 4, 1);
	sanPedro.pilaPaquetesCiudad.Push(nuevo5);

	cout << endl;
	cout << "Ver la pila de Ciudad SPS" << endl;
	sanPedro.pilaPaquetesCiudad.VerPila();
	cout << endl;

	cout << "Retorna sacar paqute: " << endl;
	Paquete salida = sanPedro.sacarPaquete(1);
	cout << "Id: " << salida.id << endl;
	cout << "Remitente: " << salida.remitente << endl;
	cout << "Destinatario: " << salida.destinatario << endl;
	cout << "Ciudad Origen: " << listaCiudades.getNombreCiudad(salida.idCorigen) << endl;
	cout << "Ciudad Destino: " << listaCiudades.getNombreCiudad(salida.idCdestino) << endl;

	cout << endl;
	cout << "Ver la pila de Ciudad SPS despues de sacar paquete" << endl;
	sanPedro.pilaPaquetesCiudad.VerPila();

	system("pause");
	return 0;
}


