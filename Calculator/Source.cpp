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

double value(string str)
{
	string term;
	vector<string> arr;
	for (int i = 0; i < str.length(); i++)
	{
		switch (str[i])
		{
		case '-':
				if (i != 0 && (str[i-1] > 47 && str[i-1] < 58))
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
	float num, val = 0;
	for (int i = 0; i < arr.size(); i++)
	{
		num = 1;
		operatorEnum = eMultiply;
		start = 0;
		for (int j = 0; j < arr.at(i).size(); j++)
		{
			if (!(arr.at(i).at(j) > 47 && arr.at(i).at(j) < 58 || arr.at(i).at(j) == '.' || arr.at(i).at(j) == '-') && j != 0)
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
		val += num;
	}
	return(val);
}

int main()
{
	string input;
	cin >> input;
	cout << value(input)<<endl;
	return 0;
}