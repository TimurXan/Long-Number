#include "Number.h"
#include <vector>
#include "linkedList.h"

#include <iostream>
using namespace std;

istream& operator >> (istream& is, Number& value)
{
	char ch = ' ';
	vector<char> str;

	while (ch != '\n')
	{
		is.get(ch);

		if ((ch != '\n') &&(ch!=' '))
		{
			str.push_back(ch);
		}
	}

	while (!value.st.empty())
		value.st.pop();
	if (str.empty())
		cout << "Error enter"<<endl;
	else
		antigorner(str, value);
	return is;
}

void antigorner(vector<char>&str, Number& value)
{
	//Проверить на пустую строку!!!!!!!!!!!
	int i = 0;
	int num_div = 0;
	int num_mod = 0;
	int index = 0;//Указывает на начало буффера
	if (str[i] == '-')
	{
		value.symbols = true;
		i++;
	}
	do {
		while (i < (str.size()))
		{

			num_mod = (num_mod * 10 + str[i++] - '0');
			num_div = (num_mod) / 256;//!!!!!!

			if ((num_div>0) || (index != 0))
				str[index++] = num_div + '0';

			num_mod = num_mod % 256;//!!!!!
		}

		if (index>0)
		{

			str.resize(index);
			i = 0;
			index = 0;
			value.st.push((short int)num_mod);
		//	value.st.length++;
			num_mod = 0;
		}
		else
		{
			value.st.push((short int)num_mod);
			str.clear();
			//value.st.length++;
		}

	} while (str.size()>0);
}
ostream& operator<< (ostream& os, const Number& value)
{
	if (value.symbols)
		os << '-' ;
	os << value.st << endl;
	return os;
}

Number Number::operator+ (Number & num) 
{
	Number result;
	int re_tmp = 0;
	int i = 0;
	int znak;//0 : +,1: = -,2 : ничего
	znak = analysis('+', *this,num,result);
	if ((znak == 0) || (znak == 1))
	{
		while ((i < st.length) || (i < num.st.length))
		{
			if ((i < st.length) && (i < num.st.length))
				re_tmp = re_tmp + st[i] + num.st[i];
			else if ((i < st.length))
				re_tmp = re_tmp + st[i];
			else
				re_tmp = re_tmp + num.st[i];
			result.st.push(re_tmp % 256);
			re_tmp /= 256;
			i++;
		}
		while (re_tmp > 0)
		{
			result.st.push(re_tmp % 256);
			re_tmp /= 256;
		}
		if (znak == 1)
			result.symbols = true;
	}
	
	return result;
}
Number Number::operator- (Number & num)
{

	Number result;
	int re_tmp = 0;
	int i = 0;

	int znak;//0 : +,1: = -,2 : ничего
	znak = analysis('-', *this, num, result);
	if (znak == 0)
	{
		while ((i < st.length) || (i < num.st.length))
		{

			if ((i < st.length) && (i < num.st.length))
				re_tmp = re_tmp + st[i] - num.st[i];//ПРАВКИ НАЧИНАЮТСЯ ОТСЮДА
			else if ((i < st.length))
				re_tmp = re_tmp + st[i];
			else
				re_tmp = re_tmp - num.st[i];

			if (re_tmp < 0)
			{
				result.symbols = true;
				re_tmp = -re_tmp;
			}

			result.st.push(re_tmp % 256);//!!!
			re_tmp /= 256;
			i++;
		}
		while (re_tmp > 0)
		{
			result.st.push(re_tmp % 256);
			re_tmp /= 256;
		}
	}
	return result;
}

