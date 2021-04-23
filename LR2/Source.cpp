#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <vector>
using namespace std;



int main() {

    vector<pair<int, double>> f, phi, g, psi;
    bool f_f = false, f_phi = false, f_g = false, f_psi = false;

    string line1;
    string line2;
    string line;
   
    ifstream in("C:\\Users\\kobze\\source\\repos\\LR2_EMMM\\Variant_9.txt");

    if (in.is_open())
    {
        while (getline(in, line))
        {
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == ' ') {
                    line1 = line2;
                    line2 = " ";
                }
                else {
                    line2 += line[i];
                }
            }

            if (line == "   x      f(x)") {
                f_f = true;
                f_phi = false;
                f_g = false;
                f_psi = false;
            }
            else if(f_f && line != " ") {
                f.push_back(make_pair(atoi(line1.c_str()), atof(line2.c_str())));
            }
            if (line == "   x      g(x)") {
                f_f = false;
                f_phi = false;
                f_g = true;
                f_psi = false;
            }
            else if (f_g && line != " ") {
                g.push_back(make_pair(atoi(line1.c_str()), atof(line2.c_str())));
            }
            if (line == "   x    phi(x)") {
                f_f = false;
                f_phi = true;
                f_g = false;
                f_psi = false;
            }
            else if (f_phi && line != " ") {
                phi.push_back(make_pair(atoi(line1.c_str()), atof(line2.c_str())));
            }
            if (line == "   x    psi(x)") {
                f_f = false;
                f_phi = false;
                f_g = false;
                f_psi = true;
            }
            else if (f_psi && line != " ") {
                psi.push_back(make_pair(atoi(line1.c_str()), atof(line2.c_str())));
            }
            line1 = " ";
            line2 = " ";
        }
    }
    for (int i = 0; i < psi.size(); ++i) {
        cout << psi[i].first << " " << psi[i].second << endl;
    }
}
