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
void performOperation(double * prevNum, double currNum)
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

double value(string str)
{
	string term;
	vector<string> arr;
	for (unsigned int i = 0; i < str.length(); i++)
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
			term += str[i];
			break;
		}
	}
	arr.push_back(term);
	int start;
	double num, val = 0;
	for (unsigned int i = 0; i < arr.size(); i++)
	{
		num = 1;
		operatorEnum = eMultiply;
		start = 0;
		for (unsigned int j = 0; j < arr.at(i).size(); j++)
		{
			char currChar = arr.at(i).at(j);
			if (!(currChar > 47 && currChar < 58 || currChar == '.') && j != 0)
			{
				double currNum = atof(arr.at(i).substr(start, j - start).c_str());
				performOperation(&num, currNum);
				operatorEnum = operation(currChar);
				start = j + 1;
			}
		}
		double currNum = atof(arr.at(i).substr(start).c_str());
		performOperation(&num, currNum);
		val += num;
	}


	return(val);
}

int main()
{
	string input;
	cin >> input;
	cout << value(input);
	return 0;
}