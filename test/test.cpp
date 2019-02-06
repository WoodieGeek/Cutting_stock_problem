#include <bits/stdc++.h>
#include <glpk.h>
#include "../matrix.h"
int main() {
    // glp_term_out(GLP_OFF);
    glp_prob* lp = glp_create_prob();
    glp_set_prob_name(lp, "cs");
    glp_set_obj_dir(lp, GLP_MIN);
    const int n = 3;
    const int m = 5;
    glp_add_rows(lp, n);
    glp_add_cols(lp, m);
    std::vector<int> c = {3, 1, 2};
    std::vector<std::vector<int>> a = {
        {4, 0, 1, 0, 2},
        {0, 3, 1, 0, 0},
        {0, 0, 1, 2, 1}
    };
    for (size_t i = 0; i < c.size(); i++)
        glp_set_row_bnds(lp, i + 1, GLP_LO, c[i], 0);
    for (size_t i = 0; i < m; i++) {
        glp_set_col_bnds(lp, i + 1, GLP_LO, 0, 0);
        glp_set_obj_coef(lp, i + 1, 1.0);
    }
    std::vector<int> rows(n * m + 100);
    //int rows[n * m + 1];
    int columns[n * m + 1];
    double d[n * m + 1];
    int cnt = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j]) {
                rows[cnt] = i + 1;
                columns[cnt] = j + 1;
                d[cnt] = a[i][j];
                cnt++;
            }
        }
    }
    glp_load_matrix(lp, cnt - 1, static_cast<int*>(&rows[0]), columns, d);
    glp_simplex(lp, NULL);
    double dual[n + 1];
    for (int i = 1; i <= n; i++) {
        dual[i] = glp_get_row_dual(lp, i);
        std::cout << dual[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "ANS\n";
    for (int i = 1; i <= m; i++)
        std::cout << glp_get_col_prim(lp, i) << " ";
    return 0;
}

