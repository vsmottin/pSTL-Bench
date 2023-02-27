
#ifndef MASTER_BENCHMARKS_B9_5_TRANSFORM_CUSTOM_ITERATOR_H
#define MASTER_BENCHMARKS_B9_5_TRANSFORM_CUSTOM_ITERATOR_H

#include <vector>
#include <algorithm>

namespace B9 {

    //TODO: investigate why this does not run!
    namespace CustomIterator {

        // copied from https://github.com/UoB-HPC/BabelStream/blob/main/src/std-indices/STDIndicesStream.h
        // used in paper such as "Evaluating ISO C++ Parallel Algorithms on Heterogeneous HPC Systems"
        template<typename N>
        class ranged {
            N from, to;
        public:
            ranged(N from, N to) : from(from), to(to) {}

            class iterator {
                N num;
            public:
                using difference_type = N;
                using value_type = N;
                using pointer = const N *;
                using reference = const N &;
                using iterator_category = std::random_access_iterator_tag;

                explicit iterator(N _num = 0) : num(_num) {}

                iterator &operator++() {
                    num++;
                    return *this;
                }

                iterator operator++(int) {
                    iterator retval = *this;
                    ++(*this);
                    return retval;
                }

                iterator operator+(const value_type v) const { return iterator(num + v); }

                bool operator==(iterator other) const { return num == other.num; }

                bool operator!=(iterator other) const { return *this != other; }

                bool operator<(iterator other) const { return num < other.num; }

                reference operator*() const { return num; }

                difference_type operator-(const iterator &it) const { return num - it.num; }

                value_type operator[](const difference_type &i) const { return num + i; }

            };

            iterator begin() { return iterator(from); }

            iterator end() { return iterator(to >= from ? to + 1 : to - 1); }
        };

    }

    template<class ExecutionPolicy>
    inline void
    b9_5_transform_custom_iterator(ExecutionPolicy &&policy,
                                   const std::vector<int> &input_data,
                                   std::vector<int> &res) {

        auto view = B9::CustomIterator::ranged<int>(0, input_data.size());

        std::transform(policy, view.begin(), view.end(), res.begin(), [&](const auto &index) {
            return input_data[index] + 10;
        });

    }

}

#endif //MASTER_BENCHMARKS_B9_5_TRANSFORM_CUSTOM_ITERATOR_H
