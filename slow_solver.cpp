#include "slow_solver.h"

SlowSolver::SlowSolver() {}

SlowSolver::~SlowSolver() {};

Answer SlowSolver::Solve(CuttingStockProblem* problem) {
    Problem.reset(new CuttingStockProblem(*problem));
    std::vector<size_t> x;
    A.reset(new std::vector<std::vector<size_t>>);
    X.reset(new std::vector<std::vector<size_t>>);
    A->resize(Problem->Get_N());
    BruteVariant(x);
    x.clear();
    GetAllSolves(x);
    Answer ans;
    if(X->empty())
        return ans;
    ans.planes.resize(A->size());
    const auto& variant = X->at(0);
    ans.counts = variant;
    for (size_t i = 0; i < variant.size(); ++i) {
        if (!variant[i])
            break;
        for (size_t j = 0; j < A->size(); j++) {
            ans.planes[j].push_back(A->at(j)[i]);
        }
    }
    return ans;
}

void SlowSolver::BruteVariant(std::vector<size_t>& x) {
    if (x.size() == Problem->Get_Ls().size()) {
        size_t maybe_L = 0;
        for (size_t i = 0; i < x.size(); i++) {
            maybe_L += x[i] * Problem->Get_Ls()[i];
        }
        if (maybe_L <= Problem->Get_L()) {
            for (size_t i = 0; i < x.size(); i++) {
                A->at(i).push_back(x[i]);
            }
        }
    }
    else {
        size_t current = x.size();
        for (size_t v = 0; v <= Problem->Get_L() / Problem->Get_Ls()[current]; v++) {
            x.push_back(v);
            BruteVariant(x);
            x.pop_back();
        }
    }
}

void SlowSolver::GetAllSolves(std::vector<size_t>& x) {
    if (x.size() == A->at(0).size()) {
        for (size_t i = 0; i < A->size(); i++) {
            size_t maybe_b = 0;;
            for (size_t j = 0; j < x.size(); j++) {
                maybe_b +=  x[j] * A->at(i)[j];
            }
            if (maybe_b != Problem->Get_C()[i])
                return;
        }
        size_t sum = 0;
        sum = std::accumulate(x.begin(), x.end(), sum);
        if (sum == Ans) {
            X->push_back(x);
        } else if (sum < Ans) {
            X->clear();
            X->push_back(x);
            Ans = sum;
        }
    }
    else {
        for (size_t v = 0; v <= 1; v++) {
            x.push_back(v);
            GetAllSolves(x);
            x.pop_back();
        }
    }
}


