#include <iostream>
#include <vector>
#include <fstream>

using namespace std;



int main() {
	
	ifstream file("C:\\Users\\Aria_nrod\\source\\repos\\LR2\\Debug\\Вариант 9.txt");
	if (file.is_open()) {
		for (file >> f; !file.eof(); f >> file) {
			cout << file << endl;
		}
	}

}
