#include <iostream>
using namespace std;



class Paquete /*Clase paquete para armar las pilas de paquetes de una ciudad*/
{
    public:
        int id;
		string remitente;
		string destinatario;
		int idCorigen;			//id de la ciudad de origen
		int idCdestino;			//id de la ciudad de destino
        Paquete* NextPaquete;

    Paquete(int idp,string r, string d,int ido, int idd)
    {
		id=idp;
		remitente = r;
		destinatario = d;
		idCorigen = ido;
		idCdestino = idd;
        NextPaquete = 0;
    }

	Paquete(){}

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

    void Push(Paquete nuevo)
    {
        Paquete* nodo = new Paquete(nuevo.id, nuevo.remitente, nuevo.destinatario, nuevo.idCorigen, nuevo.idCdestino);
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

    Paquete Pop()
    {
        if(Vacia()){
            cout<<"Pila Vacia"<<endl;
        }
        else
            {
				Paquete retorno(Tope->id,Tope->remitente,Tope->destinatario,Tope->idCorigen,Tope->idCdestino);

				Paquete* nodoTemp=Tope;
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
                    cout << "Id: "<<nodoTemp->id<<endl;
					cout << "Remitente: " << nodoTemp->remitente << endl;
					cout << "Destinatario: " << nodoTemp->destinatario << endl;
					cout << "Ciudad Origen: " << nodoTemp->idCorigen << endl;
					cout << "Ciudad Destino: " << nodoTemp->idCdestino << endl;
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
		Ciudad* Siguiente;

    Ciudad(string nombreC,int id)
    {
        nombre=nombreC;
		idCiudad = id;
		Siguiente = 0;
    }

    Ciudad()
    {
    }

    void ingresarPaquete(Paquete nuevo)
    {
        pilaPaquetesCiudad.Push(nuevo);
    }

    void verPilaPaquetes()
    {
        pilaPaquetesCiudad.VerPila();
    }

	
    Paquete sacarPaquete(int idPaquete)
    {
        Paquete* paqueteTemp;
        Paquete resultado;
        if(pilaPaquetesCiudad.Tope->id==idPaquete){
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
                if(paqueteTemp->id==idPaquete){
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

class ListaCiudades {
public:
	Ciudad* Primero;
	Ciudad* Ultimo;
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
			Ciudad* nuevaCiudad = new Ciudad(nombre, Size);
			Primero = Ultimo = nuevaCiudad;
		}
		else
		{
			if (!existeCiudad(nombre)) {
				Size++;
				Ciudad* nuevaCiudad = new Ciudad(nombre, Size);
				Ultimo->Siguiente = nuevaCiudad;
				Ultimo = nuevaCiudad;
			}
		}
		const int sizeMatriz = Size;
	}

	bool existeCiudad(string nombre) {
		Ciudad* tempCiudad;
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
		Ciudad* tempCiudad;
		tempCiudad = Primero;
		for (int i = 0; i <= Size; i++) {
			cout << "Id Ciudad: " << tempCiudad->idCiudad <<
				" Nombre: " << tempCiudad->nombre << endl;
			tempCiudad = tempCiudad->Siguiente;
		}
	}

	int getIdCiudad(string nombre) {
		Ciudad* tempCiudad;
		tempCiudad = Primero;
		for (int i = 0; i <= Size; i++) {
			if (tempCiudad->nombre == nombre)
			{
				return tempCiudad->idCiudad;
			}
			tempCiudad = tempCiudad->Siguiente;
		}
		return -1;
	}

	string getNombreCiudad(int id) {
		Ciudad* tempCiudad;
		tempCiudad = Primero;
		for (int i = 0; i <= Size; i++) {
			if (tempCiudad->idCiudad == id)
			{
				return tempCiudad->nombre;
			}
			tempCiudad = tempCiudad->Siguiente;
		}
		return "No Existe";
	}

};