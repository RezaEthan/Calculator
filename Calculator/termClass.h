#pragma once
#include <string>
#include <vector>
using namespace std;
class termClass
{
private:
	double _numericValue;
	string _strTerm;
public:
	termClass(void);
	void setNumericValue (double numericValue);
	double numericValue ();
	void setStrTerm (string strTerm);
	string strTerm();

	vector <double> powValues;
	virtual ~termClass(void);
};

