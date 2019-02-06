#ifndef CUTTINGSTOCKPROBLEM_H
#define CUTTINGSTOCKPROBLEM_H
#include <bits/stdc++.h>
#include "matrix.h"

struct Answer {
    Answer() = default;
    Matrix<size_t> planes;
    std::vector<size_t> counts;

};

class CuttingStockProblem;

class Solver {
public:
    Solver() = default;
    virtual Answer Solve(CuttingStockProblem* problem) = 0;
    virtual ~Solver() = default;
};


class CuttingStockProblem
{
public:
    CuttingStockProblem(size_t L, size_t N, std::vector<size_t>& Ls, std::vector<size_t>& C);
    CuttingStockProblem(size_t L, size_t N, std::vector<size_t>&& Ls, std::vector<size_t>&& C);
    Answer GetAnswer(std::unique_ptr<Solver> solver);
    size_t Get_L();
    size_t Get_N();
    std::vector<size_t>& Get_Ls();
    std::vector<size_t>& Get_C();
private:
    size_t L_;
    size_t N_;
    std::vector<size_t> Ls_;
    std::vector<size_t> C_;
};

#endif // CUTTINGSTOCKPROBLEM_H
