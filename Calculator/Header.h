#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum eOperator
{
	eDivide,
	eMultiply,
	eSubtract,
	eAdd,
	ePower,
	eOpenBrack,
	eCloseBrack,
	eNoOperation
};

eOperator operatorEnum;


double value(string str);
void performOperation(double * prevNum, double currNum);
inline eOperator operation(char op);

#endif