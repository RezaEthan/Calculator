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

inline void performOperation(double * prevNum, double currNum)
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
	unsigned int inBrac = 0;
	for (unsigned int i = 0; i < str.length(); i++) //sorts the string into terms, turning each into a termClass and putting them in a vector
	{
		switch (str[i])
		{
		case '-':
			if ((i != 0 && ((str[i-1] > 47 && str[i-1] < 58) || str[i-1] == ')')) && inBrac <= 0) 
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
				if (inBrac <= 0)
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
			inBrac++;
			term += '(';
			break;
		case ')':
			inBrac--;
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
		if (currentIndexString.find('(') != string::npos) //if brackets exist in terms
		{
			int firstBrac = currentIndexString.find_first_of('(',0);
			int bracs_within_curr_brac = 0; //finds the number of brackets within the current bracket to know how many closed brackets to pass
			for (unsigned int index = firstBrac + 1; index < currentIndexString.length() - 1; index++)
			{
				if (currentIndexString[index] == '(')
					bracs_within_curr_brac++;
				else if (currentIndexString[index] == ')' && bracs_within_curr_brac <= 0)
					break;

			}
			int secondBrac = currentIndexString.find_first_of(')',firstBrac);
			while (bracs_within_curr_brac-- > 0 && secondBrac != -1)
				secondBrac = currentIndexString.find_first_of(')', secondBrac+1);
			do
			{
				string replacer = "";
				terms.at(i)->bracValues.push_back(value(currentIndexString.substr(firstBrac+1,secondBrac-firstBrac-1))); 
				if (firstBrac != 0 && ((currentIndexString[firstBrac-1] > 48 && currentIndexString[firstBrac-1] < 58) || currentIndexString[firstBrac-1] == '$' || currentIndexString[firstBrac-1] == '&'))
					replacer += '*';
				replacer += '$';
				if (secondBrac != currentIndexString.length()-1 && ((currentIndexString[secondBrac+1] > 48 && currentIndexString[secondBrac+1] < 58) || currentIndexString[secondBrac+1] == '$' || currentIndexString[secondBrac+1] == '&'))
					replacer += '*';
				currentIndexString.replace(firstBrac,secondBrac-firstBrac+1,replacer);
				terms.at(i)->setStrTerm(currentIndexString);
				firstBrac = currentIndexString.find_first_of('(',firstBrac+1);
				for (unsigned int index = firstBrac + 1; index < currentIndexString.length() - 1; index++)
				{
					if (currentIndexString[index] == '(')
						bracs_within_curr_brac++;
					else if (currentIndexString[index] == ')' && bracs_within_curr_brac <= 0)
						break;
				}
				secondBrac = currentIndexString.find_first_of(')',firstBrac);
				while (bracs_within_curr_brac-- > 0 && secondBrac != -1)
					secondBrac = currentIndexString.find_first_of(')', secondBrac+1);
			}while (firstBrac != string::npos);
		}
	}
	for (unsigned int i = 0; i < terms.size(); i++) //same as above but for powers, and replaces with &
	{
		string currentIndexString = terms.at(i)->strTerm();
		if (currentIndexString.find('^') != string::npos)
		{
			int posOfPow = currentIndexString.length() - 1;
			int prevPower = 0;
			int currBracIndex = 0;
			int currPowIndex = 0;
			do
			{
				char operators[] = { '/', '*', '-', '+', '^', '(', ')' };
				posOfPow = currentIndexString.find_last_of('^',posOfPow);
				int prevOperator = currentIndexString.find_last_of(operators,posOfPow - 1);
				if (prevOperator == string::npos || prevOperator > posOfPow)
				{
					prevOperator = -1;
				}
				int nextOperator = currentIndexString.find_first_of(operators,posOfPow+1);
				if (nextOperator == string::npos)
				{
					nextOperator = currentIndexString.length();
				}
				double base = 0;

				switch(currentIndexString[posOfPow-1])
				{
				case '$':
					base = terms.at(i)->bracValues.at(currBracIndex);
					currBracIndex++;
					break;
				default:
					base = atof(currentIndexString.substr(prevOperator+1,posOfPow-prevOperator).c_str());
					break;
				}

				double expo = 0;
				switch(currentIndexString[posOfPow+1])
				{
				case '$':
					expo = terms.at(i)->bracValues.at(currBracIndex);
					currBracIndex++;
					break;
				case '&':
					expo = terms.at(i)->powValues.at(currPowIndex);
					terms.at(i)->powValues.erase(terms.at(i)->powValues.begin() + currPowIndex);
					break;
				default:
					expo = atof(currentIndexString.substr(posOfPow + 1, nextOperator-posOfPow).c_str());
					break;
				}
				double power = pow(base,expo);
				currentIndexString.replace(prevOperator+1,nextOperator - (prevOperator + 1),"&");
				terms.at(i)->setStrTerm(currentIndexString);
				terms.at(i)->powValues.push_back(power);
				posOfPow = currentIndexString.find_last_of('^',posOfPow);
				prevPower = currentIndexString.find_first_of('&',prevPower + 1);

			} while(posOfPow != string::npos);
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
