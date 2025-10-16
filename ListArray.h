#include <iostream>
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
};
