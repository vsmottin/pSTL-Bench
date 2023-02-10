#include <algorithm>
#include <vector>
#include <utility>
#include <numeric>
#include <iostream>
#include <chrono>
#include <execution>

#define PAR std::execution::unseq,

int main() {

    //std::vector<int> x{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> x(10000, 4);
    std::vector<int> result1;

    const auto s1 = std::chrono::high_resolution_clock::now();
    std::copy_if(PAR x.begin(), x.end(), std::back_inserter(result1), [](const auto &a) { return a > 3; });
    const auto d1 = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - s1);

    std::cout << "Copy_if: " << d1.count() << "ns" << std::endl;

    ///////////////////////////
    std::vector<int> result2;
    result2.reserve(x.size()); // because it might improve perf

    const auto s2 = std::chrono::high_resolution_clock::now();

    std::for_each(PAR x.begin(), x.end(), [&result2](const auto &v) { if (v > 3) { result2.push_back(v); }});

    const auto d2 = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - s2);

    std::cout << "Foreach: " << d2.count() << "ns" << std::endl;

    std::cout << "Size same: " << (result1.size() == result2.size()) << std::endl;
    std::cout << "R1: " << result1.size() << "\nR2: " << result2.size() << std::endl;
}
