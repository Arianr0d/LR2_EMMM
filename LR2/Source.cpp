#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;



int main() {
    string line;

    ifstream in("C:\\Users\\kobze\\source\\repos\\LR2_EMMM\\Variant_9.txt");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            std::cout << line << std::endl;
        }
    }

}
