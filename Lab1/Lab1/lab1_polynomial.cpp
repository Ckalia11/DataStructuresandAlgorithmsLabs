// lab1_polynomial.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <algorithm>
#include<time.h>
#include <cstdlib> 
#include <fstream>
#include <string>
#include "lab1_polynomial.hpp"

using namespace std;

	Polynomial::Polynomial(int A[], int size) {
		data.resize(0);
		for (int i = 0; i < size; i++) {
			data.push_back(A[i]);
		}
		
	}

	Polynomial::Polynomial() {
		int random = rand() % 1001;
		int max = 1000;
		int min =  0 - 1000;
		for (int i = 0; i < random + 1; i++) {
			int coefficient = rand() % (max - min + 1) + min;
			data.push_back(coefficient);
		}
	}

	Polynomial::Polynomial(string filename) {

		ifstream in(filename);
		
		if (in) {

			string line;
			getline(in, line);
			while (getline(in, line)) {
				if (line == "") {
					data.push_back(0);
				}
				else {
					data.push_back(stoi(line));
				}
			}

		}
	}

	bool Polynomial::operator==(const Polynomial& target) {
		if (this->data.size() != target.data.size()) {
			return false;
		}
		for (int i = 0; i < target.data.size(); i++) {
			if (target.data[i] != this->data[i]) {
				return false;
			}
		}
		return true;
	}

	void Polynomial::print() {
		string poly = "";
		int i = data.size() - 1;
		if (data.size() == 1 && data[i] == 0) {
		}
		else {
			//pop values off vector if they equal zero
				while (data[i] == 0) {
					data.pop_back();
					i--;
				}
			string str = to_string(data[i]) + "x^" + to_string(i);
			poly.append(str);
			if (data.size() > 2) {
				for (int i = data.size() - 2; i >= 0; i--) {
					int coefficient = data[i];
					if (coefficient != 0) {
						poly.append(" + ");
						str = to_string(coefficient) + "x^" + to_string(i);
						poly.append(str);
					}
				}
			}
		}
		cout << poly << endl;
	}

	Polynomial Polynomial::operator+(const Polynomial& target) // performs *this + target
	{
		Polynomial addition;
		addition.data.resize(0);

		int min_size = target.data.size();

		//if size of both vectors are the same

		if (target.data.size() == this->data.size()) {
			for (int i = 0; i < min_size; i++) {
				int insert = target.data[i] + this->data[i];
				addition.data.push_back(insert);
			}
		}
		else {
			if (target.data.size() < this->data.size()) {
					
				for (unsigned int i = 0; i < target.data.size(); i++) {
					int insert = target.data[i] + this->data[i];
					addition.data.push_back(insert);
				}
				for (unsigned int i = target.data.size(); i < this->data.size(); i++) {
					addition.data.push_back(this->data[i]);
				}
	
			}

			else {

				for (unsigned int i = 0; i < this->data.size(); i++) {
					int insert = target.data[i] + this->data[i];
					addition.data.push_back(insert);
				}
				for (unsigned int i = this->data.size(); i < target.data.size(); i++) {
					addition.data.push_back(target.data[i]);
				}
			}

		}
		return addition;

	}
			//this - target
	Polynomial Polynomial::operator-(const Polynomial& target) {

		Polynomial subtraction;
		subtraction.data.resize(0);
				
		int min_size = target.data.size();

		if (target.data.size() == this->data.size()) {
			for (int i = 0; i < min_size; i++) {
				int insert = this->data[i] - target.data[i];
				subtraction.data.push_back(insert);
			}
		}
		else {
			if (target.data.size() < this->data.size()) {

				for (unsigned int i = 0; i < target.data.size(); i++) {
					int insert = this->data[i] - target.data[i];
					subtraction.data.push_back(insert);
				}
				for (unsigned int i = target.data.size(); i < this->data.size(); i++) {
					subtraction.data.push_back(this->data[i]);
				}

			}

			else {

				for (unsigned int i = 0; i < this->data.size(); i++) {
					int insert = this->data[i] - target.data[i];
					subtraction.data.push_back(insert);
				}
				for (unsigned int i = this->data.size(); i < target.data.size(); i++) {
					subtraction.data.push_back( 0 - target.data[i]);
				}
			}

		}

		return subtraction;
}

	Polynomial Polynomial::operator*(const Polynomial& target) // performs *this * target
	{
		Polynomial multiplication;
		int a = this->data.size();
		int b = target.data.size();
		multiplication.data.resize( a + b - 1);

		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < b; j++)
				multiplication.data[i + j] += this->data[i] * target.data[j];
		}

		return multiplication;
	}

	Polynomial Polynomial::derivative() {

		Polynomial derive;
		derive.data.resize(0);

		if (this->data.size() == 1) {

			derive.data.push_back(0);
		}

		else {

			for (unsigned int i = 1; i < this->data.size(); i++) {
				int insert = this->data[i] * i;
				derive.data.push_back(insert);
			}

		}
		
		return derive;
	}
		//empty since no dynamic memory allocation
	 Polynomial::~Polynomial() {
	}

	 class PolynomialTest {
	 public:

		 bool test_constructors1() {
			 int A[] = { 7, 5, 3, 10, 12, 6, 15 };
			 int length = size(A);
			 Polynomial test(A, length);
			 test.print();
			 return true;
		 }

		 bool test_constructors2() {
			 for (int i = 0; i < 50; i++) {
				 Polynomial a;
				 Polynomial b;
				 if (a == b) {
					 cout << "Matching two polynomials instances ERROR";
					 return false;
				 }
			 }
			 return true;
		 }

		 bool test_constructors3() {
			 //test case 1 
			 Polynomial a("file.txt");
			 a.print();
			 //test case 2 - file has an empty line that should be stored as 0
			 Polynomial b("missingline.txt");
			 b.print();
			 return true;
		 }

		 bool test_equal_operator() {
			 //test case 1 - same coefficients
			 int A[] = { 7, 5, 3, 10, 12, 6, 15 };
			 int length = size(A);
			 Polynomial test(A, length);
			 int B[] = { 7, 5, 3, 10, 12, 6, 15 };
			 int length2 = size(B);
			 Polynomial test2(B, length);
			 if (test == test2) {
			 }
			 else {
				 return false;
			 }
			 //test case 2 - different size and coefficients
			 int C[] = { 10, 4, 5, 2, 7, 1 };
			 int length3 = size(C);
			 Polynomial test3(C, length3);
			 Polynomial test4("file.txt");
			 if (test3 == test4) {
				 return false;
			 }
			 //test case 3 & 4 (zero polynomial)
			 int D[] = { 0 };
			 int length4 = 1;
			 Polynomial test5(D, length4);
			 int E[] = { 0 };
			 int length5 = 1;
			 Polynomial test6(E, length5);
			 if (test5 == test4) {
				 return false;
			 }
			 if (test5 == test6) {
				 return true;
			 }
			 return false;
		 }

		 bool test_print() {
			 cout << "print() was used more than 3 times in other tests" << endl;
			 int A[] = { 6, 5, 3, 10, 9, 6, 9 };
			 int length = size(A);
			 Polynomial test1(A, length);
			 //test when coefficient(s) is zero
			 test1.print();
			 int B[] = { 0, 5, 3, 10, 0, 6, 0 };
			 int length2 = size(B);
			 Polynomial test2(B, length2);
			 test2.print();
			 int C[] = { 0,0,4,6,7 };
			 int length3 = size(C);
			 Polynomial test3(C, length3);
			 test3.print();
			 int D[] = { 7,0,0,0,0 };
			 int length4 = size(D);
			 Polynomial test4(D, length4);
			 test4.print();
			 return true;
			 
		 }

		 bool test_plus_operator() {
			 //test case 1 - same length
			 int A[] = { 7, 5, 3, 10, 12, 6, 15 };
			 int length = size(A);
			 Polynomial test(A, length);
			 test.print();
			 int B[] = { 13, 15, 17, 10, 8, 14, 5 };
			 int length2 = size(B);
			 Polynomial test2(B, length2);
			 test2.print();
			 (test + test2).print();
			 //test case 2 - different length
			 int C[] = { 7, 5, 3, 10, 12, 6, 15 };
			 int length3 = size(C);
			 Polynomial test3(C, length3);
			 test3.print();
			 Polynomial test4("file.txt");
			 test4.print();
			 (test3 + test4).print();
			 //test case 3 - zero polynomial
			 int D[] = { 0 };
			 int size4 = 1;
			 Polynomial test5(D, size4);
			 test5.print();
			 (test3 + test5).print();
			 return true;
		 }

		 bool test_minus_operator() {
			 //test case 1 - same length
			 int A[] = { 7, 5, 3, 10, 12, 6, 15 };
			 int length = size(A);
			 Polynomial test(A, length);
			 test.print();
			 int B[] = { 6, 4, 2, 9, 11, 5, 14 };
			 int length2 = size(B);
			 Polynomial test2(B, length2);
			 test2.print();
			 (test - test2).print();
			 //test case 2 - this->data.size() < target.data.size()
			 int C[] = { 7, 5, 3, 10, 12 };
			 int length3 = size(C);
			 Polynomial test3(C, length3);
			 test3.print();
			 Polynomial test4("file.txt");
			 test4.print();
			 (test3 - test4).print();
			 //test case 3 - target.data.size() < this->data.size()
			 (test4 - test3).print();
			 // test case 4 - zero polynomial
			 int D[] = { 0 };
			 int length4 = 1;
			 Polynomial test5(D, length4);
			 test5.print();
			 (test3 - test5).print();
			 (test5 - test3).print();
			 return true;
		 }

		 bool test_multiplication_operator() {
			 //test case 1
			 int A[] = { 7, 5, 3, 6, 9, 10 };
			 int length = size(A);
			 Polynomial test(A, length);
			 test.print();
			 int B[] = { 2, 3, 4, 5 };
			 int length2 = size(B);
			 Polynomial test2(B, length2);
			 test2.print();
			 (test * test2).print();
			 //test case 2
			 int C[] = { 7, 5, 3 };
			 int length3 = size(C);
			 Polynomial test3(C, length3);
			 test3.print();
			 Polynomial test4("file.txt");
			 test4.print();
			 (test3 * test4).print();
			 //test case 3
			 int D[] = { 0 };
			 int length4 = 1;
			 Polynomial test5(D, length4);
			 test5.print();
			 (test3 * test5).print();
			 return true;
		 }

		 bool test_derrivative() {
			 //test case 1
			 int A[] = { 7, 5, 3, 10, 12, 6, 15 };
			 int length = size(A);
			 Polynomial test(A, length);
			 test.print();
			 (test.derivative()).print();
			 //test case 2
			 int B[] = { 6, 3, 6, 2, 13 };
			 int length2 = size(B);
			 Polynomial test2(B, length2);
			 test2.print();
			 (test2.derivative()).print();
			 //test case 3 - zero polynomial, both print outputs should be nothing
			 int C[] = { 0 };
			 int length3 = 1;
			 Polynomial test3(C, length3);
			 test3.print();
			 (test3.derivative()).print();
			 return true;
		 }

		 void run() {
			 if (test_constructors1()) {
				 cout << "Test Constructors1 Passed\n" << endl;
			 }
			 else {
				 cout << "Test Constructors1 Failed\n" << endl;
			 }
			 if (test_constructors2()) {
				 cout << "Test Constructors2 Passed\n" << endl;
			 }
			 else {
				 cout << "Test Constructors2 Failed\n" << endl;
			 }
			 if (test_constructors3()) {
				 cout << "Test Constructors3 Passed\n" << endl;
			 }
			 else {
				 cout << "Test Constructors3 Failed\n" << endl;
			 }
			 if (test_equal_operator()) {
				 cout << "Test Equal Operator Passed\n" << endl;
			 }
			 else {
				 cout << "Test Equal Operator Failed\n" << endl;
			 }
			 if (test_print()) {
				 cout << "Test Print Passed\n" << endl;
			 }
			 else {
				 cout << "Test Print Failed\n" << endl;
			 }
			 if (test_plus_operator()) {
				 cout << "Test Plus Operator Passed\n" << endl;
			 }
			 else {
				 cout << "Test Plus Operator Failed\n" << endl;
			 }
			 if (test_minus_operator()) {
				 cout << "Test Minus Operator Passed\n" << endl;
			 }
			 else {
				 cout << "Test Minus Operator Failed\n" << endl;
			 }
			 if (test_multiplication_operator()) {
				 cout << "Test Multiplication Operator Passed\n" << endl;
			 }
			 else {
				 cout << "Test MultiplicationOperator Failed\n" << endl;
			 }
			 if (test_derrivative()) {
				 cout << "Test Derrivative Passed\n" << endl;
			 }
			 else {
				 cout << "Test Derrivative Failed\n" << endl;
			 }

		 }
	 };
	

int main() {
	srand(time(0));
	PolynomialTest mytest;
	mytest.run();
	return 0;
	
}

	



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file