#ifndef GLPK_SOLUTION_H
#define GLPK_SOLUTION_H
#include <QDebug>
#include "cuttingstockproblem.h"
#include "matrix.h"
#include "knapsack.h"


class Glpk_solution : public Solver
{
public:
    Glpk_solution() = default;
    virtual Answer Solve(CuttingStockProblem* problem) override;
    ~Glpk_solution() override = default;
};

#endif // GLPK_SOLUTION_H
