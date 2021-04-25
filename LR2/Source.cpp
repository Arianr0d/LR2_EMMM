#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;


double search__(double x, vector<pair< int, pair<int, double> >> arr) {   // здесь ошибка out of range
    
    for (int i = 0; i < arr.size(); ++i) {
        if (x == arr[i].first) {
            return arr[i].second.second;
        }
        if (x < arr[i].first) {
            return (arr[i - 1].second.second * (arr[i].first - x) + arr[i].second.second * (x - arr[i - 1].first)) / (arr[i].first - arr[i - 1].first);
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
    vector<pair<int, double>> P_n(n);
    P_n[3].second = 0;

    vector<pair<int, double>> f, phi, g, psi;
    bool f_f = false, f_phi = false, f_g = false, f_psi = false;

    vector<int> left(n), right(n);
    left[0] = 1000;
    right[0] = k1;

    string line1;
    string line2;
    string line;
   
    //ifstream in("C:\\Users\\Aria_nrod\\source\\repos\\LR2\\Debug\\Вариант 9.txt");
    ifstream in("C:\\Users\\kobze\\source\\repos\\LR2_EMMM\\x64\\Debug\\Вариант 9.txt");

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
            else if(f_f && line1 != " " && line1 != "x") {
                f.push_back(make_pair(atoi(line1.c_str()), atof(line2.c_str())));
            }
            if (line1 == "x" && line2 == "g(x)" ) {
                f_f = false;
                f_phi = false;
                f_g = true;
                f_psi = false;
            }
            else if (f_g && line1 != " " && line1 != "x") {
                g.push_back(make_pair(atoi(line1.c_str()), atof(line2.c_str())));
            }
            if (line1 == "x" && line2 == "phi(x)") {
                f_f = false;
                f_phi = true;
                f_g = false;
                f_psi = false;
            }
            else if (f_phi && line1 != " " && line1 != "x") {
                phi.push_back(make_pair(atoi(line1.c_str()), atof(line2.c_str())));
            }
            if (line1 == "x" && line2 == "psi(x)") {
                f_f = false;
                f_phi = false;
                f_g = false;
                f_psi = true;
            }
            else if (f_psi && line1 != " " && line1 != "x") {
                psi.push_back(make_pair(atoi(line1.c_str()), atof(line2.c_str())));
            }
            line1 = " ";
            line2 = " ";
        }
    }

   /* for (int i = 1; i < n; ++i) {
        left[i] = floor(search_(right[i - 1], psi));
        right[i] = round(search_(right[i - 1], phi));
    }*/

    FILE* file, *file1;
    fopen_s(&file, "inverse.txt", "w");
    fprintf_s(file, "Таблицы обратного планирования\n\n");

    fprintf_s(file, "%4s | %4s | %5s \n", "k4", "x4", "P4");

    vector< vector< pair< int, pair<int, double> > > > P(n);
    vector<int> shape(n);
    for (int i = 0; i < n; i++) {
        P[i].assign(101, make_pair(0, make_pair(0,0)));
        //shape[i] = right[i] - left[i] + 1;
    }

    /*for (int i = left[n-1], i1 = 0; i <= right[n-1]; ++i, i1++) {
        if (i == 423) {
            cout << 1;
        }
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
    }*/

    for (int i = 0, i1 = 0; i <= 1000; i += 10, i1++) {
        for (int j = 0; j <= i; j+= 10) {
            P[n - 1][i1].second.second = search_(j, f) + search_(i - j, g);
            if (P[n - 1][i1].second.second > P_n[3].second) {
                P_n[3].second = P[n - 1][i1].second.second;
                P_n[3].first = j;
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

    /*for (int i = n-2; i >= 0; i--) {

        fprintf_s(file, "%4s | %4s | %5s \n", "k", "x", "P");
        for (int j = left[i], j1 = 0; j <= right[i]; ++j, j1++) {
            for (int k = 0; f[k].first < j; k++) {
                P[i][j1].second.second = f[k].second + search_(j - f[k].first, g) + search__(round(psi[k].first + search_(j - f[k].first, phi)), P[i+1]);  // возможное место ошибки
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
    }*/
    for (int k = n-2; k >= 0; --k) {
        for (int i = 0, i1 = 0; i <= 1000; i += 10, i1++) {
            for (int j = 0; j <= i; j += 10) {
                P[k][i1].second.second = search_(j, f) + search_(i - j, g) + search__(search_(j, phi) + search_(i - j, psi), P[k + 1]);
                if (P[k][i1].second.second > P_n[k].second) {
                    P_n[k].second = P[k][i1].second.second;
                    P_n[k].first = j;
                }
            }
            P[k][i1].second.second = P_n[k].second;
            P[k][i1].second.first = P_n[k].first;
            P[k][i1].first = i;
            fprintf_s(file, "%4i | %4i | %5.3f\n", i, P_n[k].first, P_n[k].second);
        }
    }

    fopen_s(&file1, "direct.txt", "w");

    fprintf_s(file1, "%3s | %5s | %5s | %5s | %5s | %5s | %5s | %5s \n", "i", "k", "x", "y", "f", "g", "phi", "psi");

    vector< vector <double> > Pr(n, vector < double> (8));

    Pr[0][0] = 1;
    Pr[0][1] = P[0][100].first;
    Pr[0][2] = P[0][100].second.first;
    Pr[0][3] = P[0][100].first - P[0][100].second.first;
    Pr[0][4] = search_(Pr[0][2], f);
    Pr[0][5] = search_(Pr[0][3], g);
    Pr[0][6] = search_(Pr[0][2], phi);
    Pr[0][7] = search_(Pr[0][3], psi);


    fprintf_s(file1, "\n", Pr[0][0], Pr[0][1], Pr[0][2], Pr[0][3], Pr[0][4], Pr[0][5], Pr[0][6], Pr[0][7]);
    for (int i = 1; i < n; i++) {

        Pr[i][0] = i+1;
        Pr[i][1] = Pr[i-1][6] + Pr[i-1][7];
        Pr[i][2] = search__(Pr[i][1], P[i]);
        Pr[i][3] = Pr[i][1] - Pr[i][2];
        Pr[i][4] = search_(Pr[i][2],f);
        Pr[i][5] = search_(Pr[i][3],g);
        if (i == n-1) {
            //fprintf_s(file1, "", Pr[i][0], Pr[i][1], Pr[i][2], Pr[i][3], Pr[i][4], Pr[i][5], "__", "__");
            break;
        }
        Pr[i][6] = search_(Pr[i][2], phi);
        Pr[i][7] = search_(Pr[i][3], psi);
        //fprintf_s(file1, "", Pr[i][0], Pr[i][1], Pr[i][2], Pr[i][3], Pr[i][4], Pr[i][5], Pr[i][6], Pr[i][7]);
    }

    fprintf_s(file1, "\n\n\n");

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += Pr[i][4] + Pr[i][5];
    }
    fprintf_s(file1, "P_1(1000) = %3.4f", sum);
}
