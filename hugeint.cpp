#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::ios;

const unsigned int numTestCases = 22;
const unsigned int arraySize = 200;

// HugeInteger class definition
class HugeInteger
{
public:
	// enable user to input a positive huge integer
	void input(istream &inFile);

	// output the specified huge integer
	void output(ostream &outFile);

	// return true if and only if all digits are zero
	bool isZero();

	// return true if and only if current object == hugeInt2
	bool equal(HugeInteger hugeInt2);

	// return true if and only if current object < hugeInt2
	bool less(HugeInteger hugeInt2);

	// sum = current object + adder
	void addition(HugeInteger adder, HugeInteger &sum);

	// difference = current object - subtrahend
	// provided that the minuend is greater than or equal to the subtrahend
	void subtraction(HugeInteger subtrahend, HugeInteger &difference);

	// product = current object * multiplier
	void multiplication(HugeInteger multiplier, HugeInteger &product);

	// quotient = current object / divisor; remainder = current object % divisor
	// provided that the divisor is not equal to 0
	void division(HugeInteger divisor, HugeInteger &quotient, HugeInteger &remainder);

	// current object /= 10
	void divideByTen();

	unsigned int size = 1;        // the number of digits of the integer; it can never be zero
	int elems[arraySize] = {};  // used to store a nonnegative integer, one digit per element
}; // end class HugeInteger


   // enable user to input a positive huge integer
void HugeInteger::input(istream &inFile)
{
	char numericString[arraySize];

	inFile >> numericString;

	size = strlen(numericString);
	for (unsigned int i = 0; i < size; i++)
		elems[size - i - 1] = numericString[i] - '0';
} // end function input

  // output the specified huge integer
void HugeInteger::output(ostream &outFile)
{
	if (isZero())
		outFile << 0;
	else
		for (int i = size - 1; i >= 0; i--)
			if (elems[i] < 10)
				outFile << elems[i];
	outFile << endl;
} // end function output

  // test if a HugeInteger is zero
bool HugeInteger::isZero()
{
	for (unsigned int i = 0; i < size; i++)
		if (elems[i] != 0)
			return false;
	return true;
} // end function isZero

  // test if two HugeIntegers are equal
bool HugeInteger::equal(HugeInteger hugeInt2)
{
	if (size == hugeInt2.size) {
		for (int i = size - 1; i >= 0; i--) {
			if (elems[i] != hugeInt2.elems[i])
				return false;
			else
				return true;
		}
	}
	else
		return false;
} // end function equal

  // test if one HugeInteger is less than another
bool HugeInteger::less(HugeInteger hugeInt2)
{
	if (size < hugeInt2.size)
		return true;
	else if (size == hugeInt2.size) {
		for (int i = size - 1; i >= 0; i--) {
			if (elems[i] < hugeInt2.elems[i])
				return true;
			if (elems[i] > hugeInt2.elems[i])
				return false;
		}
		return false;//h1=h2
	}
	else
		return false;

} // end function less

  // sum = current object + adder
void HugeInteger::addition(HugeInteger adder, HugeInteger &sum)
{
	sum.size = (size >= adder.size) ? size + 1 : adder.size + 1;

	for (unsigned int i = 0; i < size; i++)
		sum.elems[i] = elems[i];

	for (unsigned int i = size; i < sum.size; i++)
		sum.elems[i] = 0;

	for (unsigned int i = 0; i < adder.size; i++)
		sum.elems[i] += adder.elems[i];

	for (unsigned int i = 0; i < sum.size - 1; i++)
		if (sum.elems[i] > 9) // determine whether to carry a 1
		{
			sum.elems[i] -= 10; // reduce to 0-9
			sum.elems[i + 1]++;
		}

	if (sum.elems[sum.size - 1] == 0)
		sum.size--;
} // end function addition

  // difference = current object - subtrahend
  // provided that the minuend is greater than or equal to the subtrahend
void HugeInteger::subtraction(HugeInteger subtrahend, HugeInteger &difference)
{
	difference.size = size;
	//先將差歸0
	for (unsigned int i = 0; i < size; i++) {
		difference.elems[i] = 0;
	}
	//減法
	for (int i = 0; i < size; i++) {
		if (i < subtrahend.size)
			difference.elems[i] = elems[i] - subtrahend.elems[i];
		else
			difference.elems[i] = elems[i];
	}

	//進位
	for (int i = 0; i < size; i++) {
		if (difference.elems[i] < 0) {
			difference.elems[i] += 10;
			difference.elems[i + 1]--;
		}
	}

	//削0
	for (int i = size - 1; i >= 0; i--) {
		if (difference.elems[i] != 0)
			break;
		else
			difference.size--;
	}
} // end function subtraction

  // product = current object * multiplier
