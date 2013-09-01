#include "Header.h"


int main()
{
	string input = "";
	cin >> input;
	cout << value(input);
	return 0;
}

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

	case ePower:
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

	for (unsigned int i = 0; i < arr.size(); i++)
	{
		string currentIndexString = arr.at(i);
		if (currentIndexString.find('^') != string::npos)
		{
			size_t prevPos = 0;
			do
			{
				char operators[7] = { '/', '*', '-', '+', '^', '(', ')' };
				prevPos = currentIndexString.find_first_of('^',prevPos);
				size_t prevOperator = currentIndexString.find_last_of(operators,prevPos-1);
				size_t nextOperator = currentIndexString.find_first_of(operators,prevPos+1);

				double base = atof(currentIndexString.substr(prevOperator+1,prevPos-prevOperator).c_str());
				double expo = atof(currentIndexString.substr(prevPos + 1, nextOperator-prevPos).c_str());
					//3*3332^6
				double power = pow(base,expo);
				cout << currentIndexString << endl;
				/*
				Can't convert float -> string with specifying how accurate (how many decimals)
				Float is never ending and by converting it you lose accuracy of calculator
				*/
				//currentIndexString.replace(prevOperator+1,nextOperator-prevOperator,);

			}while(prevPos != string::npos);
		}
	}

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
