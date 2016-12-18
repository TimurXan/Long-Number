#pragma once
#include <iostream>
using namespace std;
template<typename Tname>
class linkedList;

template<typename T>
class Element
{
public:
	T item;
	Element* next;
	Element(T value = 0, Element *ptr = 0) :item(value), next(ptr) {};
	friend ostream& operator<< (ostream& os, Element<T>& el)
	{
		os << el.item;
		return os;
	}
	friend linkedList<T>;

	~Element() {  };
};


template<typename Tname>
class linkedList
{
public:
	long int length;///Поправить бы
	Element<Tname> *front;
	linkedList() { front = NULL; length = 0; }
	~linkedList();
	Tname pop();
	bool empty() { return (front == 0); }
	void push(const Tname value);
	void push_back(const Tname value);
	linkedList<Tname>& operator=(const linkedList<Tname>&value);
	Element<Tname> print_end() { return *front; }
	template<typename T>
	friend ostream& operator<< (ostream& os, const linkedList<T>& st);
	Tname& operator[](int);

};
template<typename Tname>
Tname& linkedList<Tname>::operator [](int value)
{
	Element<Tname>* temp=front;
	if (value > length) {
		cout << "Error index";
		exit(-4);
	}
	for ( int i = 0; i < value; i++)
		temp=temp->next;
	return temp->item;
}

template<typename Tname>
Tname linkedList<Tname>::pop()
{
	if (front)
	{
		Tname value = front->item;
		Element<Tname> *pNext = front;
		front = front->next;
		length--;
		delete pNext;
		return value;
	}
	else
	{
		cout << "Error - linkedList is empty" << endl;
		exit(-1);
	}
}


template<class Tname>
void linkedList<Tname>::push(const Tname value)

{
	Element<Tname> *pNext = new Element<Tname>(Element<Tname>(value, front));
	length++;
	front = pNext;

}
template<class Tname>
void linkedList<Tname>::push_back(const Tname value)

{
	Element<Tname> *pNext = front;
	if (pNext != NULL)
	{
		while (pNext->next != NULL)
			pNext = pNext->next;

		pNext->next = new Element<Tname>(Element<Tname>(value, NULL));
	}
	else
		front = new Element<Tname>(Element<Tname>(value, NULL));
	length++;
}
template<typename Tname>
linkedList<Tname>::~linkedList<Tname>()
{
	while (front)
	{
		pop();
	}
}
template<typename Tname>
linkedList<Tname>& linkedList<Tname>::operator=(const linkedList<Tname>&value)//////////!переписать
{
	while (!empty())
	{
		pop();
	}
	Element<Tname>* temp = value.front;
	while (temp)
	{
		push(temp->item);
		temp=temp->next;
	}
	return *this;
}


template<typename Tname>
ostream& operator<< (ostream& os, const linkedList<Tname>& st)

{
	Element<Tname>* temp = st.front;
	while (temp != 0)
	{
		os << *(temp) << " ";
		temp = (temp)->next;
	}
	return os;

}
