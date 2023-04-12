
#ifndef MASTER_BENCHMARKS_B9_5_TRANSFORM_CUSTOM_ITERATOR_H
#define MASTER_BENCHMARKS_B9_5_TRANSFORM_CUSTOM_ITERATOR_H

#include <vector>
#include <algorithm>

namespace B9 {

    namespace CustomIterator {

        // copied from https://github.com/UoB-HPC/cloverleaf_stdpar/blob/5f17b03982f059765684b568cc93a95591c84905/src/utils.hpp
        // similar can be found in https://github.com/UoB-HPC/BabelStream/blob/main/src/std-indices/STDIndicesStream.h
        // used in paper such as "Evaluating ISO C++ Parallel Algorithms on Heterogeneous HPC Systems"
        template<typename N>
        class range {
        public:
            class iterator {
                friend class range;

            public:

                using difference_type = typename std::make_signed_t<N>;
                using value_type = N;
                using pointer = const N *;
                using reference = N;
                using iterator_category = std::random_access_iterator_tag;

                // XXX This is not part of the iterator spec, it gets picked up by oneDPL if enabled.
                // Without this, the DPL SYCL backend collects the iterator data on the host and copies to the device.
                // This type is unused for any other STL impl.
                using is_passed_directly = std::true_type;

                reference operator*() const { return i_; }

                iterator &operator++() {
                    ++i_;
                    return *this;
                }

                iterator operator++(int) {
                    iterator copy(*this);
                    ++i_;
                    return copy;
                }

                iterator &operator--() {
                    --i_;
                    return *this;
                }

                iterator operator--(int) {
                    iterator copy(*this);
                    --i_;
                    return copy;
                }

                iterator &operator+=(N by) {
                    i_ += by;
                    return *this;
                }

                value_type operator[](const difference_type &i) const { return i_ + i; }

                difference_type operator-(const iterator &it) const { return i_ - it.i_; }

                iterator operator+(const value_type v) const { return iterator(i_ + v); }

                bool operator==(const iterator &other) const { return i_ == other.i_; }

                bool operator!=(const iterator &other) const { return i_ != other.i_; }

                bool operator<(const iterator &other) const { return i_ < other.i_; }

            protected:
                explicit iterator(N start) : i_(start) {}

            private:
                N i_;
            };

            iterator begin() const { return begin_; }

            iterator end() const { return end_; }

            range(N begin, N end) : begin_(begin), end_(end) {}

        private:
            iterator begin_;
            iterator end_;
        };

    }

    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>
    >
    inline void
    b9_5_transform_custom_iterator(ExecutionPolicy &&policy,
                                   const suite::int_vec<BASE_POLICY> &input_data,
                                   suite::int_vec<BASE_POLICY> &res) {

        auto view = B9::CustomIterator::range<int>(0, input_data.size());

        std::transform(policy, view.begin(), view.end(), res.begin(), [&](const auto &index) {
            return input_data[index] + 10;
        });

    }

}

#endif //MASTER_BENCHMARKS_B9_5_TRANSFORM_CUSTOM_ITERATOR_H
