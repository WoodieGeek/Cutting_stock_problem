#include "generator.h"

CuttingStockProblem Generator::GetProblem() {
    const size_t N = 10;
    size_t L = rand() % N + 1;
    size_t n = rand() % N + 1;
    std::vector<size_t> l(n), b(n);
    std::transform(l.begin(), l.end(), l.begin(), [&](size_t) { return rand() % L + 1;});
    std::transform(b.begin(), b.end(), b.begin(), [&](size_t) { return rand() % N;});
    return  CuttingStockProblem(L, N, std::move(l), std::move(b));
}
