#ifndef LINEAR_SYSTEM_H_
#define LINEAR_SYSTEM_H_
#include <vector>
using std::vector;

class LinearSystem
{
public:
    LinearSystem();
    ~LinearSystem();
    void outputData();
    vector<double> LDP();
    vector<double> LU();

private:
    int order;
    void init();
    vector<vector<double>> coefficients;
    vector<double> bVector;
    vector<vector<double>> lMatrix;
    vector<vector<double>> dMatrix;
    vector<vector<double>> pMatrix;
    vector<vector<double>> uMatrix;
    vector<double> solveUpper(const vector<vector<double>> &matrix, const vector<double> &value);
    vector<double> solveLower(const vector<vector<double>> &matrix, const vector<double> &value);
    // vector<double> solveUpper(const vector<vector<double>> &matrix, const vector<double> &value);
    // vector<double> solveLower(const vector<vector<double>> &matrix, const vector<double> &value);
};

#endif