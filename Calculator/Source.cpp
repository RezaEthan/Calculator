#include "Header.h"
#include "termClass.h"

int main()
{
	string input = "";
	cin >> input;
	cout << value(input) << endl;
	return 0;
}

inline eOperator operation(char op)
{

	eOperator opp = eNoOperation;
	char operators[] = { '/', '*', '-', '+', '^', '(', ')' };
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

//performs the calculation of the string
double value(string str)
{
	string term;
	vector<termClass *> terms;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		switch (str[i])
		{
		case '-':
			if (i != 0)
			{
				termClass * currTerm = new termClass();
				currTerm->setStrTerm(term);
				terms.push_back(currTerm);
				term = "";
			}
			term += '-';
			break;
		case '+':
			{
				termClass * currTerm = new termClass();
				currTerm->setStrTerm(term);
				terms.push_back(currTerm);
				term = "";
			}
			break;
		default:
			term += str[i];
			break;
		}
	}
	termClass * _term = new termClass();
	_term->setStrTerm(term);
	terms.push_back(_term);

	for (unsigned int i = 0; i < terms.size(); i++)
	{
		string currentIndexString = terms.at(i)->strTerm();
		if (currentIndexString.find('^') != string::npos)
		{
			int prevPos = 0;
			int prevPower = 0;
			do
			{
				char operators[] = { '/', '*', '-', '+', '(', ')' };
				prevPos = currentIndexString.find_first_of('^',prevPos);
				int prevOperator = currentIndexString.find_last_of(operators,prevPos);
				if (prevOperator == string::npos || prevOperator > prevPos)
				{
					prevOperator = -1;
				}


				int nextOperator = currentIndexString.find_first_of(operators,prevPos+1);

				double base = atof(currentIndexString.substr(prevOperator+1,prevPos-prevOperator).c_str());
				double expo = atof(currentIndexString.substr(prevPos + 1, nextOperator-prevPos).c_str());
				//3*3332^6
				double power = pow(base,expo);

				currentIndexString.replace(prevOperator+1,nextOperator - (prevOperator + 1),"&");
				terms.at(i)->setStrTerm(currentIndexString);
				terms.at(i)->powValues.push_back(power);

				prevPos = currentIndexString.find_first_of('^',prevPos);
				prevPower = currentIndexString.find_first_of('&',prevPower + 1);

			} while(prevPos != string::npos);
		}
	}

	int start;
	double num, val = 0;
	for (unsigned int i = 0; i < terms.size(); i++)
	{
		num = 1;
		operatorEnum = eMultiply;
		start = 0;
		unsigned int num_pows = 0;
		termClass * currTerm = terms.at(i);
		for (unsigned int j = 0; j < terms.at(i)->strTerm().size(); j++)
		{
			char currChar = terms.at(i)->strTerm().at(j);
			if (currChar < 47 || currChar > 58 || currChar == '.' || (j == '-' && j != 0))
			{
				double currNum;
				if (currChar == '&')
				{
					currNum = terms.at(i)->powValues.at(num_pows);
					num_pows++;
					performOperation(&num, currNum);
				}
				else if (j > 0)
				{
					if (terms.at(i)->strTerm().at(j-1) != '&')
					{
						currNum = atof(terms.at(i)->strTerm().substr(start, j - start).c_str());
						performOperation(&num, currNum);
						operatorEnum = operation(currChar);

					}
					else if (terms.at(i)->strTerm().at(j-1) == '&')
					{
						operatorEnum = operation(currChar);
					}
				}

				else
				{
					currNum = atof(terms.at(i)->strTerm().substr(start, j - start).c_str());
					performOperation(&num, currNum);
					operatorEnum = operation(currChar);
				}

				start = j + 1;
			}

			else if (j == terms.at(i)->strTerm().length()-1)
			{
				double currNum = atof(terms.at(i)->strTerm().substr(start).c_str());
				performOperation(&num, currNum);
			}
		}
		currTerm->setNumericValue(num);
	}

	for (unsigned int i = 0; i < terms.size(); i++)
	{
		val += terms.at(i)->numericValue();
	}

	return(val);
}
