#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <bits/stdc++.h>


class Knapsack
{
public:
    static std::pair<std::vector<size_t>, double> GetPlane(std::vector<double> &y, std::vector<size_t> &ls, size_t l) {
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

};

#endif // KNAPSACK_H
