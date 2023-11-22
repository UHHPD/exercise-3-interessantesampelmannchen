#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double poisson(double mu, int k) {
    return pow(mu, k) * exp(-mu) / tgamma(k + 1);
}

int main() {
    using namespace std;
    vector<int> zaehler(11);

    ifstream fin("datensumme.txt");
    int zahl;
    while (fin >> zahl) {
        zaehler[zahl] += 1;
    }
    fin.close();

    ofstream fout("hist.txt");
    ofstream fout2("histpoi.txt");
    for (unsigned int k = 0; k < zaehler.size(); k++) {
        std::cout << k << ":" << zaehler[k] << endl;
        fout << k << " " << zaehler[k] << endl;
        fout2 << k << " " << zaehler[k] << " " << poisson(3.11538, k) * 234 << endl;
    }
    fout.close();
    fout2.close();

}