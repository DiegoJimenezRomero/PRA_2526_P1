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
			new T* arr;
			arr = this->arr;
			delete[] this->arr;
			this->arr = &arr;
			max = new_size;
		}
	public:
		ListArray()
		{
			arr[MINSIZE];
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
};
