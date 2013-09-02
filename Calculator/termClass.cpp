#include "termClass.h"

termClass::termClass(void)
{
}

void termClass::setStrTerm(std::string strTerm)
{
	_strTerm = strTerm;
}

std::string termClass::strTerm()
{
	return _strTerm;
}

void termClass::setNumericValue(double numericValue)
{
	_numericValue = numericValue;
}

double termClass::numericValue()
{
	return _numericValue;
}

termClass::~termClass(void)
{
}
