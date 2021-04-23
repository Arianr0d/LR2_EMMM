#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int search(double x, vector<pair<int, double>> arr) {
    for (int i = 0; i < arr.size(); ++i) {
        if (x == arr[i].first) {
            return arr[i].second;
        }
        if (x < arr[i].first) {
            return (arr[i - 1].second * (arr[i].first - x) + arr[i].second * (x - arr[i - 1].first)) / (arr[i].first - arr[i - 1].first);
        }
    }

}

double search_(double x, vector<pair<int, double>> arr) {
    for (int i = 0; i < arr.size(); ++i) {
        if (x == arr[i].first) {
            return arr[i].second;
        }
        if (x < arr[i].first) {
            return (arr[i - 1].second * (arr[i].first - x) + arr[i].second * (x - arr[i - 1].first)) / (arr[i].first - arr[i - 1].first);
        }
    }

}

int main() {

    int n = 4, k1 = 1000;
    vector<pair<double, double>> P_n(n);
    P_n[3].second = 0;

    vector<pair<int, double>> f, phi, g, psi;
    bool f_f = false, f_phi = false, f_g = false, f_psi = false;

    vector<int> left(n), right(n);
    left[0] = 0;
    right[0] = k1;

    string line1;
    string line2;
    string line;
   
    ifstream in("C:\\Users\\kobze\\source\\repos\\LR2_EMMM\\Variant_9.txt");

    if (in.is_open())
    {
        while (!in.eof())
        {
            in >> line1;
            in >> line2;
            if (line1 == "x" && line2 == "f(x)") {
                f_f = true;
                f_phi = false;
                f_g = false;
                f_psi = false;
            }
            else if(f_f && line1 != " ") {
                f.push_back(make_pair(atoi(line1.c_str()), atof(line2.c_str())));
            }
            if (line1 == "x" && line2 == "g(x)") {
                f_f = false;
                f_phi = false;
                f_g = true;
                f_psi = false;
            }
            else if (f_g && line1 != " ") {
                g.push_back(make_pair(atoi(line1.c_str()), atof(line2.c_str())));
            }
            if (line1 == "x" && line2 == "phi(x)") {
                f_f = false;
                f_phi = true;
                f_g = false;
                f_psi = false;
            }
            else if (f_phi && line1 != " ") {
                phi.push_back(make_pair(atoi(line1.c_str()), atof(line2.c_str())));
            }
            if (line1 == "x" && line2 == "psi(x)") {
                f_f = false;
                f_phi = false;
                f_g = false;
                f_psi = true;
            }
            else if (f_psi && line1 != " ") {
                psi.push_back(make_pair(atoi(line1.c_str()), atof(line2.c_str())));
            }
            line1 = " ";
            line2 = " ";
        }
    }
    for (int i = 0; i < psi.size(); ++i) {
        cout << f[i].first << " " << f[i].second << endl;
    }

    for (int i = 1; i < n; ++i) {
        left[i] = search(right[i - 1], psi);
        right[i] = search(right[i - 1], phi);
    }

    for (int i = 0; i < f.size(); ++i) {
        int k = f[i].second + search_(k1 - f[i].first, g);
        if (k > P_n[3].second) {
            P_n[3].second = k;
            P_n[3].first = f[i].first;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = left[i]; i <= right[i]; ++j) {

        }
    }
}