void HugeInteger::multiplication(HugeInteger multiplier, HugeInteger &product)
{
	product.size = size +  multiplier.size;

	for (int i = product.size; i >= 0; i--)//here
		product.elems[i] = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < multiplier.size; j++) {
			product.elems[i + j] += elems[i] * multiplier.elems[j];
		}
	}
	for (unsigned int i = 0; i < product.size; i++) {
		if (product.elems[i] >= 10) {
			product.elems[i + 1] += product.elems[i] / 10;
			product.elems[i] = product.elems[i] % 10;
		}
	}

	for (int i = product.size - 1; i >= 0; i--) {
		if (product.elems[i] > 0)
			break;
		else
			product.size--;
	}

} // end function multiplication

  // quotient = current object / divisor; remainder = current object % divisor
  // provided that the divisor is not equal to 0
void HugeInteger::division(HugeInteger divisor, HugeInteger &quotient, HugeInteger &remainder)
{
	if (isZero()) {
		quotient.size = 1;
		quotient.elems[0] = 0;
		remainder.size = 1;
		remainder.elems[0] = 0;
		return;
	}
	remainder.size = size;
	for (unsigned int i = 0; i < size; i++) {
		remainder.elems[i] = elems[i];
	}
	if (less(divisor)) {
		quotient.size = 1;
		quotient.elems[0] = 0;
	}
	else
	{
		int n = size - divisor.size;
		HugeInteger buffer;
		buffer.size = size;
		//buffer 歸0
		for (unsigned int i = 0; i < size; i++)
			buffer.elems[i] = 0;
		//把除數放到buffer 跟他對齊
		for (unsigned int i = 0; i < divisor.size; i++)
			buffer.elems[i + n] = divisor.elems[i];
		quotient.size = size - divisor.size;
		if (less(buffer))
			buffer.divideByTen();
		else
			quotient.size++;

		for (unsigned int i = 0; i < quotient.size; i++)
			quotient.elems[i] = 0;
		for (unsigned int k = quotient.size - 1; k >= 0; k--) {
			while (!remainder.less(buffer))
			{
				HugeInteger h;
				remainder.subtraction(buffer, h);
				remainder.size = h.size;
				for (unsigned int i = 0; i < h.size; i++)
					remainder.elems[i] = h.elems[i];
				quotient.elems[k]++;
				if (remainder.isZero())
					return;
			}
			buffer.divideByTen();
		}
	}
} // end function division

  // current object /= 10
void HugeInteger::divideByTen()
{
	if (size == 1)
		elems[0] = 0;
	else
	{
		for (unsigned int i = 1; i < size; i++)
			elems[i - 1] = elems[i];
		elems[size - 1] = 0;
		size--;
	}
} // end function divideByTen


void perform(ostream &outFile, HugeInteger hugeInt1, HugeInteger hugeInt2,
	HugeInteger hugeInt3, HugeInteger hugeInt4);

int main()
{
	system("mode con cols=122");

	ifstream inFile("Test cases.txt", ios::in);

	// exit program if ifstream could not open file
	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	ofstream outFile("Result.txt", ios::out);

	// exit program if ofstream could not open file
	if (!outFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	for (int i = 0; i < numTestCases; i++)
	{
		HugeInteger hugeInt1;
		HugeInteger hugeInt2;
		HugeInteger hugeInt3;
		HugeInteger hugeInt4;

		hugeInt1.input(inFile);
		hugeInt2.input(inFile);
		perform(cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4);
		perform(outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4);
	}

	inFile.close();
	outFile.close();

	system("pause");
}

void perform(ostream &outFile, HugeInteger hugeInt1, HugeInteger hugeInt2,
	HugeInteger hugeInt3, HugeInteger hugeInt4)
{
	hugeInt1.output(outFile);
	hugeInt2.output(outFile);

	hugeInt1.addition(hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 + hugeInt2
	hugeInt3.output(outFile);

	if (hugeInt1.less(hugeInt2))
	{
		outFile << '-';
		hugeInt2.subtraction(hugeInt1, hugeInt3); // hugeInt3 = hugeInt2 - hugeInt1
		hugeInt3.output(outFile);
	}
	else
	{
		hugeInt1.subtraction(hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 - hugeInt2
		hugeInt3.output(outFile);
	}

	hugeInt1.multiplication(hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 * hugeInt2
	hugeInt3.output(outFile);

	if (hugeInt2.isZero())
	{
		outFile << "DivideByZero!\n";
		outFile << "DivideByZero!\n";
	}
	else
	{
		// hugeInt3 = hugeInt1 / hugeInt2; // hugeInt4 = hugeInt1 % hugeInt2
		hugeInt1.division(hugeInt2, hugeInt3, hugeInt4);
		hugeInt3.output(outFile);
		hugeInt4.output(outFile);
	}

	outFile << endl;
}
