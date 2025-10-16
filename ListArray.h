#include <iostream>
using namespace std;
#include "List.h"

template <typename T>
class ListArray : public List<T>
{
	private:
		T* arr;
		int max;
		int n;
		static const int MINSIZE = 2;
		void resize(int new_size)
		{
			//Crear nuevo array
			T* NewArr = new T[new_size];
			//Copiar elementos del viejo array al nuevo
			for(int i = 0; i < n; i++)
			{
				NewArr[i] = arr[i];
			}
			//Eliminamos el puntero al antiguo array
			delete[] arr;
			//Cambiamos la variable de tamaño del array
			max = new_size;
			//Cambiamos el puntero del nuevo array al puntero original
			arr = NewArr;
		}
	public:
		ListArray()
		{
			//Creamos un nuevo array dinamico
			arr = new T[MINSIZE];
			n = 0;
			max = MINSIZE;
		}
		~ListArray()
		{
			delete[] arr;
		}
		T operator[](int pos)
		{
			if(pos < 0 || pos > n - 1) throw out_of_range("Posicion introducida fuera del rango (0, size() - 1)");
			return arr[pos];
		}
		friend std::ostream&operator<<(std::ostream &out, const ListArray<T> &list)
		{
			out << "["; //Ponemos el primer corchete del array
			for(int i = 0; i < list.n; i++)
			{
				out << list.arr[i]; //Guardamos en la respuesta los elementos del array
				if(i < list.n - 1) out << ", "; //Mientras que no sea el ultimo elemento ponemos una coma
			}
			out << "]"; //Cerramos el corchete
			return out; //Devolvemos la respuesta
		}
		
		//Métodos heredados
		
		void insert(int pos, T e) override
		{
			if(pos < 0 || pos > max - 1) throw out_of_range("Posicion introducida fuera del rango (0, max - 1)");
			//Añadimos en un array auxiliar los elementos que hay desde la posición donde se quiere insertar
			//el nuevo elemento hasta el final del array
			T* aux = new T[n + 1 - pos];
			for(int i = pos + 1; i < n; i++)
			{
				aux[i - pos - 1] = arr[i];
			}
			if(n == max) //Comprobamos que el array tenga espacio para más elementos
			{
				this->resize(max + 1); //Actualizamos el tamaño del array
			}
			arr[pos] = e; //Insertamos el elemento
			for(int i = pos + 1; i < n; i++) //Metemos los elementos que habian desde esa posición hasta el final
			{
				arr[i] = aux[i - pos - 1]; 
			}
			n++; //Actualizamos la cantidad de elementos que contiene el array
		}
		void append(T e) override
		{
			//Llamamos al metodo insert en la ultima posicion del array
			insert(n, e);
		}
		void prepend(T e) override
		{
			//Llamamos al metodo insert en la primera posicion del array
			insert(0, e);
		}
		T remove(int pos) override
		{
			if(pos < 0 || pos > n - 1) throw out_of_range("Posicion introducida fuera del rango (0, size() - 1)");
			T aux = arr[pos]; //Guardo el valor a eliminar en una variable auxiliar
			for(int i = pos; i < n - 1; i++) //Elimino el elemento en la posición indicada copiando en cada elemento
							     //desde esa el siguiente en el array
			{
				arr[i] = arr[i + 1];
			}
			arr[n - 1] = T(); //Copio en el ultimo elemento un elemento vacio
			n -= 1; //Cambio la variable de elementos del array
			return aux; //Devuelvo el valor eliminado
		}
		T get(int pos) override
		{
			if(pos < 0 || pos > n - 1) throw out_of_range("Posicion introducida fuera del rango (0, size() - 1)");
			return arr[pos];
		}
		int search(T e) override
		{
			int counter = 0; //Creo un contador para guardar la posición del array
			while(counter < n)
			{
				if(arr[counter] == e) return counter + 1; //Si el elemento almacenado en esa posición es el buscado
									  //se devuelve la posición. Se devuelve counter + 1 porque el contador
									  //marca la posición del array, no de la lista
				else counter++; //Si no, se incrementa el contador
			}
			return -1; //Si se ha salido del contador, se devuelve -1 porque no está el elemento buscado en la lista
		}
		bool empty() override
		{
			if(n == 0) return true; //Si la cantidad de elementos del array es 0, el array esta vacío
			else return false; //Si no, no está vacío
		}
		int size() override
		{
			return n; //n contiene la cantidad de elementos del array
		}
};
