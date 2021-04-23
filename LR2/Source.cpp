#include <iostream>
#include <fstream>
#include <cstdlib>
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

    //setlocale(LC_ALL, "ru");

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
        left[i] = search(right[i - 1], psi);
        right[i] = search(right[i - 1], phi);
    }

    /*for (int i = 0; i < f.size(); ++i) {
        int k = f[i].second + search_(k1 - f[i].first, g);
        if (k > P_n[3].second) {
            P_n[3].second = k;
            P_n[3].first = f[i].first;
        }
    }*/

    FILE* file;
    fopen_s(&file, "inverse.txt", "w");
    fprintf_s(file, "Таблицы обратного планирования\n\n");

    fprintf_s(file, "%4s | %4s | %5s \n", "k4", "x4", "P4");

    /*vector<pair<int, double>> P4(right[3] - left[3] + 1), P3(right[2] - left[2] + 1), P2(right[1] - left[1] + 1), P1(right[0] - left[0] + 1);

    for (int i = left[n - 1]; i <= right[n - 1]; ++i) {
        for (int j = 0; f[j].first <= i; j++) {
            P4[j].second = f[j].second + search_(i - f[j].first, g);
            if (P4[j].second > P_n[3].second) {
                P_n[3].second = P4[j].second;
                P_n[3].first = f[j].first;
                P4[j].first = f[j].first;
            }
        }
        fprintf_s(file, "%4i | %4i | %5.3f\n", i, P_n[3].first, P_n[3].second);
    }

    fprintf_s(file, "\n\n");

    
    fprintf_s(file, "%4s | %4s | %5s \n", "k3", "x3", "P3");
    for (int j = left[2]; j <= right[2]; ++j) {
        for (int k = 0; f[k].first <= j; k++) {
            P3[k].second = f[k].second + search_(j - f[k].first, g) + search_((search_(f[k].first, phi) + search_(j - f[k].first, psi)), P4);
            if (P3[k].second > P_n[2].second) {
                P_n[2].second = P3[k].second;
                P_n[2].first = f[k].first;
                P3[k].first = f[k].first;
            }
        }

        fprintf_s(file, "%4i | %4i | %5.3f \n", j, P_n[2].first, P_n[2].second);
    }

    fprintf_s(file, "\n\n");



    fprintf_s(file, "%4s | %4s | %5s \n", "k2", "x2", "P2");
    for (int j = left[1]; j <= right[1]; ++j) {
        for (int k = 0; f[k].first <= j; k++) {
            P2[k].second = f[k].second + search_(j - f[k].first, g) + search_((search_(f[k].first, phi) + search_(j - f[k].first, psi)), P3);
            if (P2[k].second > P_n[1].second) {
                P_n[1].second = P2[k].second;
                P_n[1].first = f[k].first;
                P2[k].first = f[k].first;
            }
        }

        fprintf_s(file, "%4i | %4i | %5.3f \n", j, P_n[1].first, P_n[1].second);
    }

    fprintf_s(file, "\n\n");



    fprintf_s(file, "%4s | %4s | %5s \n", "k1", "x1", "P1");
    for (int k = 0; f[k].first <= right[0]; k++) {
        P1[k].second = f[k].second + search_(right[0] - f[k].first, g) + search_((search_(f[k].first, phi) + search_(right[0] - f[k].first, psi)), P2);
        if (P1[k].second > P_n[0].second) {
            P_n[0].second = P1[k].second;
            P_n[0].first = f[k].first;
            P1[k].first = f[k].first;
        }
    }

    fprintf_s(file, "%4i | %4i | %5.3f \n", right[0], P_n[1].first, P_n[1].second);
    

    fprintf_s(file, "\n\n");*/

    vector<vector<pair<int, double>>> P(n, vector<pair<int, double>>(f.size()));

    for (int i = left[n-1]; i <= right[n-1]; ++i) {
        for (int j = 0; f[j].first <= i; j++) {
            P[n-1][j].second = f[j].second + search_(i - f[j].first, g);
            if (P[n - 1][j].second > P_n[3].second) {
                P_n[3].second = P[n - 1][j].second;
                P_n[3].first = f[j].first;
                P[n - 1][j].first = f[j].first;
            }
        }
        fprintf_s(file, "%4i | %4i | %5.3f\n", i, P_n[3].first, P_n[3].second);
    }

    fprintf_s(file, "\n\n");

    P_n[2].second = 0;
    P_n[1].second = 0;
    P_n[0].second = 0;

    for (int i = 0; i < P[n-1].size(); i++) {
        cout << P[n - 1][i].first << " " << P[n - 1][i].second << endl;
    }

    /*for (int i = n-2; i >= 1; i--) {

        fprintf_s(file, "%4s | %4s | %5s \n", "k", "x", "P");
        for (int j = left[i]; j <= right[i]; ++j) {
            for (int k = 0; f[k].first <= j; k++) {
                P[i][k].second = f[k].second + search_(j - f[k].first, g) + search_(phi[k].first + search_(j - f[k].first, psi), P[i+1]);
                if (P[i][k].second > P_n[i].second) {
                    P_n[i].second = P[i][k].second;
                    P_n[i].first = f[k].first;
                    P[i][k].first = f[k].first;
                }
            }

            fprintf_s(file, "%4i | %4i | %5.3f \n", j, P_n[i].first, P_n[i].second);
        }

        fprintf_s(file, "\n\n");
    }*/
}
