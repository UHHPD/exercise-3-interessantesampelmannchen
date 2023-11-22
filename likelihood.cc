#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double poisson(double mu, int k) {
    return pow(mu, k) * exp(-mu) / tgamma(k + 1);
}

double prob(std::vector<int> daten, double mu) {
    double likelihood = 1;
    for(int k: daten){
        likelihood *= poisson(mu, k);
    }
    return likelihood;
}

double lambda(std::vector<int> daten, double mu) {
    double likelihood = 1;
    double max_likelihood = 1;
    for(int k: daten){
        likelihood *= poisson(mu, k);
        max_likelihood *= poisson(k, k);
    }
    return likelihood/max_likelihood;
}

int main() {
    using namespace std;
    std::vector<int> daten;
    ifstream fin("datensumme.txt");
    int zahl;
    while (fin >> zahl) {
        daten.push_back(zahl);
    }
    fin.close();

    std::cout << "THe likelihood for mu=3.11538 is " << prob(daten, 3.11538) << std::endl;

    ofstream fout("likelihood.txt");
    ofstream fout2("nll.txt");
    ofstream fout3("deltanll.txt");
    ofstream fout4("lambda.txt");
    for(double mu = 0; mu <= 6; mu += 0.1){
        double likelihood = prob(daten, mu);
        fout << mu << " " << likelihood << std::endl;
        fout2 << mu << " " << -2 * log(likelihood) << std::endl;
        fout3 << mu << " " << -2 * (log(likelihood)  - log(prob(daten, 3.11538))) << std::endl;
        fout4 << mu << " " << -2* log(lambda(daten, mu)) << std::endl;
    }
    fout.close();
    fout2.close();
    fout3.close();
    fout4.close();

    std::cout << "z = " << (-2* log(lambda(daten, 3.11538)) - 233)/sqrt(2*233) << std::endl;

}