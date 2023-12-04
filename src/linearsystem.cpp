#include "linearsystem.h"
#include <iomanip>
#include <iostream>
using std::cout, std::cin, std::fixed, std::setprecision, std::defaultfloat;

LinearSystem::~LinearSystem() {}

LinearSystem::LinearSystem()
{
    cout << "Enter the order of your matrix: ";
    cin >> order;
    coefficients = vector<vector<double>>(order, vector<double>(order, 0.));

    bVector = vector<double>(order, 0);

    for (int i = 0; i < order; ++i)
    {
        for (int j = 0; j < order; ++j)
        {
            cout << "Enter the coefficient at position [" << i << ", " << j << "]: ";
            cin >> coefficients[i][j];
        }
    }

    for (int i = 0; i < order; ++i)
    {
        cout << "Enter the constant at position [" << i << "]: ";
        cin >> bVector[i];
    }

    init();
}

void LinearSystem::init()
{

    vector<vector<double>> u{coefficients};
    vector<vector<double>> l(order, vector<double>(order, 0.));
    vector<vector<double>> d(order, vector<double>(order, 0.));

    // Initializing the diagonal of the L  and D matrix with 1.
    for (int i = 0; i < order; ++i)
    {
        d[i][i] = 1;
        l[i][i] = 1;
    }

    // Making the L matrix and the U matrix
    for (int i = 0; i < order - 1; ++i)
    {
        double pivot = u[i][i];
        if (pivot == 0)
            throw std::runtime_error("Error! The matrix is not valid");

        for (int k = i + 1; k < order; ++k)
        {
            double multiplier = u[k][i] / pivot;
            l[k][i] = multiplier;

            for (int j = i; j < order; ++j)
            {
                double c = u[k][j] - (multiplier * u[i][j]);
                u[k][j] = c;
            }
        }
    }

    lMatrix = l;
    uMatrix = u;

    // L U done, need to init D and P

    // D is the elements in the diagonal of U, and P is the U with the lines divided by
    for (int i = 0; i < order; ++i)
    {
        double pivot = u[i][i];
        d[i][i] = pivot;
        if (pivot == 0)
            throw std::runtime_error("Error! The matrix is not valid");
        for (int j = 0; j < order; ++j)
        {
            u[i][j] = u[i][j] / pivot;
        }
    }

    dMatrix = d;
    pMatrix = u;
}

vector<double> LinearSystem::solveUpper(const vector<vector<double>> &matrix, const vector<double> &value)
{
    // Condition: the matrix needs to be triangular and need to match the vector size
    int mLength = matrix[0].size();
    int vLength = value.size();

    if (mLength != vLength)
        throw std::runtime_error("Error! Mismatch in matrix/vector size!\n");

    vector<double> result{value};

    for (int i = mLength - 1; i >= 0; --i)
    {
        for (int j = vLength - 1; j >= i; --j)
        {
            if (i == j)
                result[i] = result[i] / matrix[i][j];
            else
            {
                result[i] = result[i] - (matrix[i][j] * result[j]);
            }
        }
    }
    return result;
}

vector<double> LinearSystem::solveLower(const vector<vector<double>> &matrix, const vector<double> &value)
{
    // Condition: the matrix needs to be triangular and need to match the vector size
    int mLength = matrix[0].size();
    int vLength = value.size();

    if (mLength != vLength)
        throw std::runtime_error("Error! Mismatch in matrix/vector size!\n");

    vector<double> result{value};

    for (int i = 0; i < mLength; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            if (i == j)
                result[i] = result[i] / matrix[i][j];
            else
            {
                result[i] = result[i] - (matrix[i][j] * result[j]);
            }
        }
    }
    return result;
}

// Could be void?
vector<double> LinearSystem::LU()
{

    vector<double> yVector{solveLower(lMatrix, bVector)};

    vector<double> xVector{solveUpper(uMatrix, yVector)};

    return xVector;
}

vector<double> LinearSystem::LDP()

{

    vector<double> yVector{solveLower(lMatrix, bVector)};

    vector<double> zVector{solveLower(dMatrix, yVector)};

    vector<double> xVector{solveUpper(pMatrix, zVector)};

    return xVector;
}

void LinearSystem::outputData()
{
    cout << fixed << setprecision(1);
    cout << "---L MATRIX---\n";
    for (auto i = 0; i < order; ++i)
    {
        for (auto j = 0; j < order; ++j)
        {
            cout << lMatrix[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << "---U MATRIX---\n";
    for (auto i = 0; i < order; ++i)
    {
        for (auto j = 0; j < order; ++j)
        {
            cout << uMatrix[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << "---P MATRIX---\n";

    for (auto i = 0; i < order; ++i)
    {
        for (auto j = 0; j < order; ++j)
        {
            cout << pMatrix[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << "---D MATRIX---\n";

    for (auto i = 0; i < order; ++i)
    {
        for (auto j = 0; j < order; ++j)
        {
            cout << dMatrix[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << fixed << setprecision(-1);
    cout << "------- RESULTS -------:\n";
    vector<double> output{LU()};

    cout << "LU RESULT:  [ ";
    for (size_t i = 0; i < output.size(); ++i)
    {
        cout << output[i] << ' ';
    }
    cout << "]\n";

    output = LDP();
    cout << "LDP RESULT: [ ";
    for (size_t i = 0; i < output.size(); ++i)
    {
        cout << output[i] << ' ';
    }
    cout << "]\n";
}