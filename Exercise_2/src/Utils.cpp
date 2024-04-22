#include "Utils.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


// Definition of IMPORT DATA from Input File
bool importData(const string& inputFilePath,
                double& S,
                size_t& n,
                double*& w,
                double*& r)
{
    // OPEN Input File
    ifstream file;
    file.open(inputFilePath);

    if (file.fail())
    {
        cerr << "ATTENTION: Input File open failed!" << endl;
        return false;
    }


    // Get DATA from Input File
    string line;
    while (!file.eof())
    {
        getline(file, line);
        if(line[0] == 'S')          // Definition of "S" (TOTAL SUM INVESTED)
        {
            istringstream convert_S;
            convert_S.str(line.substr(2));
            // line.substr(2): extract and return a substring from "line", starting from 3rd character (which corresponds to index 2)
            convert_S >> S;
        }
        else if(line[0] == 'n')     // Definition of "n" (ASSETS)
        {
            istringstream convert_n;
            convert_n.str(line.substr(2));
            // line.substr(2): extract and return a substring from "line", starting from 3rd character (which corresponds to index 2)
            convert_n >> n;

            break;                  // Break: when a line starting with "n" is found
        }
    }

    getline(file, line);            // Skip the 3rd line, i.e. "w;r"

    w = new double[n];              // Allocate memory for an Array "w" of 8 doubles (n = 8, from Input File)
    r = new double[n];              // Allocate memory for an Array "r" of 8 doubles (n = 8, from Input File)

    for (unsigned int i = 0; i < n; i++)
    {
        // Get the first array, w
        istringstream convert_w;
        getline(file, line, ';');
        convert_w.str(line);
        convert_w >> w[i];

        // Get the second array, r
        istringstream convert_r;
        getline(file, line);
        convert_r.str(line);
        convert_r >> r[i];
    }


    file.close();

    return true;
}


// Definition of RATE OF RETURN of the whole Portfolio
double rateOfReturnPortfolio(const size_t& n,
                             const double* const& w,
                             const double* const& r)
{
    double ratRet = 0;
    for (unsigned int i = 0; i < n; i++)
        ratRet += w[i] * r[i];                  // Compute the "dot product" between 2 Arrays, w and r

    return ratRet;
}


// Definition of FINAL VALUE of the whole Portfolio
double finalValuePortfolio(const double& S,
                           const size_t& n,
                           const double* const& w,
                           const double* const& r)
{
    double finVal = 0;
    for (unsigned int i = 0; i < n; i++)
        finVal += (1 + r[i]) * (w[i] * S);      // Formula given in README.pdf

    return finVal;
}


// Definition of EXPORT DATA AND RESULT to Output File
bool exportReadDataAndResult(const string& outputFilePath,
                             const double S,
                             const size_t& n,
                             const double* const& w,
                             const double* const& r,
                             const double& ratRet,
                             const double& finVal)
{
    // OPEN Output File
    ofstream file;
    file.open(outputFilePath);

    if (file.fail())
    {
        cerr << "ATTENTION: Output File open failed!" << endl;
        return false;
    }


    // WRITE read data and result on the Ouput File
    file << "S = " << fixed << setprecision(2) << S << "," << " n = " << n << endl;

    file << defaultfloat;        // Delete the previous setprecision(2) and restore the default notation

    file << "w = [ ";
    for (unsigned int i = 0; i < n; i++)
        file << (i != 0 ? " " : "") << w[i];
    file << " ]" << endl;

    file << "r = [ ";
    for (unsigned int i = 0; i < n; i++)
        file << (i != 0 ? " " : "") << r[i];
    file << " ]" << endl;

    file << "Rate of return of the portfolio: " << fixed << setprecision(4) << ratRet << endl;
    file << "V: " << fixed << setprecision(2) << finVal << endl;

    file.close();

    return true;
}


// Definition of ARRAY to STRING Conversion
string ArrayToString(const size_t& n,
                     const double* const& v)
{
    string str;
    ostringstream conversionToString;

    conversionToString << "[ ";
    for (unsigned int i = 0; i < n; i++)
        conversionToString << v[i] << " ";
    conversionToString << "]";

    return conversionToString.str();
}
