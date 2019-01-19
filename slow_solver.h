#ifndef SLOW_SOLVER_H
#define SLOW_SOLVER_H

#include "cuttingstockproblem.h"

class SlowSolver : public Solver
{
public:
    SlowSolver();
    ~SlowSolver();
    Answer Solve(CuttingStockProblem* problem);
private:
    void BruteVariant(std::vector<size_t>& x);
    void GetAllSolves(std::vector<size_t>& x);
private:
    std::unique_ptr<std::vector<std::vector<size_t>>> A;
    size_t Ans = 1e9;
    std::unique_ptr<CuttingStockProblem> Problem;
    std::unique_ptr<std::vector<std::vector<size_t>>> X;
};

#endif // SLOW_SOLVER_H