Number Number::operator* (Number & num)
{
	Number result;
	Number result1;
	int re_tmp = 0;
	int i = 0,k=0;

	int znak;//0 : +,1: -,2 : ничего
	znak = analysis('*', *this, num, result);
	if ((znak == 0)||(znak==1))
	{
			for (k = st.length-1; k >= 0; k--)
			{
				while ((i < st.length) || (i < num.st.length))
				{
					re_tmp = re_tmp + st[k] * num.st[i];
					if (k == st.length-1)
					{
						result.st.push(re_tmp % 256);//!!!
					}
					else
					{
						result1.st.push(re_tmp % 256);
					}
					re_tmp /= 256;
					i++;
				}

				if (k != st.length-1)
				{
					for(int l = k;l!= st.length - 1;l++)
						result1.st.push_back(0);
					result = result + result1;	
				}
				i = 0;
				while(!result1.st.empty())
					result1.st.pop();
			}
		while (re_tmp > 0)
		{
			result.st.push(re_tmp % 256);
			re_tmp /= 256;
		}
		if(znak == 1)
			result.symbols = true;
	}

	return result;
}

Number Number::operator/ (Number & num)
{

	Number result;
	int re_tmp = 0;

	int znak = analysis('/', *this, num, result);

	if (st.length < num.st.length)
		result.st.push(0);
	else
	{
		Number result1 = *this;
		if (st.length = num.st.length)
		{
			result.st.push(0);
			while (result1.symbols != 1)
			{
				result1 = result1 - num;
					result.st[0] = result.st[0] + 1;
			}
			result.st[0] = result.st[0] - 1;
		}
		else
		{
			Number result2=num;
			for (int i = st.length - num.st.length; i < st.length - 1; i++)
			{
				result2.st.push_back(0);
			}
			while (result1.symbols != 1)
			{
				result1 = result1 - num;
				result.st[0] = result.st[0] + 1;
			}
		}
	}
	
	return result;
}
Number::Number(const Number& num)
{
	linkedList<short int > temp;
	temp = num.st;
	temp.length = num.st.length;
	while (!temp.empty())
		st.push(temp.pop());
	symbols = num.symbols;
}

void Number::push(vector<char>& str)
{
	while (!st.empty())
		st.pop();
	antigorner(str, *this);
}

Number& Number::operator=(Number&value) 
{
	while (st.length)
	{
		st.pop();
	}
	int i = st.length-1;
	while (i>=0)	
	{
		this->st.push(value.st[i]);
			i--;
	}
	symbols = value.symbols;
	return *this;
}


int analysis(char c, Number& num_1, Number &num_2, Number &result)
{
	int re_tmp = 0;
	int i = 0;
	switch (c)
	{
	case '+':
		if ((!num_1.symbols) && (!num_2.symbols))
			return false;
		else if ((num_1.symbols) && (num_2.symbols))
			return true;
		else if (num_1.symbols)
		{
			num_1.symbols = false;
			result = num_2 - num_1;
			num_1.symbols = true;//обязательно в минусе обработать знак
			return 2;
		}
		else if (num_2.symbols)
		{
			num_2.symbols = false;
			result = num_1 - num_2;
			num_2.symbols = true;//обязательно в минусе обработать знак
			return 3;
		}
		break;
	case '-':
		if ((!num_1.symbols) && (!num_2.symbols))
			return false;
		else if ((num_1.symbols) && (num_2.symbols))//-1--4
		{
			num_2.symbols = false;
			num_1.symbols = false;
			result = num_2 - num_1;
			num_2.symbols = true;
			num_1.symbols = true;
			return 2;
		}
		else if (num_1.symbols)//-1-4
		{
			num_1.symbols = false;
			result = num_1 + num_2;
			result.symbols = true;
			num_1.symbols = true;
			return 3;
		}
		else if (num_2.symbols)//1--4
		{
			num_2.symbols = false;
			result = num_1 + num_2;
			result.symbols = false;
			num_2.symbols = true;
			return 4;
		}
		break;
	case '*':
		if (((!num_1.symbols) && (!num_2.symbols)) || (num_1.symbols) && (num_2.symbols))
			return false;
		else
			return true;
		break;
	case '/':
		if (((!num_1.symbols) && (!num_2.symbols)) || (num_1.symbols) && (num_2.symbols))
			return false;
		else
			return true;
		break;
	}
}