#include "cutting_plane.h"

Cutting_plane::Cutting_plane()
{

}

Cutting_plane::~Cutting_plane() {

}

std::vector<double> Cutting_plane::SolvingSystem(Matrix<size_t>& a_, const std::vector<size_t>& b) {
    Matrix<double> a(N_, N_);
    for (size_t i = 0; i < N_; i++) {
        for (size_t j = 0; j < N_; j++) {
            a[i][j] = static_cast<double>(a_[i][j]);
        }
    }
    a.AppendColumn(b);
    for (size_t i = 0; i < a.GetRows(); i++) {
        for (size_t j = i; j < a.GetColumns(); j++) {
            if (a[j][i] != 0.0) {
                a.SwapRows(i, j);
                break;
            }
        }
        for (size_t j = i + 1; j < a[i].size(); j++)
            a[i][j] /= a[i][i];
        a[i][i] = 1;
        for (size_t j = i + 1; j < a.GetRows(); j++) {
            double tmp = a[j][i];
            for (size_t l = i; l < a.GetColumns(); l++) {
                a[j][l] -= a[i][l] * tmp;
            }
        }
    }
    std::vector<double> x(a.GetRows());
    for (size_t i = a.GetRows() - 1; ; i--) {
        x[i] = a[i][a[i].size()-1];
        for (size_t j = i + 1; j < a.GetRows() ; j++)
            x[i] -= a[i][j] * x[j];
        if (!i)
            break;
    }
    return x;
}

std::pair<std::vector<size_t>, double> Cutting_plane::Knapsack(std::vector<double> &y, std::vector<size_t> &ls, size_t l)
{
    std::vector<double> dp(l + 1);
    std::vector<int> p(l + 1, -1);
    for (size_t i = 1; i <= l; i++) {
        for (size_t j = 0; j < ls.size(); j++) {
            if (ls[j] <= i && dp[i] < y[j] + dp[i - ls[j]]) {
                dp[i] = y[j] + dp[i - ls[j]];
                p[i] = static_cast<int>(j);
            }
        }
    }
    std::vector<size_t> plane(ls.size());
    size_t current = l;
    for (size_t i = dp.size() - 1; ; i--) {
        if (dp[current] < dp[i])
            current = i;
        if (i)
            break;
    }
    while (p[current] != -1) {
        plane[(static_cast<size_t>(p[current]))]++;
        current -= ls[static_cast<size_t>(p[current])];
    }
    return {plane, dp[l]};
}



Answer Cutting_plane::Solve(CuttingStockProblem* problem) {
    N_ = problem->Get_N();
    L_ = problem->Get_L();
    Answer ans;
    Matrix<size_t> a(N_, N_);
    for (size_t i = 0; i < N_; i++) {
        a[i][i] = L_ / problem->Get_Ls()[i];
    }
    std::vector<size_t> c(N_);
    std::vector<double> x, y, g;
    do {
        x = SolvingSystem(a, problem->Get_C());
        c.assign(c.size(), 1);
        a.Transpose();
        y = SolvingSystem(a, c);
        a.Transpose();
        const auto& result_knapsack = Knapsack(y, problem->Get_Ls(), problem->Get_L());
        if (result_knapsack.second <= 1)
            break;
        g = SolvingSystem(a, result_knapsack.first);
        double mn = 1e9; // TODO: INF = 1e9;
        size_t ind = 0;
        for (size_t i = 0; i < g.size(); i++) {
            if (mn > x[i] / g[i]) {
                mn = x[i] / g[i];
                ind = i;
            }
        }
        a.SetColumn(ind, result_knapsack.first);
    } while(1);
    ans.planes = a;
    ans.counts.resize(x.size());
    for (size_t i = 0; i < ans.counts.size(); i++) {
        ans.counts[i] = static_cast<size_t>(x[i] + 0.999999999);
    }
    return ans;
}
