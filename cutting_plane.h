#ifndef CUTTING_PLANE_H
#define CUTTING_PLANE_H
#include <bits/stdc++.h>
#include <cuttingstockproblem.h>


class Cutting_plane : public Solver {
public:
    Cutting_plane();
    Answer Solve(CuttingStockProblem* problem);
    ~Cutting_plane();
private:
    std::vector<double> SolvingSystem(std::vector<std::vector<size_t>>a, const std::vector<size_t>& b);
    std::pair<std::vector<size_t>, double> Knapsack(std::vector<double>& y, std::vector<size_t>& ls, size_t l);

private:
    size_t N_;
    size_t L_;
};

#endif // CUTTING_PLANE_H
