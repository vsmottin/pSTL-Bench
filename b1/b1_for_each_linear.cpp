#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

template<class ExecutionPolicy>
void for_each_linear(ExecutionPolicy &policy, const std::vector<int> &input_data) {

    std::for_each(policy, input_data.begin(), input_data.end(), [](auto &entry) {
        entry = entry + 10;
    });

}

int main() {

    std::vector<int> x(10, 1);

    for_each_linear(std::execution::par, x);

    return 0;
}
