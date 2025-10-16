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
			n = MINSIZE;
			max = MINSIZE;
		}
		~ListArray();
		T operator[](int pos)
		{
			return arr[pos];
		}
		friend std::ostream&operator<<(std::ostream &out, const ListArray<T> &list)
		{
			return list.arr;
		}
		
		//Métodos heredados
		
		void insert(int pos, T e) override
		{
			if(pos < 0 || pos > n - 1) throw out_of_range;
			//Añadimos en un array auxiliar los elementos que hay desde la posición donde se quiere insertar
			//el nuevo elemento hasta el final del array
			aux = new T[n + 1 - pos];
			for(int i = pos - 1; i < n; i++)
			{
				aux[i - pos - 1] = arr[i];
			}
			if(n = max) //Comprobamos que el array tenga espacio para más elementos
			{
				arr.resize(max + 1); //Actualizamos el tamaño del array
			}
			arr[pos - 1] = e; //Insertamos el elemento
			for(int i = pos; i < n; i++) //Metemos los elementos que habian desde esa posición hasta el final
			{
				arr[i] = aux[i - pos];
			}
			n++; //Actualizamos la cantidad de elementos que contiene el array
		}
		void append(T e) override
		{
			//Llamamos al metodo insert en la ultima posicion del array
			insert(n - 1, e);
		}
		void prepend(T e) override
		{
			//Llamamos al metodo insert en la primera posicion del array
			insert(0, e);
		}
		void remove(int pos) override
		{
			for(int i = pos - 1; i < n - 1; i++) //Elimino el elemento en la posición indicada copiando en cada elemento
							     //desde esa el siguiente en el array
			{
				arr[i] = arr[i + 1];
			}
			arr[n - 1] = T(); //Copio en el ultimo elemento un elemento vacio
			n -= 1; //Cambio la variable de elementos del array
		}
		T get(int pos) override
		{
			if(pos < 0 || pos > n - 1) throw out_of_range("Posicion introducida fuera del rango (0, size() - 1)");
			return arr[pos - 1];
		}
		int search(T e) override
		{
			int counter = 0; //Creo un contador para guardar la posición del array
			while(counter < n)
			{
				if(arr[counter] == e) break; //Si el elemento almacenado en esa posición es el buscado, se sale del bucle
				else counter++; //Si no, se incrementa el contador
			}
			return -1//Se devuelve counter + 1 porque counter es la posición en el array, no en la lista
};
