#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Classes.h"

using namespace std;
const int sizeMatriz = 50;

ListaCiudades listaCiudades;

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

	int getCosto(int idCDesde, int idCHasta) {
		string ndesde = listaCiudades.getNombreCiudad(idCDesde);
		string nhasta = listaCiudades.getNombreCiudad(idCHasta);

		Ruta* tempRuta;
		tempRuta = Primero;
		for (int i = 0; i <= Size; i++) {
			if (tempRuta->Desde.nombre == ndesde && tempRuta->Hasta.nombre == nhasta)
			{
				return tempRuta->Costo;
			}
			if (tempRuta->Desde.nombre == nhasta && tempRuta->Hasta.nombre == ndesde)
			{
				return tempRuta->Costo;
			}
			tempRuta = tempRuta->Siguiente;
		}
		return 0;
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

ListaRutasCosto listaRutas;

class ConfigManager{
    public:
         /**TEMPORAL PARA PRUEBAS**/
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
		
		
};

class Grafo {
public:
	int Matriz[sizeMatriz][sizeMatriz];

	Grafo() {
		inicializarMatriz();
	}

	void inicializarMatriz() { //inicializa toda la matriz con los datos de las rutas
		if(listaCiudades.Size<=sizeMatriz){
			for (int i = 0; i <= listaCiudades.Size; i++) {
				for (int j = 0; j <= listaCiudades.Size; j++) {
					Matriz[i][j] = listaRutas.getCosto(i,j);
				}
			}
		}
		else {
			cout << "No se pueden usar mas de 50 ciudades!";
		}
	}

	void imprimirMatriz() {
			cout << "Matriz de Adyacencia" << endl;
			cout << "\t";
			for (int i = 0; i <=listaCiudades.Size; i++) {
				cout << i << "\t";
			}

			cout << endl;
			for (int i = 0; i <=listaCiudades.Size; i++) {
				cout << i << "\t";
				for (int j = 0; j <=listaCiudades.Size; j++) {
					cout << Matriz[i][j] << "\t";
				}
				cout << endl;
			}
			cout << endl;
	}


};
