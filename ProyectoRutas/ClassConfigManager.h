#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Classes.h"
#define INF 99999

using namespace std;
const int sizeMatriz = 50;
int cantidadCiudades = 0;

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
			cantidadCiudades = listaCiudades.Size;
            if (!infile.eof())
            {
            cerr << "Terminado!\n";
            }
        }
		
		
};

class Grafo {
public:
	int Matriz[sizeMatriz][sizeMatriz];
	int costoCiudad[sizeMatriz];
	int rutasCiudad[sizeMatriz];
	int costosTodasCiudades[sizeMatriz][sizeMatriz];

	Grafo() {
		inicializarMatriz();
	}

	void inicializarMatriz() { //inicializa toda la matriz con los datos de las rutas
		if(cantidadCiudades <=sizeMatriz){
			for (int i = 0; i <= cantidadCiudades; i++) {
				for (int j = 0; j <= cantidadCiudades; j++) {
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
			for (int i = 0; i <= cantidadCiudades; i++) {
				cout << i << "\t";
			}

			cout << endl;
			for (int i = 0; i <= cantidadCiudades; i++) {
				cout << i << "\t";
				for (int j = 0; j <= cantidadCiudades; j++) {
					cout << Matriz[i][j] << "\t";
				}
				cout << endl;
			}
			cout << endl;
	}

	int minDistance(int dist[], bool sptSet[])
	{
		// Inicializar valor minimo
		int min = INT_MAX, min_index;
		for (int i = 0; i <= cantidadCiudades; i++)
			if (sptSet[i] == false && dist[i] <= min)
				min = dist[i], min_index = i;
		return min_index;
	}

	//Algoritmo de DIKJSTRA para calcular costo minimo entre ciudades
	bool CostoMinimo(int idCorigen,int idCdestino) {
		if (idCorigen == idCdestino) { cout << "Accion invalida"<<endl; return false; }

		bool conocido[8];		

		for (int i = 0; i <= cantidadCiudades; i++) {
			rutasCiudad[i] = -1, costoCiudad[i] = INT_MAX, conocido[i] = false;
		}

		costoCiudad[idCorigen] = 0;
		for (int count = 0; count <= cantidadCiudades - 1; count++)
		{
			int u = minDistance(costoCiudad, conocido);
			conocido[u] = true;

			for (int v = 0; v <= cantidadCiudades; v++)
				if (!conocido[v] && Matriz[u][v] && costoCiudad[u] != INT_MAX
					&& costoCiudad[u] + Matriz[u][v] < costoCiudad[v]) {
					costoCiudad[v] = costoCiudad[u] + Matriz[u][v];
					rutasCiudad[v] = u;
				}
		}

		return true;
	}

	//muestra el costo entre una ciudad de origen y el destino
	void MostrarCosto(int origen,int destino)
	{
		
		int costo;
		for (int i = 0; i <= destino; i++) {
			costo = costoCiudad[i];
		}
		
		int padre;
		int actual = destino;
		string ruta = listaCiudades.getNombreCiudad(actual);
		do {
			padre = rutasCiudad[actual];
			actual = padre;
			if (actual<0) {
				break;
			}
			ruta =  listaCiudades.getNombreCiudad(actual) + "------->" + ruta;
		} while (true);
		cout << "Costo: " << costo << " Ruta: " << ruta << endl;
	}

	// floyd para calculo de menor costo entre todos los vertices
	void CostoMinimoTodasCiudades()
	{
		int i, j, k;

		for (i = 0; i <= cantidadCiudades; i++) 
		{
			for (j = 0; j <= cantidadCiudades; j++) 
			{
					costosTodasCiudades[i][j] = Matriz[i][j];
			}
		}

		for (int a = 0; a <= cantidadCiudades; a++)
		{
			for (int b = 0; b <= cantidadCiudades; b++)
			{
				if (a == b) {
					costosTodasCiudades[a][b] = 0;
				}
				else if(costosTodasCiudades[a][b]==0)
					costosTodasCiudades[a][b] = INF;
			}
		}
				
		for (k = 0; k <= cantidadCiudades; k++)
		{
			for (i = 0; i <= cantidadCiudades; i++)
			{
				for (j = 0; j <= cantidadCiudades; j++)
				{
					if (costosTodasCiudades[i][k] + costosTodasCiudades[k][j] < costosTodasCiudades[i][j])
						costosTodasCiudades[i][j] = costosTodasCiudades[i][k] + costosTodasCiudades[k][j];
				}
			}
		}
		
	}

	/* imprime la matriz de costos */
	void mostrarMatrizCostos()
	{
		cout << setw(22)<<" ";
		for (int a = 0; a <= cantidadCiudades; a++) {
			cout<< setw(5) << a ;
		}
		cout << endl;
		for (int i = 0; i <= cantidadCiudades; i++)
		{
			cout <<setw(20)<< listaCiudades.getNombreCiudad(i)<<" "<<i<<" ";
			for (int j = 0; j <= cantidadCiudades; j++)
			{
				if (costosTodasCiudades[i][j] == INF)
					cout << setw(5) << "0" ;
				else
					cout << setw(5) << costosTodasCiudades[i][j];
			}
			cout << endl;
		}
	}

};
