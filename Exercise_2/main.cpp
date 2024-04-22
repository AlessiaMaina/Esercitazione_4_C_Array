#include "Utils.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


int main()
{
    // INPUT File, type CSV
    string inputFile = "./data.csv";
    double S = 0.0;
    size_t n = 0;
    double* w = nullptr;
    double* r = nullptr;          // Pointers initialized to "nullptr"

    if (!importData(inputFile, S, n, w, r))
    {
        cerr << " ATTENTION: IMPORT goes wrong!" << endl;
        return -1;
    }
    else
        cout << fixed << setprecision(2) << "IMPORT of DATA: Successful! \n" << "S = " << S << ", n = " << n << "\n"
             << "w = " << ArrayToString(n, w) << "\n"
             << "r = " << ArrayToString(n, r) << "\n" << endl;


    double ratRet = rateOfReturnPortfolio(n, w, r);
    cout << fixed << setprecision(4) << "Rate of return of the portfolio: " << ratRet << endl;

    double finVal = finalValuePortfolio(S, n, w, r);
    cout << fixed << setprecision(2) << "V: " << finVal << "\n" << endl;


    // OUTPUT File, type TXT
    string outputFile = "./result.txt";
    if (!exportReadDataAndResult(outputFile, S, n, w, r, ratRet, finVal))
    {
        cerr << "ATTENTION: EXPORT goes wrong!"<< endl;
        return -1;
    }
    else
        cout<< "EXPORT of READ DATA AND RESULT: Successful!" << endl;

    delete[] w;   // Delete an Array
    delete[] r;   // Delete an Array

    return 0;
}
