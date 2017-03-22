#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Classes.h"

using namespace std;

ListaCiudades listaCiudades;

class xCiudad /*Clase Ciudad, es decir un nodo del grafo*/
{
public:
	string nombre;
	int idCiudad;
	xCiudad* Siguiente;

	xCiudad(string nombreC, int id)
	{
		nombre = nombreC;
		idCiudad = id;
		Siguiente = 0;
	}
};

class ListaCiudades {
public:
	xCiudad* Primero;
	xCiudad* Ultimo;
	int Size;

	ListaCiudades()
	{
		Primero = 0;
		Ultimo = 0;
		Size = 0;
	}

	void agregarCiudad(string nombre) {
		if (Primero == 0)
		{
			xCiudad* nuevaCiudad = new xCiudad(nombre, Size);
			Primero = Ultimo = nuevaCiudad;
		}
		else
		{
			if (!existeCiudad(nombre)) {
				Size++;
				xCiudad* nuevaCiudad = new xCiudad(nombre, Size);
				Ultimo->Siguiente = nuevaCiudad;
				Ultimo = nuevaCiudad;
			}
		}
		sizeMatriz = Size;
	}

	bool existeCiudad(string nombre) {
		xCiudad* tempCiudad;
		tempCiudad = Primero;
		for (int i = 0; i <= Size; i++) {
			if (tempCiudad->nombre == nombre)
			{
				return true;
			}
			tempCiudad = tempCiudad->Siguiente;
		}
		return false;
	}

	void imprimirListaCiudades()
	{
		xCiudad* tempCiudad;
		tempCiudad = Primero;
		for (int i = 0; i <= Size; i++) {
			cout << "Id Ciudad: " << tempCiudad->idCiudad <<
				" Nombre: " << tempCiudad->nombre << endl;
			tempCiudad = tempCiudad->Siguiente;
		}
	}
};

class Ruta{ /*Clase Ruta, Para almaenar las filas del archivo de rutas al leerlo*/
    public:
        Ciudad Desde;
        Ciudad Hasta;
        float Costo;
        Ruta* Siguiente;

    Ruta(string Cdesde, string Chasta, float costoEnvio)
    {
        Desde.nombre=Cdesde;
        Hasta.nombre=Chasta;
        Costo=costoEnvio;
    }

};

class ListaRutasCosto{ /*Lista que almacena los valores leidos del archivo de rutas*/
    public:
        Ruta* Primero;
        Ruta* Ultimo;
        int Size;

    ListaRutasCosto()
    {
        Primero=0;
        Size=0;
    }

    void InsertarRuta(string Rdesde, string Rhasta, float RcostoEnvio) /**Inserta un elemento al inicio**/
    {
        if(Primero==0)
        {
            Ruta* nuevaRuta = new Ruta(Rdesde,Rhasta,RcostoEnvio);
            Primero=Ultimo=nuevaRuta;
        }
        else
            {
                if(!existeRuta(Rdesde,Rhasta)){
                    Ruta* nuevaRuta = new Ruta(Rdesde,Rhasta,RcostoEnvio);
                    Ultimo->Siguiente=nuevaRuta;
                    Ultimo=nuevaRuta;
                    Size++;
                }else
                    {
                        cout<<"Ya existe esta ruta"<<endl;
                    }
            }
    }

    bool existeRuta(string Cdesde, string Chasta)
    {
        Ruta* tempRuta;
        tempRuta=Primero;
        for(int i=0;i<=Size;i++){
            if(tempRuta->Desde.nombre==Cdesde && tempRuta->Hasta.nombre==Chasta)
            {
                return true;
            }
            if(tempRuta->Desde.nombre==Chasta && tempRuta->Hasta.nombre==Cdesde)
            {
                return true;
            }
            tempRuta=tempRuta->Siguiente;
        }
        return false;
    }

    void imprimirListaRutas()
    {
        Ruta* tempRuta;
        tempRuta=Primero;
        for(int i=0;i<=Size;i++){
            cout<<"Desde: "<<tempRuta->Desde.nombre<<" Hasta: "<<tempRuta->Hasta.nombre<<" Costo: "<<tempRuta->Costo<<endl;
            tempRuta=tempRuta->Siguiente;
        }
    }
};

class ConfigManager{
    public:
        ListaRutasCosto listaRutas;
         /**TEMPORAL PARA PRUEBAS**/
        int indiceActualArreglo=0;
        void leerArchivo()
        {
            //string nombreArchivo="ArchivoRutas.txt";
            ifstream infile( "ArchivoRutas.txt" );
            while (infile)
            {
                string fila;
                string filaDelimitada[3];
                float costo;

                if (!getline( infile, fila )) break;
                istringstream ss( fila );
                int i=0;
                while (ss)
                {
                  string dato;
                  if (!getline( ss, dato, ',' )) break;
                  filaDelimitada[i]=dato;
                  i++;
                }

                costo = ::atof(filaDelimitada[2].c_str());
                listaRutas.InsertarRuta(filaDelimitada[0],filaDelimitada[1],costo);
            }

			/*INSERTAR LAS CIUDADES EN UNA LISTA DE CIUDADES*/
            Ruta* tempRuta;
            tempRuta=listaRutas.Primero;
            for(int i=0;i<=listaRutas.Size;i++){
                //cout<<"Desde: "<<tempRuta->Desde.nombre<<" Hasta: "<<tempRuta->Hasta.nombre<<" Costo: "<<tempRuta->Costo<<endl;
                listaCiudades.agregarCiudad(tempRuta->Desde.nombre);
				listaCiudades.agregarCiudad(tempRuta->Hasta.nombre);
                tempRuta=tempRuta->Siguiente;
            }

            if (!infile.eof())
            {
            cerr << "Terminado!\n";
            }
        }
		/*
        void insertarArregloCiudades(string NombreCiudad)
        {
            if(indiceActualArreglo==0){
                Ciudad nueva(NombreCiudad);
                arregloCiudades[indiceActualArreglo]=nueva ;
                arregloCiudades[indiceActualArreglo].nombre=NombreCiudad;
                cout<<arregloCiudades[indiceActualArreglo].nombre<<endl;
                indiceActualArreglo++;
            }else
                {
                    for(int i=0;i<indiceActualArreglo;i++){
                        if(arregloCiudades[i].nombre==NombreCiudad){
                            return;
                        }
                    }
                    arregloCiudades[indiceActualArreglo].nombre=NombreCiudad;
                    indiceActualArreglo++;
                }
        }

        void imprimirArregloCiudades()
        {
            for(int i=0;i<indiceActualArreglo;i++){
               cout<<arregloCiudades[i].nombre<<endl;
            }
        }*/
};

