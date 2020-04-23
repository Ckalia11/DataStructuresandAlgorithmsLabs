#include <iostream>
#include <iomanip>

using namespace std;

class Polynomial {
private:
	vector<int> data;
public:
	friend class PolynomialTest;
	Polynomial(int A[], int size);
	Polynomial();
	Polynomial(string filename);
	bool operator==(const Polynomial& target);
	void print();
	Polynomial operator+(const Polynomial& target);
	Polynomial operator-(const Polynomial& target);
	Polynomial operator*(const Polynomial& target);
	Polynomial derivative();
	~Polynomial();

};




