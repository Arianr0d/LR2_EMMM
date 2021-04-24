#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;


double search__(int x, vector<pair< int, pair<int, double> >> arr) {   // здесь ошибка out of range
    
    for (int i = 0; i < arr.size(); ++i) {
        if (x == arr[i].first) {
            return arr[i].second.second;
        }
        if (x < arr[i].first) {
            return (arr[i - 1].second.second * (arr[i].first - x) + arr[i].second.second * (x - arr[i - 1].first)) / (arr[i].first - arr[i - 1].first);
        }
    }
}

double search_(int x, vector<pair<int, double>> arr) {

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
    vector<pair<int, double>> P_n(n);
    P_n[3].second = 0;

    vector<pair<int, double>> f, phi, g, psi;
    bool f_f = false, f_phi = false, f_g = false, f_psi = false;

    vector<int> left(n), right(n);
    left[0] = 0;
    right[0] = k1;

    string line1;
    string line2;
    string line;
   
    ifstream in("C:\\Users\\Aria_nrod\\source\\repos\\LR2\\Debug\\Вариант 9.txt");

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

    for (int i = 1; i < n; ++i) {
        left[i] = floor(search_(right[i - 1], psi));
        right[i] = round(search_(right[i - 1], phi));
    }

    FILE* file;
    fopen_s(&file, "inverse.txt", "w");
    fprintf_s(file, "Таблицы обратного планирования\n\n");

    fprintf_s(file, "%4s | %4s | %5s \n", "k4", "x4", "P4");

    vector< vector< pair< int, pair<int, double> > > > P(n);
    vector<int> shape(n);
    for (int i = 0; i < n; i++) {
        P[i].assign(right[i] - left[i] + 1, make_pair(0, make_pair(0,0)));
        shape[i] = right[i] - left[i] + 1;
    }

    for (int i = left[n-1], i1 = 0; i <= right[n-1] && i1 < f.size(); ++i, i1++) {
        for (int j = 0; f[j].first <= i; j++) {
            P[n-1][i1].second.second = f[j].second + search_(i - f[j].first, g);
            if (P[n - 1][i1].second.second > P_n[3].second) {
                P_n[3].second = P[n - 1][i1].second.second;
                P_n[3].first = f[j].first;
            }
        }
        P[n - 1][i1].second.second = P_n[3].second;
        P[n - 1][i1].second.first = P_n[3].first;
        P[n - 1][i1].first = i;
        fprintf_s(file, "%4i | %4i | %5.3f\n", i, P_n[3].first, P_n[3].second);
    }

    fprintf_s(file, "\n\n");

    P_n[2].second = 0;
    P_n[1].second = 0;
    P_n[0].second = 0;

    /*for (int i = 0; i < P[n-1].size(); i++) {
        cout << i + left[n-1] << " " << P[n - 1][i].first << " " << P[n - 1][i].second << endl;
    }

    for (int i = 0; i < n; i++) {
        cout << left[i] << " " << right[i] << endl;
    }*/

    for (int i = n-2; i >= 1; i--) {

        fprintf_s(file, "%4s | %4s | %5s \n", "k", "x", "P");
        for (int j = left[i], j1 = 0; j <= right[i] && j1 < f.size(); ++j, j1++) {
            for (int k = 0; f[k].first <= j; k++) {
                P[i][j1].second.second = f[k].second + search_(j - f[k].first, g) + search__(round(phi[k].first + search_(j - f[k].first, psi)), P[i+1]);  // возможное место ошибки
                if (P[i][j1].second.second > P_n[i].second) {
                    P_n[i].second = P[i][j1].second.second;
                    P_n[i].first = f[k].first;
                }
            }

            fprintf_s(file, "%4i | %4i | %5.3f \n", j, P_n[i].first, P_n[i].second);
            P[i][j1].second.second = P_n[i].second;
            P[i][j1].second.first= P_n[i].first;
            P[i][j1].first= j;
        }

        fprintf_s(file, "\n\n");
    }

    /*double x = phi[0].first + search_(470 - f[0].first, psi);
    for (int i = 0; i < P[n-2].size(); ++i) {
        if (x == P[n-2].first) {
            return arr[i].second;
        }
        if (x < arr[i].first) {
            return (arr[i - 1].second * (arr[i].first - x) + arr[i].second * (x - arr[i - 1].first)) / (arr[i].first - arr[i - 1].first);
        }
    }*/
}
