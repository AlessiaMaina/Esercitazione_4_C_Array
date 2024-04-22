#pragma once

#include <iostream>

using namespace std;

// IMPORT DATA from Input File
bool importData(const string& inputFilePath,
                double& S,
                size_t& n,
                double*& w,
                double*& r);


// RATE OF RETURN of the whole Portfolio
double rateOfReturnPortfolio(const size_t& n,
                             const double* const& w,
                             const double* const& r);


// FINAL VALUE of the whole Portfolio
double finalValuePortfolio(const double& S,
                           const size_t& n,
                           const double* const& w,
                           const double* const& r);


// EXPORT DATA AND RESULT to Output File
bool exportReadDataAndResult(const string& outputFilePath,
                             const double S,
                             const size_t& n,
                             const double* const& w,
                             const double* const& r,
                             const double& ratRet,
                             const double& finVal);


// ARRAY to STRING Conversion
string ArrayToString(const size_t& n,
                     const double* const& v);
