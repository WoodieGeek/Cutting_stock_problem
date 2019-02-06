#include "glpk_solution.h"
#include <glpk.h>

Answer Glpk_solution::Solve(CuttingStockProblem* problem) {
    size_t N = problem->Get_N();
    int L = problem->Get_L();
    Answer result;
    Matrix<size_t> a(N, N);
    for (size_t i = 0; i < N; i++) {
        a[i][i] = L / problem->Get_Ls()[i];
    }
    glp_prob* lp = glp_create_prob();
    glp_set_prob_name(lp, "cuttingstock");
    glp_set_obj_dir(lp, GLP_MIN);
    glp_add_rows(lp, N);
    glp_add_cols(lp, N);
    const auto& c = problem->Get_C();
    for (size_t i = 0; i < c.size(); i++)
        glp_set_row_bnds(lp, i + 1, GLP_LO, c[i], 0);
    for (size_t i = 0; i < N; i++) {
        glp_set_col_bnds(lp, i + 1, GLP_LO, 0, 0);
        glp_set_obj_coef(lp, i + 1, 1.0);
    }
    std::vector<int> rows(N * N + 1);
    std::vector<int> columns(N * N + 1);
    std::vector<double> d(N * N  + 1);
    int cnt = 1;
    for (int i = 0; i < a.GetRows(); i++) {
        for (int j = 0; j < a.GetColumns(); j++) {
            if (a[i][j]) {
                rows[cnt] = i + 1;
                columns[cnt] = j + 1;
                d[cnt] = a[i][j];
                cnt++;
            }
        }
    }
    glp_load_matrix(lp, cnt - 1, static_cast<int *>(&rows[0]), static_cast<int *>(&columns[0]), static_cast<double *>(&d[0]));
    bool isOptimal = false;
    do {
        glp_simplex(lp, NULL);
        std::vector<double> d(a.GetRows());
        for (size_t i = 0;  i < d.size(); i++)
            d[i] =  glp_get_row_dual(lp, static_cast<int>(i + 1));
        const auto& result_knapsack = Knapsack::GetPlane(d, problem->Get_Ls(), problem->Get_L());
        if (result_knapsack.second <= 1)
            isOptimal = true;
        else {
            a.AppendColumn(result_knapsack.first);
            glp_add_cols(lp, 1);
            int j = glp_get_num_cols(lp);
            glp_set_col_bnds(lp, j, GLP_LO, 0, 0);
            glp_set_obj_coef(lp, j, 1.0);
            std::vector<int> index(a.GetRows() + 1);
            std::vector<double> values(a.GetRows() + 1);
            const auto& plane = result_knapsack.first;
            for (size_t i = 0; i < plane.size(); i++) {
                index[i + 1] = static_cast<int>(i + 1);
                values[i + 1] = plane[i];
            }
            glp_set_mat_col(lp, j, a.GetRows(), static_cast<int*>(&index[0]), static_cast<double*>(&values[0]));
        }
        qDebug() << result_knapsack.second << "\n";
    } while(!isOptimal);
    qDebug() << " goo";
    for (size_t i = 0; i < a.GetColumns(); i++) {
        double val = glp_get_col_prim(lp, static_cast<int>(i + 1));
        if (val != 0) {
            result.counts.push_back(static_cast<size_t>(val + 0.99999));
            std::vector<size_t> column;
            for (size_t j = 0; j < a.GetRows(); j++)
                column.push_back(a[j][i]);
            result.planes.AppendColumn(column);
        }
    }
    return result;
}
