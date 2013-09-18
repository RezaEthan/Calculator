#include "Header.h"
#include "termClass.h"

int main()
{
	string input = "";
	do {
		cin >> input;
		cout << value(input) << endl;
	}while(input != "0");
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

double value(string str) //performs the calculation of the string
{
	string term;
	vector<termClass *> terms;
	bool inBrac = false;
	for (unsigned int i = 0; i < str.length(); i++) //sorts the string into terms, turning each into a termClass and putting them in a vector
	{
		switch (str[i])
		{
		case '-':
			if ((i != 0 && ((str[i-1] > 47 && str[i-1] < 58) || str[i-1] == ')')) && inBrac == false) 
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
				if (inBrac == false)
				{
					termClass * currTerm = new termClass();
					currTerm->setStrTerm(term);
					terms.push_back(currTerm);
					term = "";
				}
				else
					term += '+';
			}
			break;
		case '(':
			inBrac = true;
			term += '(';
			break;
		case ')':
			inBrac = false;
			term += ')';
			break;
		default:
			term += str[i];
			break;
		}
	}
	termClass * _term = new termClass();
	_term->setStrTerm(term);
	terms.push_back(_term);

	for (unsigned int i = 0; i < terms.size(); i++) //finds the values of the brackets and stores them in a double array, replacing the brackets with $
	{
		string currentIndexString = terms.at(i)->strTerm();
		if (currentIndexString.find('(') != string::npos)
		{
			int hold;
			int firstBrac = currentIndexString.find_first_of('(',0);
			int secondBrac = currentIndexString.find_first_of(')',firstBrac);
			do
			{
				string replacer = "";
				terms.at(i)->bracValues.push_back(value(currentIndexString.substr(firstBrac+1,secondBrac-firstBrac-1))); 
				if (firstBrac != 0 && ((currentIndexString[firstBrac-1] > 48 && currentIndexString[firstBrac-1] < 58) || currentIndexString[firstBrac-1] == '$' || currentIndexString[firstBrac-1] == '&'))
					replacer += '*';
				replacer += '$';
				if (secondBrac != currentIndexString.length()-1 && ((currentIndexString[secondBrac+1] > 48 && currentIndexString[secondBrac+1] < 58) || currentIndexString[secondBrac+1] == '$' || currentIndexString[secondBrac+1] == '&'))
					replacer += '*';
				hold = currentIndexString.find_first_of('(',secondBrac);
				currentIndexString.replace(firstBrac,secondBrac-firstBrac+1,replacer);
				terms.at(i)->setStrTerm(currentIndexString);
				firstBrac = currentIndexString.find_first_of('(',firstBrac);
				secondBrac = currentIndexString.find_first_of(')',hold);
			}while (firstBrac != string::npos);
		}
	}
	for (unsigned int i = 0; i < terms.size(); i++) //same as above but for powers, and replaces with &
	{
		string currentIndexString = terms.at(i)->strTerm();
		if (currentIndexString.find('^') != string::npos)
		{
			int prevPos = 0;
			int prevPower = 0;
			int currBracIndex = 0;
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
				double base = 0;
				if (currentIndexString.substr(prevPos - 1, 1) == "$") //there was a bracket value behind the ^ making the base the bracket value
				{
					base = terms.at(i)->bracValues.at(currBracIndex);
					currBracIndex++;
				}
				else
				{
					base = atof(currentIndexString.substr(prevOperator+1,prevPos-prevOperator).c_str());
				}
				double expo = atof(currentIndexString.substr(prevPos + 1, nextOperator-prevPos).c_str());
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
	for (unsigned int i = 0; i < terms.size(); i++) //calculates the values of each term
	{
		num = 1;
		operatorEnum = eMultiply;
		start = 0;
		unsigned int num_pows = 0;
		unsigned int num_bracs = 0;
		termClass * currTerm = terms.at(i);
		for (unsigned int j = 0; j < terms.at(i)->strTerm().size(); j++)
		{
			char currChar = terms.at(i)->strTerm().at(j);
			if (((currChar < 48 || currChar > 58) && (currChar != '-' && currChar != '.' && currChar != '$' && currChar != '&')) || (currChar == '-' && j != 0))
			{ //^if currchar isn't a number and isn't a - or . or $ or &; or if its - and is array element 0
				double currNum;
				if (j > 0)
				{
					if (terms.at(i)->strTerm().at(j-1) == '&')
					{
						currNum = terms.at(i)->powValues.at(num_pows);
						num_pows++;
						performOperation(&num, currNum);
						operatorEnum = operation(currChar);
					}
					else if (terms.at(i)->strTerm().at(j-1) == '$')
					{
						currNum = terms.at(i)->bracValues.at(num_bracs);
						num_bracs++;
						performOperation(&num, currNum);
						operatorEnum = operation(currChar);
					}
					else 
					{
						currNum = atof(terms.at(i)->strTerm().substr(start, j - start).c_str());
						performOperation(&num, currNum);
						operatorEnum = operation(currChar);

					}
				}
				start = j + 1;
			}

			else if (j == terms.at(i)->strTerm().length()-1)
			{
					if (terms.at(i)->strTerm().at(j) == '&')
					{
						double currNum = terms.at(i)->powValues.at(num_pows);
						num_pows++;
						performOperation(&num, currNum);
					}
					else if (terms.at(i)->strTerm().at(j) == '$')
					{
						double currNum = terms.at(i)->bracValues.at(num_bracs);
						num_bracs++;
						performOperation(&num, currNum);
					}
					else 
					{
						double currNum = atof(terms.at(i)->strTerm().substr(start, j - start+1).c_str());
						performOperation(&num, currNum);
					}
			}
		}
		currTerm->setNumericValue(num);
	}

	for (unsigned int i = 0; i < terms.size(); i++) //adds up the terms and deletes the array
	{
		val += terms.at(i)->numericValue();
		delete terms.at(i);
	}

	return(val);
}
