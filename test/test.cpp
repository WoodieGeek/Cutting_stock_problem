#include <bits/stdc++.h>
#include "../matrix.h"
int main() {
    Matrix<int> a(1,2);
    a.GetData()[0][0] = 100;
    try {
        a.Transpose();
    }
    catch(MatrixException e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}


