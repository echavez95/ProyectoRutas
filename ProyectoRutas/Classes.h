#include <iostream>
using namespace std;

int sizeMatriz;

class Paquete /*Clase paquete para armar las pilas de paquetes de una ciudad*/
{
    public:
        int Value;
        Paquete* NextPaquete;

    Paquete(int val)
    {
        Value=val;
        NextPaquete = 0;
    }

    ~Paquete(){}
};

class PilaPaquetes /*Clase para implementas la pila de paquetes*/
{
    public :
		Paquete *Tope;

	PilaPaquetes()
	{
        Tope =0;
	}

    void Push(int valor)
    {
        Paquete* nodo = new Paquete(valor);
        if(Vacia())
        {
            Tope=nodo;
        }
        else
            {
                nodo->NextPaquete=Tope;
                Tope=nodo;
            }
    }

    int Pop()
    {
        if(Vacia()){
            cout<<"Pila Vacia"<<endl;
        }
        else
            {
                int retorno;
                Paquete* nodoTemp;
                retorno=Tope->Value;

                nodoTemp=Tope;
                Tope=Tope->NextPaquete;

                delete nodoTemp;
                return retorno;
            }
    }

    bool Vacia()
    {
        if(Tope==0)
        {
            return true;
        }
        return false;
    }

    void VerPila()
    {
        if(Vacia()){
            cout<<"Pila Vacia"<<endl;
        }
        else
            {
                Paquete* nodoTemp=Tope;
                do
                {
                    cout<<nodoTemp->Value<<endl;
                    nodoTemp=nodoTemp->NextPaquete;
                }while(nodoTemp!=0);
            }
    }

};

class Ciudad /*Clase Ciudad, es decir un nodo del grafo*/
{
    public:
        PilaPaquetes pilaPaquetesCiudad;
        string nombre;
		int idCiudad;
		//Ciudad* Siguiente;

    Ciudad(string nombreC,int id)
    {
        nombre=nombreC;
		idCiudad = id;
		//Siguiente = 0;
    }

    Ciudad()
    {
    }

    void ingresarPaquete(int valorPaquete)
    {
        pilaPaquetesCiudad.Push(valorPaquete);
    }

    void verPilaPaquetes()
    {
        pilaPaquetesCiudad.VerPila();
    }

    int sacarPaquete(int valorBuscar)
    {
        Paquete* paqueteTemp;
        int resultado =NULL;
        if(pilaPaquetesCiudad.Tope->Value==valorBuscar){
            resultado=pilaPaquetesCiudad.Pop();
            return resultado;
        }else
        {
            PilaPaquetes pilaTemporal;
            /*int a = pilaPaquetesCiudad.Pop(); *///debug
            pilaTemporal.Push(pilaPaquetesCiudad.Pop());
            paqueteTemp = pilaPaquetesCiudad.Tope;
            /*a=pilaPaquetesCiudad.Tope->Value;*///debug
            do{
                /*a=paqueteTemp->Value;*///debug
                if(paqueteTemp->Value==valorBuscar){
                    resultado = pilaPaquetesCiudad.Pop();
                    break;
                }
                pilaTemporal.Push(pilaPaquetesCiudad.Pop());
                paqueteTemp=pilaPaquetesCiudad.Tope;
            }while(pilaPaquetesCiudad.Vacia()!=true);
            /*Seccion para debugguear*/
            /*
            cout<<"Pila Paquetes Ciudad"<<endl;
            pilaPaquetesCiudad.VerPila();
            cout<<"Pila Temporal"<<endl;
            pilaTemporal.VerPila();
            */
            do
            {
                pilaPaquetesCiudad.Push(pilaTemporal.Pop());
            }while(pilaTemporal.Vacia()!=true);

            /*Seccion para debugguear*/
            /*
            cout<<"Pila Paquetes Ciudad"<<endl;
            pilaPaquetesCiudad.VerPila();
            cout<<"Pila Temporal"<<endl;
            pilaTemporal.VerPila();
            */
           return resultado;
        }
    }

};
/*

*/
class Adyacente {
public:
	Vertice* Destino;
	int Costo;
	Adyacente* Siguiente;

	Adyacente() {
		Destino = 0;
		Costo = 0;
		Siguiente = 0;
	}

	Adyacente(Vertice* v, int c) {
		Destino = v;
		Costo = c;
		Siguiente = 0;
	}
};

class ListaAdyacentes
{
public:
	Adyacente* Primero;
	Adyacente* Ultimo;

	ListaAdyacentes() {
		Primero = 0;
		Ultimo = 0;
	}

	void agregarAdyacente(Vertice* verticenuevo,int costo ) {
		if (Primero==0)
		{
			Adyacente* nuevoAdyacente = new Adyacente(verticenuevo, costo);
			Primero = Ultimo = nuevoAdyacente;
		}else{
			Adyacente* nuevoAdyacente = new Adyacente(verticenuevo, costo);
			Ultimo->Siguiente = nuevoAdyacente;
			Ultimo = nuevoAdyacente;
		}
	}

};

class Vertice
{
public:
	Ciudad* City;
	Vertice* Siguiente;
	ListaAdyacentes listaAdyacentes;

	Vertice(string nombre) {
		City->nombre = nombre;
		Siguiente = 0;
	}
};

class ListaVertices {
	public:
		Vertice* Primero;
		Vertice* Ultimo;
		int Size;

		ListaVertices()
		{
			Primero = 0;
			Size = 0;
		}

		void agregarVertice(string nombre) {
			if (Primero == 0)
			{
				Vertice* nuevaCiudad = new Vertice(nombre);
				nuevaCiudad->City->idCiudad = 1;
				Primero = Ultimo = nuevaCiudad;
			}
			else
			{
				if (!existeCiudad(nombre)) {
					Vertice* nuevaCiudad = new Vertice(nombre);
					Ultimo->Siguiente = nuevaCiudad;
					nuevaCiudad->City->idCiudad = Ultimo->City->idCiudad + 1;
					Ultimo = nuevaCiudad;
					Size++;
				}
			}
		}

		bool existeCiudad(string nombre) {
			Vertice* tempCiudad;
			tempCiudad = Primero;
			for (int i = 0; i <= Size; i++) {
				if (tempCiudad->City->nombre == nombre)
				{
					return true;
				}
				tempCiudad = tempCiudad->Siguiente;
			}
			return false;
		}
};


/*
class Matriz {
	public:
		int* Matriz = new int[sizeMatriz][sizeMatriz];

	void inicializarMatriz() {
		for (int i = 0; i <= sizeMatriz; i++) {
			for (int j = 0; j <= sizeMatriz; j++) {
				Matriz[i][j] = 0;
			}
		}
	}

	void imprimirMatriz() {
		for (int i = 0; i <= sizeMatriz; i++) {

			cout << "Id Ciudad: " << Matriz[i] << endl;
		}
	}

};*/

