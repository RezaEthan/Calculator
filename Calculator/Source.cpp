#include <iostream>
#include <string>
#include <vector>
#include "Header.h"
using namespace std;

inline eOperator operation(char op)
{

	eOperator opp = eNoOperation;
	char operators[7] = { '/', '*', '-', '+', '^', '(', ')' };
	for (int k = 0; k < 7; k++)
		if (op == operators[k])
			opp = (enum eOperator)k;

	return opp;
}
void performOperation(float * prevNum, float currNum)
{
	switch (operatorEnum)
	{
	case eMultiply:
		*prevNum *= currNum; 
		break;

	case eDivide:
		*prevNum /= currNum;
		break;

	case eNoOperation:
		cout << "NO OPERATION" << endl;
		break;

	}
}

int value(string str)
{
	string term;
	vector<string> arr;
	for (int i = 0; i < str.length(); i++)
	{
		switch (str[i])
		{
		case '-':
			if (i != 0)
			{
				arr.push_back(term);
				term = "";
			}
			term += '-';
			break;
		case '+':
			arr.push_back(term);
			term = "";
			break;
		default:

			break;
		}
	}
	arr.push_back(str);
	int start;
	float num;
	for (int i = 0; i < arr.size(); i++)
	{
		num = 1;
		operatorEnum = eMultiply;
		start = 0;
		for (int j = 0; j < arr.at(i).size(); j++)
		{
			if (!(arr.at(i).at(j) > 47 && arr.at(i).at(j) < 58) && j != 0)
			{
				float currNum = atof(arr.at(i).substr(start, j - start).c_str());
				performOperation(&num, currNum);
				operatorEnum = operation(arr.at(i).at(j));
				start = j + 1;
			}
		}
		float currNum = atof(arr.at(i).substr(start).c_str());
		performOperation(&num, currNum);
		cout << num << endl;
	}


	return(0);
}

int main()
{
	string input;
	cin >> input;
	cout << value(input);
	return 0;
}