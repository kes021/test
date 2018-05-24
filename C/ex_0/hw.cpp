#include <iostream>
// we need the following include for setw() in some c++ implementations
#include <iomanip>
using namespace std;

int main() {
	// set up cout to right-align
	cout <<  setiosflags(ios::left);
	// the first for loop will handle the rows
	for (int i = 0; i < 6; i++) {
		// the second for loop will handle the columns
		for (int j = 0;  j < 4 ; j++)
			// setw(int) sets the column width
			cout << "Hello World!";
		// this  next line is a part of the first for loop
		// and causes the new line
		cout << endl;
	}
	return 0;
}

