#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int idpaquetes=0;

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

	Paquete(){
		id = 0;
		remitente = "0";
		destinatario = "0";
		idCorigen =0;
		idCdestino = 0;
		NextPaquete = 0;
	}

	string verPaquete() {
		return "Id: " + to_string(id) + "\nRemitente: " + remitente + "\nDestinatario: " + destinatario + "\nOrigen: " + to_string(idCorigen) + "\nDestino: " + to_string(idCdestino);
	}

    ~Paquete(){}
};


void mostrarPila(vector<Paquete> paquetes) {
	RenderWindow window(VideoMode(400, 600), "PIla de la Ciudad");

	Font fuente;
	if (!fuente.loadFromFile("arial.ttf"))
	{
		return;
	}

	vector<RectangleShape> cuadros;
	vector<Text> textos;

	float y = 10;
	float espacio;
	for (int i = 0; i < paquetes.size(); i++) {
		
		Text text;
		text.setFont(fuente);
		text.setString(paquetes.at(i).verPaquete());
		text.setCharacterSize(20);
		text.setFillColor(Color::White);
		text.setStyle(Text::Bold);
		text.setPosition(10, y);

		RectangleShape cuadro(Vector2f(text.getLocalBounds().width+2, text.getLocalBounds().height+6));
		cuadro.setFillColor(Color::Blue);
		cuadro.setOutlineColor(Color::White);
		cuadro.setOutlineThickness(3);
		cuadro.setPosition(10, y);

		espacio = text.getOrigin().y + text.getLocalBounds().height;
		y = y + espacio+10;
		cuadros.push_back(cuadro);
		textos.push_back(text);

	}
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		for (int i = 0; i < textos.size(); i++) {
			window.draw(cuadros.at(i));
			window.draw(textos.at(i));
		}
		window.display();
	}
}

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
				vector<Paquete> paquetes;
                Paquete* nodoTemp=Tope;
                do
                {
					Paquete agregar;
					agregar.id = nodoTemp->id;
					agregar.remitente = nodoTemp->remitente;
					agregar.destinatario = nodoTemp->destinatario;
					agregar.idCorigen = nodoTemp->idCorigen;
					agregar.idCdestino = nodoTemp->idCdestino;
					paquetes.push_back(agregar);
                    nodoTemp=nodoTemp->NextPaquete;
                }while(nodoTemp!=0);
				mostrarPila(paquetes);
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
		if (nombre == "")return;

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
		cout << setw(2)<<"Id" << setw(20) << "Nombre"<<endl;
		for (int i = 0; i <= Size; i++) {
			cout<<setw(2)<<tempCiudad->idCiudad << setw(20) << tempCiudad->nombre << endl;
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

	void verPilaCiudad(int idCiudad) {
		Ciudad* tempCiudad;
		tempCiudad = Primero;
		for (int i = 0; i <= Size; i++) {
			if (tempCiudad->idCiudad == idCiudad)
			{
				tempCiudad->verPilaPaquetes();
				return;
			}
			tempCiudad = tempCiudad->Siguiente;
		}
		cout << "No existe esta ciudad";
	}

	void agregarPaqueteCiudad(int idDestino, Paquete nuevoPaquete) {
		Ciudad* tempCiudad;
		tempCiudad = Primero;
		for (int i = 0; i <= Size; i++) {
			if (tempCiudad->idCiudad == idDestino)
			{
				tempCiudad->ingresarPaquete(nuevoPaquete);
				return;
			}
			tempCiudad = tempCiudad->Siguiente;
		}
		cout << "No existe esta ciudad";
	}

	Paquete retirarPaqueteCiudad(int idCiudad, int idpaquete) {
		Ciudad* tempCiudad;
		tempCiudad = Primero;
		for (int i = 0; i <= Size; i++) {
			if (tempCiudad->idCiudad == idCiudad)
			{
				return tempCiudad->sacarPaquete(idpaquete);
			}
			tempCiudad = tempCiudad->Siguiente;
		}
		cout << "No existe esta ciudad";
	}

};