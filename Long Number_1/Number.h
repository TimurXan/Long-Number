#pragma once
#include <iostream>
#include "linkedList.h"
#include <vector>
using namespace std;
class Number
{
	//int length;
	linkedList<short int> st;
	bool symbols;//0 - +//1 - '-'
public:
	//Number operator + (const Number & num, char* str);
	Number() { st.length = 0; symbols = false; };
	Number(const Number& num);

	Number operator+ ( Number & num);
	Number operator- (Number & num);
	Number operator* (Number & num);
	Number operator/ (Number & num);
	Number& operator=( Number&value);

	friend int analysis(char c, Number& num_1, Number &num_2, Number &result);
	friend istream& operator >> (istream& is, Number&);
	friend ostream& operator<< (ostream& os, const Number& value);

	void push(vector<char>& str);
	friend void antigorner(vector<char>&str, Number& value);
	void print_length() { cout << st.length; }

	template<typename Tname>
	Element<Tname> print_st_end() { return st.print_end(); }

	~Number() {};
};
