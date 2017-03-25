// ProyectoRutas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include "ClassConfigManager.h"

using namespace std;


int main()
{
	//dibujarRuta();
	
	ConfigManager fmHandler;
	fmHandler.leerArchivo();
	Grafo grafoRutas;
	grafoRutas.inicializarMatriz();
	grafoRutas.CostoMinimoTodasCiudades();

	int opcion;
	int r;
	do {
		system("cls");
		cout << "-------------- Envio de Paquetes ------------" << endl;
		cout << "1. Calcular Costo de envio" << endl;
		cout << "2. Ver costos entre ciudades" << endl;
		cout << "3. Enviar Paquete" << endl;
		cout << "4. Ver Pila de Paqutes" << endl;
		cout << "5. Retirar Paquete" << endl;
		cout << "0. Salir" << endl;
		cout << "Presione la tecla correspondiente a la opcion: ";
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			do
			{
				system("cls");
				int idOrigen, idDestino;
				cout << "Lista de Ciudades: " << endl;
				listaCiudades.imprimirListaCiudades();
				cout << endl;
				cout << "Origen: ";
				cin >> idOrigen;
				cout << "Destino: ";
				cin >> idDestino;
				cout << endl;
				if (grafoRutas.CostoMinimo(idOrigen, idDestino)) { grafoRutas.MostrarCosto(idOrigen, idDestino); };
				cout << "Presione 0 para salir o cualquier numero para repetir: ";
				cin >> r;
			} while (r != 0);
			break;
		case 2:
			system("cls");
			cout << "Tabla de Costos Minimos" << endl;
			grafoRutas.mostrarMatrizCostos();
			system("pause");
			break;
		case 3:
			do
			{
				system("cls");
				int idOrigen, idDestino;
				string remitente, destinatario;
				cout << "Enviar Paquete" << endl;
				cout << "Lista de Ciudades: " << endl;
				listaCiudades.imprimirListaCiudades();
				cout << endl;
				cout << "Origen: ";
				cin >> idOrigen;
				cout << "Destino: ";
				cin >> idDestino;
				cout << endl;
				if (grafoRutas.CostoMinimo(idOrigen, idDestino)) {
					cout << "Remitente: ";
					cin >> remitente;
					cout << "Destinatario: ";
					cin >> destinatario;
					idpaquetes++;
					cout << "El Id del Paquete es: "<<idpaquetes<< endl;
					grafoRutas.MostrarCosto(idOrigen, idDestino);
					Paquete nuevo(idpaquetes, remitente, destinatario, idOrigen, idDestino);
					listaCiudades.agregarPaqueteCiudad(idDestino,nuevo);
					cout << "Paquete enviado!" << endl;
				}
				cout << "Presione 0 para salir o cualquier numero para repetir: ";
				cin >> r;
			} while (r != 0);

			break;
		case 4:
			do
			{
				system("cls");
				int idCiudad;
				cout << "Ver pila de paquetes de la Ciudad" << endl;
				cout << "Lista de Ciudades:" << endl;
				listaCiudades.imprimirListaCiudades();
				cout << endl;
				cout << "Id de la Ciudad: ";
				cin >> idCiudad;
				cout << endl;
				listaCiudades.verPilaCiudad(idCiudad);
				cout << "Presione 0 para salir o cualquier numero para repetir: ";
				cin >> r;
			} while (r != 0);
			break;
		case 5:
			do
			{
				system("cls");
				int idCiudad,idpaquete;
				cout << "Retirar paquete de Ciudad" << endl;
				cout << "Lista de Ciudades:" << endl;
				listaCiudades.imprimirListaCiudades();
				cout << endl;
				cout << "Id de la Ciudad: ";
				cin >> idCiudad;
				cout << endl;
				cout << "Id del paquete: ";
				cin >> idpaquete;
				cout << endl;
				Paquete retirado = listaCiudades.retirarPaqueteCiudad(idCiudad, idpaquete);
				if (retirado.id == 0) 
				{
					cout << "No existe este paquete"<<endl;
				}
				else 
				{
					cout << "Id: " << retirado.id << endl;
					cout << "Remitente: " << retirado.remitente << endl;
					cout << "Destinatario: " << retirado.destinatario << endl;
					cout << "Ciudad Origen: " << listaCiudades.getNombreCiudad(retirado.idCorigen) << endl;
					cout << "Ciudad Destino: " << listaCiudades.getNombreCiudad(retirado.idCdestino) << endl;
				}
				cout<< "Presione 0 para salir o cualquier numero para repetir: ";
				cin >> r;
			} while (r != 0);
			break;
		default:
			break;
		}


	} while (opcion != 0);
	
	system("pause");
	return 0;
	/*
	cout << "Leer archivo y guardarlo en una lista de rutas" << endl;
	
	listaRutas.imprimirListaRutas();
	cout << endl;
	cout << "Imprmir la lista de ciudades" << endl;
	listaCiudades.imprimirListaCiudades();

	
	cout << "Imprmir la matriz" << endl;
	
	grafoRutas.imprimirMatriz();
	
	grafoRutas.CostoMinimo(1,3);

	cout << "Imprmir la matriz" << endl;
	grafoRutas.CostoMinimoTodasCiudades();
	*/
	/*
	cout << "Buscar Puerto Cortes" << endl;
	cout << listaCiudades.getNombreCiudad(0) << endl;
	*/
	/*
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
	sanPedro.pilaPaquetesCiudad.VerPila();*/

	
}


