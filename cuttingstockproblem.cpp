#include "cuttingstockproblem.h"

CuttingStockProblem::CuttingStockProblem(size_t L, size_t N, std::vector<size_t>& Ls, std::vector<size_t>& C)
    : L_(L)
    , N_(N)
    , Ls_(Ls)
    , C_(C) {}

Answer CuttingStockProblem::GetAnswer(std::unique_ptr<Solver> solver) {
    return solver->Solve(std::unique_ptr<CuttingStockProblem>(this));
}

size_t CuttingStockProblem::Get_L() {
    return L_;
}

size_t CuttingStockProblem::Get_N() {
    return N_;
}

std::vector<size_t>& CuttingStockProblem::Get_Ls() {
    return Ls_;
}

std::vector<size_t>& CuttingStockProblem::Get_C() {
    return C_;
}
