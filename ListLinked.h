#include <ostream>
#include "List.h"
#include "Node.h"

template<typename T>
class ListLinked : public List<T>
{
	private:
		Node<T>* first;
		int n;
	public:
		ListLinked() //Método constructor sin argumentos
		{
			n = 0;
			first = nullptr;
		}

		~ListLinked() //Método destructor
		{
			Node<T>* aux;
			while(aux != nullptr)
			{
				aux = first->next;
				delete[] first;
				first = aux;
			}
		}

		T operator[](int pos) //Sobrecarga (overload) del operador [] para indicar elemento almacenado en la posición requerida
		{
			if(pos < 0 || pos > size() - 1) throw out_of_range("Posición fuera del rango (0, size() - 1)");
			Node<T>* aux = first; //Creo un nodo auxiliar para recorrer la lista
			for(int i = 0; i <= pos; i++) //Recorro la lista con un bucle for
			{
				aux = aux->next;
			}
			return aux->data; //Devuelvo el valor almacenado en la posición especificada
		}

		friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) //Sobrecarga del operador << para imprimir una
											      //instancia de la lista
		{
			out << "List (Node): ";
			Node<T>* aux = list.first; //Creo un nodo auxiliar para recorrer la lista
			for(int i = 0; i < list.n; i++)
			{
				out << aux->data; //Almaceno en out el valor del nodo actual
				if(i < list.n - 1) out << " -> "; //Si no es la ultima posición pongo una flecha entre medias
				aux = aux->next; //Avanzo al siguiente nodo
			}
			return out;
		}

		//Métodos heredados
		
		void insert(int pos, T e) override
		{
			Node<T>* newNode = new Node<T>(e); //Creo un nuevo nodo para insertar el elemento en la lista
			Node<T>* aux = first; //Creo un nodo auxiliar para recorrer la lista
			for(int i = 0; i < pos; i++) //Recorro la lista con un bucle for
			{
				aux = aux->next;
			}
			if(pos == 0)
			{
				first = newNode;
				first->next = aux; //Pongo a aux (que es una copia del primer elemento) en segunda posición
				first->data = e; //Cambio el primer elemento al elemento especificado
			}
			else
			{
				newNode->next = aux->next; //Pongo el nuevo nodo delante del nodo que estaba en la posición especificada
				aux->next = newNode; //Pongo el nuevo nodo detrás del nodo que estaba delante del nodo antiguo
				newNode->data = e; //Almaceno en el nuevo nodo el elemento especificado
			}
			n++;
		}

		void append(T e) override
		{
			insert(n - 1, e); //Llamo al metodo insert() en la ultima posición de la lista
		}

		void prepend(T e) override
		{
			insert(0, e); //Llamo al metodo insert() en la primera posición de la lista
		}

		T remove(int pos) override
		{
			if(pos < 0 || pos > n - 1) throw out_of_range("Posición fuera del rango (0, size() - 1)");
			Node<T>* aux1 = first; //Creo dos punteros para recorrer la lista
			Node<T>* aux2;
			for(int i = 0; i < pos - 1; i++) //Recorro la lista con un bucle for
			{
				aux2 = aux1; //aux2 marca la posición de antes del elemento que queremos eliminar
				aux1 = aux1->next; //aux1 marca la posición del elemento que queremos eliminar
			}
			aux2->next = aux1->next; //Eliminamos el puntero de la posición especificada
						 //desvinculandolo de la posición anterior y posterior
			return aux1->data; //Devolvemos el elemento almacenado en la posición eliminada
		}

		T get(int pos) override
		{
			if(pos < 0 || pos > n - 1) throw out_of_range("Posición fuera del rango (0, size() - 1)");
			Node<T>* aux = first; //Creo un nodo auxiliar para recorrer la lista
			for(int i = 0; i < pos; i++) //Recorro la lista con un bucle for
			{
				aux = aux->next;
			}
			return aux->data;
		}

		int search(T e) override
		{
			int pos = 0; //Creo un contador para marcar la posición
			Node<T>* aux = first; //Creo un nodo auxiliar para recorrer la lista
			while(aux->data != e) //Recorro la lista con un bucle while para detectar si se ha encontrado el elemento
			{
				aux = aux->next;
				pos++;
			}
			if(aux != nullptr) return pos;
			else return -1;
		}

		bool empty() override
		{
			if(n = 0) return true;
			else return false;
		}

		int size() override
		{
			return n;
		}
};
