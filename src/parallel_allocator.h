
#ifndef MASTER_BENCHMARKS_PARALLEL_ALLOCATOR_H
#define MASTER_BENCHMARKS_PARALLEL_ALLOCATOR_H

// Adapted from:
//  https://github.com/STEllAR-GROUP/hpx/blob/f4cb39cad8e0ac7478626141166b74dab9f01d52/libs/core/topology/src/topology.cpp
//  COPYRIGHT FROM THE ROOT OF THIS CLASS CAN BE FOUND BELOW
//  Copyright (c) 2015 Thomas Heller
//  Copyright (c) 2015-2022 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef>
#include <limits>
#include <vector>
#include <algorithm>
#include <execution>

///////////////////////////////////////////////////////////////////////////////
//
// WARNING: This class is highly experimental, it might not do what you expect
//
///////////////////////////////////////////////////////////////////////////////

namespace suite {
    ///////////////////////////////////////////////////////////////////////////
    template<typename T, typename Policy>
    class numa_allocator {

        using POLICY_BASE_TYPE = std::remove_cv<typename std::remove_reference<Policy>::type>::type;
        using IS_SEQ = std::is_same<POLICY_BASE_TYPE, std::execution::sequenced_policy>;

    public:
        // typedefs
        using value_type = T;
        using pointer = value_type *;
        using const_pointer = value_type const *;
        using reference = value_type &;
        using const_reference = value_type const &;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

    public:
        // convert an allocator<T> to allocator<U>
        template<typename U>
        struct rebind {
            using other = numa_allocator<U, Policy>;
        };

    public:
        explicit numa_allocator(Policy const &execution_policy)
                : execution_policy(execution_policy) {
        }

        numa_allocator(numa_allocator const &rhs)
                : execution_policy(rhs.execution_policy) {
        }

        numa_allocator &operator=(numa_allocator const &rhs) = delete;

        template<typename U>
        explicit numa_allocator(numa_allocator<U, Policy> const &rhs)
                : execution_policy(rhs.execution_policy) {
        }

        // address
        static pointer address(reference r) {
            return &r;
        }

        static const_pointer address(const_reference r) {
            return &r;
        }

        // memory allocation
        pointer allocate(size_type cnt, void const * = nullptr) {
            // allocate memory
            auto p = static_cast<pointer>(::operator new(cnt * sizeof(T)));

            // early exit when we use std::execution::seq because it would be waste of time to seq touch it
            // this already happens by default since vector gets 0 initialized
            if constexpr (IS_SEQ::value) {
                return p;
            }

            pointer begin = p;
            pointer end = begin + cnt;

            // touch first byte of every object using the given strategy
            std::for_each(execution_policy, begin, end, [](T &val) {
                *reinterpret_cast<char *>(&val) = 0;
            });

            // return the overall memory block
            return p;
        }

        void deallocate(pointer p, size_type cnt) noexcept {
            ::operator delete(p);
        }

        // size
        static size_type max_size() noexcept {
            return (std::numeric_limits<size_type>::max)() / sizeof(T);
        }

        static void destroy(pointer p) noexcept {
            p->~T();
        }

        friend constexpr bool operator==(
                numa_allocator const &, numa_allocator const &) noexcept {
            return true;
        }

        friend constexpr bool operator!=(
                numa_allocator const &l, numa_allocator const &r) noexcept {
            return l != r;
        }

    private:
        template<typename, typename>
        friend
        class numa_allocator;

        Policy const &execution_policy;

    };
}

#endif //MASTER_BENCHMARKS_PARALLEL_ALLOCATOR_H
