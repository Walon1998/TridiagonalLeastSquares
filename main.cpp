#include <iostream>

#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

/* @brief
 * @param[in] z An $n$-dimensional vector containing one side of input data
 * @param[in] c An $n$-dimensional vector containing the other side of input data
 * @param[out] x The vector of parameters $(\alpha,\beta)$, intercept and slope of the line fitted
 */
Vector2d lsqEst(const VectorXd &z, const VectorXd &c) {
    Vector2d x;
    int length = z.size();


    MatrixXd A(length, 2);

    for (int i = 0; i < length; ++i) {
        A(i) = z(i);
    }

    A(0, 1) = z(1);
    A(length - 1, 1) = z(length - 2);

    for (int j = 1; j < length - 1; ++j) {
        A(j, 1) = z(j - 1) + z(j + 1);
    }


    cout << A << endl;


    x = A.colPivHouseholderQr().solve(c);
    

    return x;
}

int main() {
    int n = 10;
    VectorXd z(n), c(n);
    for (int i = 0; i < n; ++i) {
        z(i) = i + 1;
        c(i) = n - i;
    }

    Vector2d x = lsqEst(z, c);

    cout << "alpha = " << x(0) << endl;
    cout << "beta = " << x(1) << endl;

    return 0;
}
