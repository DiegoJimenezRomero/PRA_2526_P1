#include <iostream>
using namespace std;
#ifndef LIST_H
#define LIST_H

template <typename T>
class List
{
	public:
		virtual void insert(int pos, T e) = 0;
		virtual void append(T e) = 0;
		virtual void prepend(T e) = 0;
		T remove(int pos) = 0;
		T get(int pos) = 0;
		int search(T e) = 0;
		bool empty();
		int size();
};

#endif
