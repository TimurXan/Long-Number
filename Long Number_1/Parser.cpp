#include "linkedList.h"
#include "Number.h"
#include <vector>
#include"Parser.h"
using namespace std;

#define tr_operator(x) ((x == '+'||x =='-'||x =='/'||x =='*' || x  == '#' ) || x == ')' || x == '(') ?( true):(false)
#define os_operator(x) ((x == '+'||x =='-'||x =='/'||x =='*' || x  == '#' ))  ?( true):(false)
int priority(char x);
void infix(FILE* f)
{
	linkedList <Number> num;//стек чисел
	vector<char> operat;//стек операторов

	Number temp;
	int sum = 0;//количество операторов
	vector<char> buf;//буфер где мы будем вычислять конечное число
	Number  x, y;//для вычисления(удобства)
	Number  res;
	char c = ' ', c_ = '+';

	operat.push_back('(');

	sum = 1;
	while ((c != ';'))
	{
		c = fgetc(f);

		if (isdigit(c))
			buf.push_back(c);
		else if ((c != ' ')) //&& (c != ';'))
		{
			if (c == ';')
				c = ')';

			if ((os_operator(c_) || (c_ == '(')) && (c != '('))//  + 12 ) ((tr_operator(c_)) && (c != '('))
			{
				temp.push(buf);
				num.push(temp);
				cout << ' ' << num.print_end();
			}

			c_ = c;
			buf.clear();


			if ((tr_operator(c)) && ((sum == 1) || (c == '(')))
			{
				operat.push_back(c);
				sum++;
			}
			else
				if (os_operator(c))//проверить на ( и )os_operator
				{
					{
						while ((priority(operat[sum - 1])
							>= priority(c))
							&& sum != 0)
						{
							x = num.pop();
							y = num.pop();

							cout << operat[sum - 1];

							switch (operat[sum - 1])
							{
							case '+':
								res = x + y;//Допилить,через деноминатор
								break;
							case '-':
								res = y - x;
								break;
								/*case '*':
								res = x * y;
								break;
								case '/':
								res = y / x;
								break;*/
							}

							num.push(res);
							sum--;
							operat.pop_back();
						}
						operat.push_back(c);
						sum++;
					}
				}
				else if (c == ')')
				{
					while (operat[sum - 1] != '(')//добавить проверку на количество скобок
					{
						x = num.pop();
						y = num.pop();

						cout << operat[sum - 1] << ' ';

						switch (operat[sum - 1])
						{
						case '+':
							res = x + y;
							break;
						case '-':
							res = y - x;
							break;
							/*case '*':
							res = x * y;
							break;
							case '/':
							res = y / x;
							break;*/
						}
						sum--;
						num.push(res);
						operat.pop_back();
					}
					sum--;
					operat.pop_back();
					if (sum == 0)
						c = ';';


				}
		}
	}
	cout << "= " << res;
}
int priority(char x) {
	switch (x)
	{
	case '+':
	case '-': return 0; break;
	case '*':
	case '/': return 1; break;
	case '#':return 2; break;
	case '(':return -1; break;
	case ')':return 3; break;
	}
}